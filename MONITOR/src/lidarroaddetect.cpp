#include "lidarroaddetect.h"
#include "qdebug.h"


LidarRoadDetect::LidarRoadDetect()
{
    temp_detect[0][0] = 0.00162690750;
    temp_detect[0][1] = -0.0177743770;
    temp_detect[0][2] = 0.999840736;
    temp_detect[0][3] = 5.88664865;
    temp_detect[0][4] = 0.0510192923;
    temp_detect[0][5] = -0.0148897609;
    temp_detect[0][6] = 0.998586714;
    temp_detect[0][7] = 6.07632923;
    temp_detect[0][8] = -1.5;


    trackinit();

    Lidar_Height = 0;
    lidar_index = 0;



}
void LidarRoadDetect::LidarInit(uchar _lidar_index, float lidar_height){
    ;
}

LidarRoadDetect::~LidarRoadDetect()
{
    if (sockPython != -1)close(sockPython);
}


void LidarRoadDetect::trackinit()
{
    G = Eigen::MatrixXf::Zero(4, 2);
    G(0, 0) = T*T / 2;
    G(1, 0) = T;
    G(2, 1) = T*T / 2;
    G(3, 1) = T;
    A = Eigen::MatrixXf::Zero(4, 4);
    A(0, 0) = 1;
    A(0, 1) = T;
    A(1, 1) = 1;
    A(2, 2) = 1;
    A(2, 3) = T;
    A(3, 3) = 1;
    C = Eigen::MatrixXf::Zero(2, 4);
    C(0, 0) = 1;
    C(1, 2) = 1;
    V_Ob = Eigen::MatrixXf::Zero(2, 4);
    V_Ob(0, 1) = 1;
    V_Ob(1, 3) = 1;
    Q = Eigen::MatrixXf::Zero(2, 2);
    Q(0, 0) = 0.7 * qq;
    Q(1, 1) = 4 * qq;
    R = Eigen::MatrixXf::Zero(2, 2);
    R(0, 0) = 0.7 * rr*rr;
    R(1, 1) = 4 * rr*rr;

    P_predic = Eigen::MatrixXf::Zero(4, 4);
}


