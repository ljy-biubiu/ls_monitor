#include "algonrithm.h"
#include<pcl/filters/passthrough.h>
#include <QDebug>
#include <QSettings>

Algonrithm::Algonrithm(const float resolution,const float difference_threshold)
{
    for(int i =0;i<AREAS;i++)
    {
        filttCloud[i].reset(new pcl::PointCloud<pcl::PointXYZRGB>);
    }
    tCloud.reset(new pcl::PointCloud<pcl::PointXYZRGB>);

    qRegisterMetaType<pcl::PointCloud<pcl::PointXYZRGB>::Ptr>("pcl::PointCloud<pcl::PointXYZRGB>::Ptr");
    m_resolution = resolution;
    m_difference_threshold = difference_threshold;

}

void Algonrithm::setResolution(const float resolution)
{
    m_resolution = resolution;
}

void Algonrithm::setDifference_threshold(const float difference_threshold)
{
    m_difference_threshold = difference_threshold;
}

void Algonrithm::run()
{
    lidarIntruder cloud;
    QVariant Datavar;
    Datavar.setValue(cloud);
    qRegisterMetaType<QVariant>("QVariant");
    cloud.tCloud.reset(new pcl::PointCloud<pcl::PointXYZRGB>);
    for(int index=0;index<AREAS;index++)
    {

        points[index].clear();

        for(int i=0;i<area[index].Area2D_point_T.size();i++)
        {
            points[index].push_back(cv::Point2f(area[index].Area2D_point_T[i].x,area[index].Area2D_point_T[i].y));
        }
        // TODO: 此处可添加基于动态拟合海平面作为基准面

        // TODO: 利用栅格局部高度差
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_z(new pcl::PointCloud<pcl::PointXYZRGB>);//输出对x方向进行截取后的数据
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_x(new pcl::PointCloud<pcl::PointXYZRGB>);//输出对x方向进行截取后的数据
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_y(new pcl::PointCloud<pcl::PointXYZRGB>);//输出对Z方向进行截取后的数据

        pcl::PointCloud<pcl::PointXYZRGB>::Ptr grid_height_difference_cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
        getGridHeightDifference(tCloud, grid_height_difference_cloud, m_resolution, m_difference_threshold);
        pcl::PassThrough<pcl::PointXYZRGB> pass;

        pass.setInputCloud(grid_height_difference_cloud);
        pass.setFilterFieldName("z");
        pass.setFilterLimits(area[index].Area_height_down, area[index].Area_height_top);
        pass.filter(*cloud_z);
//        std::cout << "cloud_z size: " << cloud_z->points.size() << std::endl;

        *cloud_y +=*cloud_z;

        grid_height_difference_cloud->clear();
//        qDebug()<<index<<box_cloud[index]->size();
        filttCloud[index]->clear();

        for(int i=0;i < cloud_y->size();i++)
        {
            // opencv方法生成障碍物点云
            cv::Point2f pt;

            pt.x = cloud_y->points[i].x;
            pt.y = cloud_y->points[i].y;

            if(points[index].size()>2)
            {
                double dis = pointPolygonTest(points[index], pt, true);
                if(dis > 0)
                {
                    pcl::PointXYZRGB p;
                    p.x =cloud_y->points[i].x;
                    p.y= cloud_y->points[i].y;
                    p.z=cloud_y->points[i].z;

                    if(index ==0)
                    {
                        p.r =255; p.g=0;p.b =0;
                    }
                    else if(index ==1)
                    {
                        p.r =0; p.g=255;p.b =0;
                    }
                    else if(index ==1)
                    {
                        p.r =0; p.g=0;p.b =255;
                    }

                    filttCloud[index]->push_back(p);

                }

            }
        }
        *cloud.tCloud +=*filttCloud[index];
    }

    emit sigShow(cloud);

}

// 获取海平面浮标线的点云用于平面拟合
void Algonrithm::useRANSAC (pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_in, pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_out,
                             pcl::ModelCoefficients &coefficients, int sac_model, int max_iterations, float threshold)
{
//    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients);
    pcl::PointIndices::Ptr inliers(new pcl::PointIndices);
    pcl::SACSegmentation<pcl::PointXYZRGB> seg;
    seg.setOptimizeCoefficients(true);
    seg.setModelType(sac_model);
    seg.setMethodType(pcl::SAC_RANSAC);
    seg.setMaxIterations( max_iterations);
    seg.setDistanceThreshold(threshold);
    seg.setInputCloud(cloud_in);
    seg.segment(*inliers, coefficients);
    if (inliers->indices.size() == 0)
        std::cout << "Error ! Could not found any inliers !" << std::endl;
    pcl::ExtractIndices<pcl::PointXYZRGB> extractor;
    extractor.setInputCloud(cloud_in);
    extractor.setIndices(inliers);
    extractor.setNegative(false);
    extractor.filter(*cloud_out);

}

void Algonrithm::passThrough(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_in, pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_out, std::shared_ptr<PassThroughConfig> config)
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr x_output(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr y_output(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::PassThrough<pcl::PointXYZRGB> pass;
    auto start = std::chrono::system_clock::now();

    pass.setInputCloud(cloud_in);
    pass.setFilterFieldName("x");
    pass.setFilterLimits(config->kx_min, config->kx_max);
    pass.setFilterLimitsNegative(false);
    pass.filter(*x_output);

    pass.setInputCloud(x_output);
    pass.setFilterFieldName("y");
    pass.setFilterLimits(config->ky_min, config->ky_max);
    pass.setFilterLimitsNegative(false);
    pass.filter(*y_output);

    pass.setInputCloud(y_output);
    pass.setFilterFieldName("z");
    pass.setFilterLimits(config->kz_min, config->kz_max);
    pass.setFilterLimitsNegative(false);
    pass.filter(*cloud_out);

    auto end = std::chrono::system_clock::now();
    std::cout << "PassThroughTime: " << std::chrono::duration_cast<std::chrono::microseconds> (end - start ).count() << " us" << std::endl;
}

inline
void Algonrithm::getGridHeightDifference(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_in, pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_out, float resolution, float difference_threshold)
{
    std::vector<int> indices;
    pcl::GridHeightDifference<pcl::PointXYZRGB> grid_height_difference(resolution, difference_threshold);
    grid_height_difference.setInputCloud(cloud_in);
    grid_height_difference.filter(*cloud_out);

}