void LidarRoadDetect::LidarCluster(std::vector<Cloud_Point>* lidar_points, std::vector<Object>* all_objects_out,\
                                   const float clusterTolerance,const int  minClusterSize,const int  maxClusterSize)
{
    pcl::PointCloud<pcl::PointXYZ> LidarPointFilter;  //过滤地面后点云
    pcl::PointCloud<pcl::PointXYZ> cloudtest;	//左边点

    std::vector<Object> All_Objects;


    for (uint i = 0; i < lidar_points->size(); i++)
    {
        pcl::PointXYZ temp;
        temp.x = (*lidar_points)[i].x;
        temp.y = (*lidar_points)[i].y;
        temp.z = (*lidar_points)[i].z;

        //cv::Point2d point = cv::Point2d(temp.x, temp.y);
        cloudtest.push_back(temp);
        (*lidar_points)[i].r = 100;
        (*lidar_points)[i].g = 200;
        (*lidar_points)[i].b = 150;
    }

    /*****************xjl******/
    for (size_t i = 0; i < cloudtest.size(); i++){

        pcl::PointXYZ temp = pcl::PointXYZ(cloudtest.points[i].x, cloudtest.points[i].y, cloudtest.points[i].z);
        LidarPointFilter.push_back(temp);			//道路以内滤除地面后数据
    }
    /*********************/

    if (!LidarPointFilter.empty())
    {
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud0(new pcl::PointCloud<pcl::PointXYZ>);
        cloud0->clear();
        //填充点云数据
        cloud0->width = LidarPointFilter.size();			//设置点云宽度
        cloud0->height = 1;									//设置点云高度
        cloud0->is_dense = false;								//非密集型
        cloud0->points.resize(cloud0->width * cloud0->height); //变形，无序
        for (int i = 0; i < (int)LidarPointFilter.size(); i++)
        {
            cloud0->points[i].x = LidarPointFilter[i].x;		//PCL显示以m为单位
            cloud0->points[i].y = LidarPointFilter[i].y;
            cloud0->points[i].z = LidarPointFilter[i].z;
        }

        //对点云进行下采样，VoxelGrid可以堪称是个小的3D小方盒
        // TODO:WU
//        pcl::VoxelGrid<pcl::PointXYZ> vg;
//        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered(new pcl::PointCloud<pcl::PointXYZ>);
//        vg.setInputCloud(cloud0);
//        vg.setLeafSize(0.25f, 0.25f, 0.25f);
//        vg.filter(*cloud_filtered);

        //对点云欧式聚类
        pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
        tree->setInputCloud(cloud0);// TODO:WU

        std::vector<pcl::PointIndices> cluster_indices;
        pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
        ec.setClusterTolerance(clusterTolerance); // 6cm// 这里是60cm
        ec.setMinClusterSize(minClusterSize);
        ec.setMaxClusterSize(maxClusterSize);
        ec.setSearchMethod(tree);
        ec.setInputCloud(cloud0);// TODO:WU
        ec.extract(cluster_indices);

        int areaCount = cluster_indices.size();
        std::vector<std::vector<pcl::PointXYZ>> areaPoint(areaCount);

        int temp_j = 0;
        for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin(); it != cluster_indices.end(); ++it)
        {

            for (std::vector<int>::const_iterator pit = it->indices.begin(); pit != it->indices.end(); pit++)
            {
                // TODO:WU
                pcl::PointXYZ temp_areapoint;
                temp_areapoint.x = cloud0->points[*pit].x;
                temp_areapoint.y = cloud0->points[*pit].y;
                temp_areapoint.z = cloud0->points[*pit].z;
                areaPoint[temp_j].push_back(temp_areapoint);
            }
            temp_j++;
        }


        for (int i = 0; i < (int)areaPoint.size(); i++)
        {
            float Minx2 = areaPoint[i].front().x;
            float Maxx2 = areaPoint[i].front().x;
            float Miny2 = areaPoint[i].front().y;
            float Maxy2 = areaPoint[i].front().y;
            float Minz2 = areaPoint[i].front().z;
            float Maxz2 = areaPoint[i].front().z;


            float sumcenterx = 0;
            float sumcentery = 0;
            float sumcenterz = 0;


            for (int j = 0; j < (int)areaPoint[i].size(); j++)
            {
                Minx2 = Minx2 < areaPoint[i][j].x ? Minx2 : areaPoint[i][j].x;
                Maxx2 = Maxx2 > areaPoint[i][j].x ? Maxx2 : areaPoint[i][j].x;
                Miny2 = Miny2 < areaPoint[i][j].y ? Miny2 : areaPoint[i][j].y;
                Maxy2 = Maxy2 > areaPoint[i][j].y ? Maxy2 : areaPoint[i][j].y;
                Minz2 = Minz2 < areaPoint[i][j].z ? Minz2 : areaPoint[i][j].z;
                Maxz2 = Maxz2 > areaPoint[i][j].z ? Maxz2 : areaPoint[i][j].z;
                sumcenterx += areaPoint[i][j].x;
                sumcentery += areaPoint[i][j].y;
                sumcenterz += areaPoint[i][j].z;
            }

            float centerx = sumcenterx / areaPoint[i].size();
            float centery = sumcentery / areaPoint[i].size();
            float centerz = sumcenterz / areaPoint[i].size();



            Object object;
            object.ID = 0;
            object.probability = 1.0;
            strcpy(object.label, "other");
            float tempdist = sqrt(centerx * centerx + centery * centery);

            object.x = centerx;
            object.y = centery;
            object.z = centerz;
            //
            object.xmin = Minx2;
            object.xmax = Maxx2;
            object.ymin = Miny2;
            object.ymax = Maxy2;
            object.zmin = Minz2;
            object.zmax = Maxz2;
            //
            object.height = Maxz2 - Minz2;
            object.width = Maxx2 - Minx2;
            object.length = Maxy2 - Miny2;

            All_Objects.push_back(object);


        }
    }

    std::vector<Object> All_Objects2;
    if(All_Objects.size() > 0)
    {
        LidarTracking(All_Objects); //轨迹
       // qDebug()<<"lidarlist->size()"<<lidarlist.size();

        for (uint i = 0; i < lidarlist.back().tracknum; i++)
        {
            trackobs temptrackobs;
            temptrackobs.ID = lidarlist.back().track[i].ID;
            temptrackobs.centerx = lidarlist.back().track[i].state(0, 0);
            temptrackobs.speedx = lidarlist.back().track[i].state(0, 1);
            temptrackobs.centery = lidarlist.back().track[i].state(0, 2);
            temptrackobs.speedy = lidarlist.back().track[i].state(0, 3);
            temptrackobs.width = lidarlist.back().track[i].width;
            temptrackobs.length = lidarlist.back().track[i].length;
            temptrackobs.height = lidarlist.back().track[i].height;

            float speedtemp = sqrt(temptrackobs.speedx * temptrackobs.speedx + temptrackobs.speedy * temptrackobs.speedy);

            bool tempflag = false;
            for (size_t j = 0; j < i; j++)
            {
                if (fabs(temptrackobs.centerx - lidarlist.back().track[j].state(0, 0)) < 0.15 && fabs(temptrackobs.centery - lidarlist.back().track[j].state(0, 2)) < 0.15 )
                {
                    tempflag = true;
                }
            }
            if (tempflag)
            {
                continue;
            }

            float distance=(temptrackobs.length/2)*(temptrackobs.length/2)+(temptrackobs.width/2)*(temptrackobs.width/2);
            int index=-i-1;
            for (uint j = 0; j < All_Objects.size(); j++)
            {
                float distance_tmp = (All_Objects[j].x - lidarlist.back().track[i].state(0, 0))*(All_Objects[j].x - lidarlist.back().track[i].state(0, 0)) +
                        (All_Objects[j].y - lidarlist.back().track[i].state(0, 2))*(All_Objects[j].y - lidarlist.back().track[i].state(0, 2));
                if(distance>distance_tmp)
                {
                    distance=distance_tmp;
                    index=j;
                }
            }

            if(index>=0)
            {
                Object object;
                object.probability = All_Objects[index].probability;
                strcpy(object.label, All_Objects[index].label);
                object.ID = lidarlist.back().track[i].ID;
                object.height = lidarlist.back().track[i].height;
                object.width = lidarlist.back().track[i].width;
                object.length = lidarlist.back().track[i].length;
                object.y = lidarlist.back().track[i].state(0,2);
                object.x = lidarlist.back().track[i].state(0,0);
                object.z = object.height/2;
                object.speed_y=lidarlist.back().track[i].state(0,3);
                object.speed_x=lidarlist.back().track[i].state(0,1);
                All_Objects2.push_back(object);
            }
        }
        noobsframe = 0;
    }
    else
    {
        noobsframe++;
        if(noobsframe >= 1)
        {
            trackinit();
            tracklist.clear();
            lidarlist.clear();
            noobsframe = 0;
        }
    }
   // qDebug()<<"All_Objects2.size()"<<All_Objects2.size();
   for(size_t i = 0; i < All_Objects2.size() ;i++)
   {
       All_Objects2[i].xmin = All_Objects[i].xmin;
       All_Objects2[i].xmax = All_Objects[i].xmax;
       All_Objects2[i].ymin = All_Objects[i].ymin;
       All_Objects2[i].ymax = All_Objects[i].ymax;
       All_Objects2[i].zmin = All_Objects[i].zmin;
       All_Objects2[i].zmax = All_Objects[i].zmax;
   }

    *all_objects_out = All_Objects2;
   std::cout << "目标个数：" << all_objects_out->size() << std::endl;
}

void LidarRoadDetect::LidarTracking(std::vector<Object> all_objects)
{
    std::vector<trackld> trackframe;
    if (all_objects.size() > 0)
    {
        for (uint i = 0; i < all_objects.size(); i++)
        {
            trackld trackldtemp;
            trackldtemp.centerx = all_objects[i].x;
            trackldtemp.centery = all_objects[i].y;
            trackldtemp.width = all_objects[i].width;
            trackldtemp.length = all_objects[i].length;
            trackldtemp.height = all_objects[i].height;
            trackframe.push_back(trackldtemp);
        }
    }

    tracklist0 tracklist1;
    tracklist1.tracknum = all_objects.size();//一帧里面的聚类数
    tracklist1.track = trackframe;//一帧里面所有聚类


    if (tracklist.size() >= 10)
    {
        tracklist.erase(tracklist.begin());//删除第一个元素
    }
    tracklist.push_back(tracklist1);//每一帧的聚类


    //lidarlist
   // qDebug()<<"lidarlist.size()"<<lidarlist.size();
    if (lidarlist.size() >= 10)//
    {
        lidarlist.erase(lidarlist.begin());//删除开始

        for (int i = 0; i < lidarlist.back().tracknum; i++)
        {
            idmax = idmax > lidarlist.back().track[i].ID ? idmax : lidarlist.back().track[i].ID;
        }


        if (idmax >= 999)
        {
            for (int j = 0; j < lidarlist.back().tracknum; j++)
            {
                lidarlist.back().track[j].ID = j;
            }
            idmax = lidarlist.back().tracknum;
        }
    }
   //

    int numset = pointset.size();

    Eigen::MatrixXf pointlabel = Eigen::MatrixXf::Zero(tracklist.back().tracknum, 1);
    Eigen::MatrixXf setlabel = Eigen::MatrixXf::Zero(numset, 1);

    //

    if (tracklist.size() == 1) //只有一帧数据
    {
        lidlist lidlisttemp;
        lidlisttemp.tracknum = 0;
        lidlisttemp.track.clear();
        lidarlist.push_back(lidlisttemp);

        for (int i = 0; i < tracklist.back().tracknum; i++)//遍历一帧里面的聚类
        {
            trackld tracktemp;
            tracktemp.centerx = all_objects[i].x;
            tracktemp.centery = all_objects[i].y;
            tracktemp.width = all_objects[i].width;
            tracktemp.length = all_objects[i].length;
            tracktemp.height = all_objects[i].height;
            ptset ptsettemp;
            ptsettemp.track = tracktemp;
            ptsettemp.numframe = 1;
            ptsettemp.traframe = 1;
            pointset.push_back(ptsettemp);
        }

    }
    else
    {
        if (tracklist.back().tracknum == 0)
        {
            if (!pointset.empty())
            {
                for (int i = 0; i < numset; i++)
                {
                    pointset[i].numframe = pointset[i].numframe + 1;
                }
            }
            if (lidarlist.back().tracknum != 0)
            {
                lidlist lidlisttemp;
                lidlisttemp.tracknum = lidarlist.back().tracknum;
                lidlisttemp.track.clear();
                lidarlist.push_back(lidlisttemp);

                std::vector<lidtrk> lidtrack;
                for (int i = 0; i < lidarlist[lidarlist.size() - 2].tracknum; i++)
                {
                    lidtrk lidtrktemp;
                    lidtrktemp.state = A * lidarlist[lidarlist.size() - 2].track[i].state.transpose();
                    lidtrktemp.P = lidarlist[lidarlist.size() - 2].track[i].P;
                    lidtrktemp.discount = lidarlist[lidarlist.size() - 2].track[i].discount + 1;
                    lidtrktemp.ID = lidarlist[lidarlist.size() - 2].track[i].ID;
                    lidtrktemp.width = lidarlist[lidarlist.size() - 2].track[i].width;
                    lidtrktemp.length = lidarlist[lidarlist.size() - 2].track[i].length;
                    lidtrktemp.height = lidarlist[lidarlist.size() - 2].track[i].height;
                    lidtrack.push_back(lidtrktemp);
                }
                lidarlist.back().track = lidtrack;

                lidlisttemp.tracknum = lidarlist.back().track.size();
            }
        }
        else
        {
            lidlist lidlisttemp;
            lidlisttemp.tracknum = lidarlist.back().tracknum;
            lidlisttemp.track.clear();
            lidarlist.push_back(lidlisttemp);

            std::vector<lidtrk> lidtrack;
            if (lidarlist[lidarlist.size() - 2].tracknum != 0)
            {
                pointdistance = Eigen::MatrixXf::Zero(numset, tracklist.back().tracknum);
                Eigen::MatrixXf D = Eigen::MatrixXf::Zero(lidarlist[lidarlist.size() - 2].tracknum, tracklist.back().tracknum);
                Eigen::MatrixXf Pdt = Eigen::MatrixXf::Zero(lidarlist[lidarlist.size() - 2].tracknum, 1);
                Eigen::MatrixXf W = Eigen::MatrixXf::Zero(lidarlist[lidarlist.size() - 2].tracknum, tracklist.back().tracknum);
                Eigen::MatrixXf Wg = Eigen::MatrixXf::Zero(lidarlist[lidarlist.size() - 2].tracknum, tracklist.back().tracknum);
                Eigen::MatrixXf Ps = Eigen::MatrixXf::Zero(lidarlist[lidarlist.size() - 2].tracknum, tracklist.back().tracknum);
                Eigen::MatrixXf Ps0 = Eigen::MatrixXf::Zero(lidarlist[lidarlist.size() - 2].tracknum, 1);
                Eigen::MatrixXf Pb = Eigen::MatrixXf::Zero(lidarlist[lidarlist.size() - 2].tracknum, tracklist.back().tracknum);
                Eigen::MatrixXf Pb0 = Eigen::MatrixXf::Zero(lidarlist[lidarlist.size() - 2].tracknum, 1);
                Eigen::MatrixXf Pr = Eigen::MatrixXf::Zero(lidarlist[lidarlist.size() - 2].tracknum, tracklist.back().tracknum);
                Eigen::MatrixXf Pr0 = Eigen::MatrixXf::Zero(lidarlist[lidarlist.size() - 2].tracknum, tracklist.back().tracknum);
                Eigen::MatrixXf Ag = Eigen::MatrixXf::Zero(lidarlist[lidarlist.size() - 2].tracknum, tracklist.back().tracknum);
                float Pd = 0.99;        //¼ÙÉèÀ×´ïÌ½²â¸ÅÂÊÎª0.99
                //                float a = 1;
                float N = 1;

                for (int j = 0; j < lidarlist[lidarlist.size() - 2].tracknum; j++)
                {
                    Pdt(j, 0) = lambda * (1.0 - Pd);

                    P_predic = A * lidarlist[lidarlist.size() - 2].track[j].P * A.transpose() + G * Q * G.transpose();

                    S = C * P_predic * C.transpose() + R;

                    K = P_predic * C.transpose() * S.inverse();

                    for (int i = 0; i < tracklist.back().tracknum; i++)
                    {
                        Eigen::MatrixXf dtemp;
                        dtemp = C * (A * lidarlist[lidarlist.size() - 2].track[j].state.transpose());
                        Eigen::MatrixXf d = Eigen::MatrixXf::Zero(1, 2);
                        d(0, 0) = fabs(tracklist.back().track[i].centerx - dtemp(0, 0));
                        d(0, 1) = fabs(tracklist.back().track[i].centery - dtemp(1, 0));

                        Eigen::MatrixXf state;
                        state = lidarlist[lidarlist.size() - 2].track[j].state;

                        Eigen::MatrixXf v = Eigen::MatrixXf::Zero(1, 2);
                        v(0, 0) = state(0, 1);
                        v(0, 1) = state(0, 3);

                        float nv = 0;
                        if (v.norm() != 0)
                        {
                            nv = v.norm();
                            v(0, 0) = v(0, 0) / nv;
                            v(0, 1) = v(0, 1) / nv;
                        }

                        Eigen::MatrixXf d0 = d * S.inverse() * d.transpose();

                        D(j, i) = d0.determinant();     //¾àÀëÏà¹ØÐÔ
                        //N = (1 / (sqrt(2 * CV_PI * S.determinant()))) * exp(-0.5 * D(j ,i)* D(j ,i) / S.determinant());
                        N = (1 / (2 * CV_PI * sqrt(S.determinant()))) * exp(-0.5 * D(j, i)* D(j, i) / S.determinant());
                        if (D(j, i) > 0 && D(j, i) < g_sigma)
                        {
                            W(j, i) = 1;
                        }

                        Pr0(j, i) = W(j, i) * N;       //Á¿²âjÂäÈëÄ¿±êtµÄ¸ú×ÙÃÅÄÚµÄ¸ÅÂÊÃÜ¶È

                        Eigen::MatrixXf V_reall = d / T;
                        Eigen::MatrixXf tmpv = V_Ob * lidarlist[lidarlist.size() - 2].track[j].state.transpose();
                        Eigen::MatrixXf dv = V_reall - tmpv.transpose();
                        Ag(j, i) = (dv * S.inverse() * dv.transpose()).determinant();

                        //                        float Ng =  (1 / (sqrt(2 * CV_PI * S.determinant()))) * exp(-0.5 * Ag(j ,i)*Ag(j ,i)/S.determinant());

                        if (Ag(j, i) > 0 && Ag(j, i) < 4)
                        {
                            Wg(j, i) = 1;
                        }
                    }
                }

                //¶Ô¸÷Ä¿±ê¸ú×ÙÃÅÄÚµÄ¹«¹²µã¼£µÄ¸ÅÂÊÃÜ¶ÈÖµ½øÐÐË¥¼õ
                for (int j = 0; j < lidarlist[lidarlist.size() - 2].tracknum; j++)
                {
                    for (int i = 0; i < tracklist.back().tracknum; i++)
                    {
                        Pr(j, i) = Pr0(j, i) * Pr0(j, i) / (Pr0.col(i).sum() + exp(-25.0));
                    }
                }

                //¼ÆËã»¥Áª¸ÅÂÊ
                for (int j = 0; j < lidarlist[lidarlist.size() - 2].tracknum; j++)
                {
                    for (int i = 0; i < tracklist.back().tracknum; i++)
                    {
                        Pb(j, i) = Pr(j, i) / (Pr.row(j).sum() + exp(-25.0) + Pdt(j, 0));
                    }
                    Pb0(j, 0) = 1 - Pb.row(j).sum();
                }

                //¶ÔÂäÈë¸÷¸ú×Ù²¨ÃÅÄÚµÄ¹«¹²µã¼£µÄ»¥Áª¸ÅÂÊ½øÐÐË¥¼õ
                Eigen::MatrixXf Pb_new = Eigen::MatrixXf::Zero(lidarlist[lidarlist.size() - 2].tracknum, tracklist.back().tracknum);
                for (int j = 0; j < lidarlist[lidarlist.size() - 2].tracknum; j++)
                {
                    for (int i = 0; i < tracklist.back().tracknum; i++)
                    {
                        Pb_new(j, i) = Pb(j, i) * Pb(j, i) / (Pb.col(i).sum() + exp(-25.0));
                    }
                }

                //¼ÆËãÐÂµÄ»¥Áª¸ÅÂÊ
                for (int j = 0; j < lidarlist[lidarlist.size() - 2].tracknum; j++)
                {
                    for (int i = 0; i < tracklist.back().tracknum; i++)
                    {
                        Ps(j, i) = Pb_new(j, i) / (Pb_new.row(j).sum() + exp(-25.0) + Pb0(j, 0));
                    }

                    Ps0(j, 0) = 1 - Ps.row(j).sum();
                }

                //¸ù¾Ý¸ÅÂÊ¸üÐÂÊý¾Ý
                for (int j = 0; j < lidarlist[lidarlist.size() - 2].tracknum; j++)
                {
                    P_predic = A * lidarlist[lidarlist.size() - 2].track[j].P * A.transpose() + G * Q * G.transpose();
                    S = C * P_predic * C.transpose() + R;
                    K = P_predic * C.transpose() * S.inverse();
                    //cout << "K" << endl << K <<endl;

                    Eigen::MatrixXf Gain = Eigen::MatrixXf::Zero(4, 4);
                    lidtrk lidtrktmp;
                    if (Ps0(j, 0) > 0.8)
                    {
                        Gain(0, 0) = 1;
                        Gain(0, 1) = T;
                        Gain(1, 1) = 1;
                        Gain(2, 2) = 1;
                        Gain(2, 3) = T;
                        Gain(3, 3) = 1;
                        lidtrktmp.state = (Gain * lidarlist[lidarlist.size() - 2].track[j].state.transpose()).transpose();
                        lidtrktmp.P = (Eigen::MatrixXf::Identity(4, 4) - K * C) * P_predic;
                        lidtrktmp.discount = lidarlist[lidarlist.size() - 2].track[j].discount + 1;
                        lidtrktmp.ID = lidarlist[lidarlist.size() - 2].track[j].ID;
                        lidtrktmp.width = lidarlist[lidarlist.size() - 2].track[j].width;
                        lidtrktmp.length = lidarlist[lidarlist.size() - 2].track[j].length;
                        lidtrktmp.height = lidarlist[lidarlist.size() - 2].track[j].height;
                    }
                    else
                    {
                        Eigen::MatrixXf tmp2 = Eigen::MatrixXf::Zero(4, 1);
                        Eigen::MatrixXf x_predic = A * lidarlist[lidarlist.size() - 2].track[j].state.transpose();
                        Gain(0, 0) = 1;
                        Gain(1, 1) = 2;
                        Gain(2, 2) = 1;
                        Gain(3, 3) = 2;
                        Gain = 3 * Gain;



                        for (int i = 0; i < tracklist.back().tracknum; i++)
                        {
                            Eigen::MatrixXf tr_state(2, 1);
                            tr_state(0, 0) = tracklist.back().track[i].centerx;
                            tr_state(1, 0) = tracklist.back().track[i].centery;
                            tmp2 = tmp2 + Ps(j, i) * (x_predic + Gain * K * (tr_state - C * x_predic));
                        }

                        int tmmp = -1;
                        int ii, jj;
                        Pr0.row(j).maxCoeff(&ii, &jj);
                        tmmp = jj;
                        if (tmmp == -1)
                        {
                            tmmp = 0;
                        }

                        tmp2 = Ps0(j, 0) * x_predic + tmp2;

                        lidtrktmp.state = tmp2.transpose();
                        lidtrktmp.P = (Eigen::MatrixXf::Identity(4, 4) - K * C) * P_predic;
                        lidtrktmp.discount = 0;
                        lidtrktmp.ID = lidarlist[lidarlist.size() - 2].track[j].ID;
                        lidtrktmp.height = tracklist.back().track[tmmp].height;

                        if (tmmp != -1)
                        {
                            float temp1 = lidarlist[lidarlist.size() - 2].track[j].width * lidarlist[lidarlist.size() - 2].track[j].length;
                            float temp2 = tracklist.back().track[tmmp].width * tracklist.back().track[tmmp].length;

                            if (fabs(temp1 / temp2 - 1) < 0.3)
                            {
                                lidtrktmp.width = tracklist.back().track[tmmp].width;
                                lidtrktmp.length = tracklist.back().track[tmmp].length;
                            }
                            else
                            {
                                lidtrktmp.width = 0.7 * lidarlist[lidarlist.size() - 2].track[j].width + 0.3 * tracklist.back().track[tmmp].width;
                                lidtrktmp.length = 0.7 * lidarlist[lidarlist.size() - 2].track[j].length + 0.3 * tracklist.back().track[tmmp].length;
                            }
                        }
                        else
                        {
                            lidtrktmp.width = lidarlist[lidarlist.size() - 2].track[j].width;
                            lidtrktmp.length = lidarlist[lidarlist.size() - 2].track[j].length;
                        }
                    }
                    lidtrack.push_back(lidtrktmp);
                    lidarlist.back().tracknum = lidarlist[lidarlist.size() - 2].tracknum;
                    lidarlist.back().track = lidtrack;
                }

                for (int i = 0; i < tracklist.back().tracknum; i++)
                {
                    if (W.col(i).sum() > 0)
                    {
                        pointlabel(i, 0) = 1;
                    }
                }
            }

            if (pointset.empty())
            {
                for (int i = 0; i < tracklist.back().tracknum; i++)
                {
                    if (pointlabel(i, 0) == 0)
                    {
                        ptset ptsettemp;
                        ptsettemp.track = tracklist.back().track[i];
                        ptsettemp.numframe = 1;
                        ptsettemp.traframe = 1;
                        pointset.push_back(ptsettemp);
                        numset = numset + 1;
                    }
                }
            }
            else
            {
                pointdistance = Eigen::MatrixXf::Zero(numset, tracklist.back().tracknum);
                for (int i = 0; i < tracklist.back().tracknum; i++)
                {
                    for (int j = 0; j < numset; j++)
                    {
                        Eigen::MatrixXf dxy(1, 2);
                        float maxWidth = tracklist.back().track[i].width > 1.0 ? tracklist.back().track[i].width : 1.0;
                        float maxLength = tracklist.back().track[i].length > 1.0 ? tracklist.back().track[i].length : 1.0;
                        dxy(0, 0) = fabs((tracklist.back().track[i].centerx - pointset[j].track.centerx) / maxWidth);
                        dxy(0, 1) = fabs((tracklist.back().track[i].centery - pointset[j].track.centery) / maxLength);
                        pointdistance(j, i) = sqrt(dxy(0, 0) * dxy(0, 0) + dxy(0, 1) * dxy(0, 1));
                    }
                }
                for (int j = 0; j < numset; j++)
                {
                    int tv, tc;
                    pointdistance.row(j).minCoeff(&tv, &tc);
                    if (tv < tvthd && pointlabel(tc, 0) == 0)
                    {
                        pointset[j].track = tracklist.back().track[tc];
                        pointset[j].numframe = pointset[j].numframe + 1;
                        pointset[j].traframe = pointset[j].traframe + 1;
                        pointlabel(tc, 0) = 1;
                        setlabel(j, 0) = 1;
                    }
                    else
                    {
                        pointset[j].numframe = pointset[j].numframe + 1;
                    }
                }
            }

            Eigen::MatrixXf pointsetdet = Eigen::MatrixXf::Zero(1, 1);

            for (int i = 0; i < numset; i++)
            {
                if (pointset[i].traframe > 2)
                {
                    lidtrk lidtrktemp;
                    lidtrktemp.state = Eigen::MatrixXf::Zero(1, 4);
                    lidtrktemp.state(0, 0) = pointset[i].track.centerx;
                    lidtrktemp.state(0, 1) = 0;
                    lidtrktemp.state(0, 2) = pointset[i].track.centery;
                    lidtrktemp.state(0, 3) = 0;
                    lidtrktemp.P = Eigen::MatrixXf::Zero(4, 4);
                    lidtrktemp.P(0, 0) = 0.1422;
                    lidtrktemp.P(0, 1) = 0.1029;
                    lidtrktemp.P(1, 0) = 0.1029;
                    lidtrktemp.P(1, 1) = 0.1065;
                    lidtrktemp.P(2, 2) = 0.8128;
                    lidtrktemp.P(2, 3) = 0.5880;
                    lidtrktemp.P(3, 2) = 0.5880;
                    lidtrktemp.P(3, 3) = 0.9171;
                    lidtrktemp.discount = 0;


                    if (lidarlist.size() < 10)
                    {
                        Eigen::MatrixXi id_available = Eigen::MatrixXi::Ones(1, 20);
                        Eigen::MatrixXi id = Eigen::MatrixXi::Zero(1, lidarlist.back().tracknum);
                        for (int k = 0; k < lidarlist.back().tracknum; k++)
                        {
                            id(0, k) = lidarlist.back().track[k].ID;
                        }
                        for (int id_i = 0; id_i < id_available.size(); id_i++)
                        {
                            for (int id_j = 0; id_j < id.size(); id_j++)
                            {
                                if (id_i - id(id_j) == 0)
                                {
                                    id_available(id_i) = 0;
                                }
                            }
                        }
                        std::vector<int> temp;
                        for (int id_i = 0; id_i < id_available.size(); id_i++)
                        {
                            if (id_available(id_i) == 1)
                            {
                                temp.push_back(id_i);
                            }
                        }
                        if (!temp.empty())
                        {
                            lidtrktemp.ID = temp.front();
                        }
                        else
                        {
                            int idmax = 0;
                            for (int id1 = 0; id1 < lidarlist.back().tracknum; id1++)
                            {
                                idmax = idmax > lidarlist.back().track[id1].ID ? idmax : lidarlist.back().track[id1].ID;
                            }
                            lidtrktemp.ID = idmax + 1;
                        }

                    }
                    else
                    {
                        lidtrktemp.ID = idmax + 1;
                    }


                    lidtrktemp.width = pointset[i].track.width;
                    lidtrktemp.length = pointset[i].track.length;
                    lidtrktemp.height = pointset[i].track.height;

                    lidarlist.back().track.push_back(lidtrktemp);
                    lidarlist.back().tracknum = lidarlist.back().track.size();

                }
            }
        }

        std::vector<int> delindex;
        for (int j = 0; j < lidarlist.back().tracknum; j++)
        {
            if (lidarlist.back().track[j].discount > disthd)
            {
                delindex.push_back(j);
            }
        }
        if (!delindex.empty())
        {
            for (int di = delindex.size() - 1; di >= 0; di--)
            {
                lidarlist.back().track.erase(lidarlist.back().track.begin() + delindex[di]);
            }
            lidarlist.back().tracknum = lidarlist.back().tracknum - delindex.size();
        }

        std::vector<int> pointsetdel;
        for (int i = 0; i < numset; i++)
        {
            if (pointset[i].numframe > 3 || pointset[i].traframe > 2)
            {
                pointsetdel.push_back(i);
            }
        }
        if (!pointsetdel.empty())
        {
            for (int pd = pointsetdel.size() - 1; pd >= 0; pd--)
            {
                pointset.erase(pointset.begin() + pointsetdel[pd]);
            }
        }
    }
}
