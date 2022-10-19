#include "maindeal.h"

Maindeal::Maindeal( AddLidar* addidar ,QObject* parent ) : QObject( parent ),addidar_( addidar ) {

    getCalibAngle();

    viewer.reset (new pcl::visualization::PCLVisualizer ("viewer", false));

    //行人轨迹
    for(int i = 0;i < 255;i++)
    {
        Clu_cloud[i].reset(new pcl::PointCloud<pcl::PointXYZRGB>);
    }
    allcloud.reset(new pcl::PointCloud<pcl::PointXYZRGB>);
    saveDataFlag = 0;

    lidarClustem = new LidarClustem;

    algonrithm =new Algonrithm(addidar_->data.resolution,addidar_->data.difference_threshold);

    // TODO:WUZHENFENG 20220407
    // 添加报警器服务端线程
    std::thread alarm_light_thread(StartAlarmLight);
    alarm_light_thread.detach();
    std::thread alarmIP_light_thread(StartAlarmLight_IP);
    alarmIP_light_thread.detach();

    m_ptz = new PTZ();




    if("CH128X1" == addidar_->data.lidarModel)
    {
        qRegisterMetaType<struct LidarDataCHXXX>("struct LidarDataCHXXX");
        qRegisterMetaType<pcl::PointCloud<pcl::PointXYZRGB>::Ptr>("pcl::PointCloud<pcl::PointXYZRGB>::Ptr");
        getCH128X1 = new GetlidarCH128X1(addidar_->data.lidarPort);
        connect(getCH128X1, SIGNAL(SendData(struct LidarDataCHXXX)), this, SLOT(CalculateCoordinatesCH128X1(struct LidarDataCHXXX)));
        connect(this, SIGNAL(send_CH128X1(pcl::PointCloud<pcl::PointXYZRGB>::Ptr)), this, SLOT(get_CH128X1(pcl::PointCloud<pcl::PointXYZRGB>::Ptr)));
        getCH128X1->start();
    }
    else if("C16" == addidar_->data.lidarModel)
    {
        qRegisterMetaType<struct LidarData>("struct LidarData");
        qRegisterMetaType<pcl::PointCloud<pcl::PointXYZRGB>::Ptr>("pcl::PointCloud<pcl::PointXYZRGB>::Ptr");
        getC16 = new GetlidarC16(addidar_->data.lidarPort);
        connect(getC16, SIGNAL(send_CH128X1(struct LidarData)), this, SLOT(CalculateCoordinates(struct LidarData)));
        connect(this, SIGNAL(send_lidarC16(pcl::PointCloud<pcl::PointXYZRGB>::Ptr)), this, SLOT(get_lidarC16(pcl::PointCloud<pcl::PointXYZRGB>::Ptr)));
        getC16->start();
    }
}



//计算最大最小
void Maindeal::search_max_min(QList<pcl::PointXYZRGB> box)
{
    if (box.size()>0)
    {
        float point_x[50] = { 0 };
        float point_y[50] = { 0 };

        for (unsigned int i = 0; i < box.size(); i++)
        {
            point_x[i] = box[i].x * 1000;
            point_y[i] = box[i].y * 1000;
        }
        quickSort(point_x, 0, box.size() - 1);
        quickSort(point_y, 0, box.size() - 1);
    }
}


void Maindeal::quickSort(float s[], int l, int r)
{
    if (l< r)
    {
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while (i < j && s[j] >= x) // 从右向左找第一个小于x的数
                j--;
            if (i < j)
                s[i++] = s[j];
            while (i < j && s[i]< x) // 从左向右找第一个大于等于x的数
                i++;
            if (i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quickSort(s, l, i - 1); // 递归调用
        quickSort(s, i + 1, r);
    }
}


///*********************点云显示**********************************/
////添加雷达安装角度与高度调整

void Maindeal::CalculateCoordinates(LidarData lidardata)
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr tCloud(new pcl::PointCloud<pcl::PointXYZRGB>);

    double cosTheta[16] = { 0 };
    double sinTheta[16] = { 0 };
    for (int i = 0; i < 16; i++)
    {
        int theta = i;
        if (i % 2 == 0)
            theta = i - 15;
        cosTheta[i] = cos(theta * PI / 180);
        sinTheta[i] = sin(theta * PI / 180);
    }
    double sinAngle[5000] = { 0 };
    double cosAngle[5000] = { 0 };
    if (lidardata.angle.size()>5000) lidardata.angle.clear();
    for (int i = 0; i < (int)lidardata.angle.size(); i++)
    {
        sinAngle[i] = sin(lidardata.angle[i] * PI / 180);
        cosAngle[i] = cos(lidardata.angle[i] * PI / 180);
    }

    tCloud->width = lidardata.angle.size() * 16;
    tCloud->height = 1;
    tCloud->is_dense = false;
    tCloud->points.resize(tCloud->width * tCloud->height);

    for (int i = 0; i < 16; i++)
    {

        for (int j = 0; j < (int)lidardata.angle.size(); j++)
        {
            if (lidardata.distance[i][j] > 0)//滤除距离为0
            {
                tCloud->points[i*lidardata.angle.size() + j].x = (lidardata.distance[i][j] * cosTheta[i] * sinAngle[j]) / 100.f;
                tCloud->points[i*lidardata.angle.size() + j].y = (lidardata.distance[i][j] * cosTheta[i] * cosAngle[j]) / 100.f;
                tCloud->points[i*lidardata.angle.size() + j].z = (lidardata.distance[i][j] * sinTheta[i]) / 100.f;

                //坐标轴方向转换
                tCloud->points[i*lidardata.angle.size() + j].x = tCloud->points[i*lidardata.angle.size() + j].x * (cos(XAngle * PI / 180) + sin(YAngle * PI / 180));
                tCloud->points[i*lidardata.angle.size() + j].y = tCloud->points[i*lidardata.angle.size() + j].y * (cos(YAngle * PI / 180) + sin(XAngle * PI / 180));
                tCloud->points[i*lidardata.angle.size() + j].z = tCloud->points[i*lidardata.angle.size() + j].z;
                //点转换
                tCloud->points[i*lidardata.angle.size() + j].x = tCloud->points[i*lidardata.angle.size() + j].x + Base_X;
                tCloud->points[i*lidardata.angle.size() + j].y = tCloud->points[i*lidardata.angle.size() + j].y + Base_Y;
                tCloud->points[i*lidardata.angle.size() + j].z = tCloud->points[i*lidardata.angle.size() + j].z;
                //
                //网址输出

                //根据反射强度显示颜色
                if (lidardata.intensity[i][j] < 32)
                {
                    tCloud->points[i*lidardata.angle.size() + j].r = 0;
                    tCloud->points[i*lidardata.angle.size() + j].g = lidardata.intensity[i][j] * 8;
                    tCloud->points[i*lidardata.angle.size() + j].b = 255;
                }
                else if (lidardata.intensity[i][j] < 64 && lidardata.intensity[i][j] >= 32)
                {
                    tCloud->points[i*lidardata.angle.size() + j].r = 0;
                    tCloud->points[i*lidardata.angle.size() + j].g = 255;
                    tCloud->points[i*lidardata.angle.size() + j].b = 255 - (lidardata.intensity[i][j] - 32) * 4;
                }
                else if (lidardata.intensity[i][j] < 128 && lidardata.intensity[i][j] >= 64)
                {
                    tCloud->points[i*lidardata.angle.size() + j].r = 4 * lidardata.intensity[i][j] - 64;
                    tCloud->points[i*lidardata.angle.size() + j].g = 255;
                    tCloud->points[i*lidardata.angle.size() + j].b = 0;
                }
                else
                {
                    tCloud->points[i*lidardata.angle.size() + j].r = 255;
                    tCloud->points[i*lidardata.angle.size() + j].g = (255 - lidardata.intensity[i][j] - 128) * 2;
                    tCloud->points[i*lidardata.angle.size() + j].b = 0;
                }

            }
        }
    }

    emit send_lidarC16(tCloud);
}

void Maindeal::CalculateCoordinatesCH128X1(LidarDataCHXXX lidardata)
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr tCloud(new pcl::PointCloud<pcl::PointXYZRGB>);


    float sinTheta1[128];                                   //ÊúÖ±œÇ
    float sinTheta2[128];                                   //ÊúÖ±œÇ

    float cos_x_angle = cos(XAngle * PI / 180);
    float sin_x_angle = sin(XAngle * PI / 180);
    float cos_y_angle = cos(YAngle * PI / 180);
    float sin_y_angle = sin(YAngle * PI / 180);
    float cos_z_angle = cos(0 * PI / 180);
    float sin_z_angle = sin(0 * PI / 180);


    for(int i = 0; i < 128; i++)
    {
        sinTheta1[i] = sin(((i % 4) * (-0.17)) * PI / 180.f);
        sinTheta2[i] = sin(BigAngle[i / 4] * PI / 180.f);
        for(int j = 0; j < (int)lidardata.angle[i].size(); j++)
        {
            if(lidardata.angle[i][j] - int(lidardata.angle[i][j] / 180) * 180 >= 30 && lidardata.angle[i][j] - int(lidardata.angle[i][j] / 180) * 180 <= 150)
            {
                float sinTheta = sinTheta2[i] + 2 * cos((lidardata.angle[i][j] * PI / 180) / 2.0) *  sinTheta1[i];
                float cosTheta = sqrt(1 - sinTheta * sinTheta);
                float sinAngle = sin(lidardata.angle[i][j] * PI / 180.f);
                float cosAngle = cos(lidardata.angle[i][j] * PI / 180.f);
                if (lidardata.distance[i][j] < 0.3)
                {
                    continue;
                }
                pcl::PointXYZRGB PointTemp1;
                PointTemp1.y = (lidardata.distance[i][j] * cosTheta * sinAngle);
                PointTemp1.x = (lidardata.distance[i][j] * cosTheta * cosAngle);
                PointTemp1.z = (lidardata.distance[i][j] * sinTheta);

                //坐标轴方向转换
                float transformed_x = PointTemp1.x * cos_z_angle * cos_y_angle + PointTemp1.y * (-sin_z_angle * cos_x_angle + cos_z_angle * sin_y_angle * sin_x_angle) + PointTemp1.z * (sin_z_angle * sin_x_angle + cos_z_angle * sin_y_angle * cos_x_angle);
                float transformed_y = PointTemp1.x * sin_z_angle * cos_y_angle + PointTemp1.y * (cos_z_angle * cos_x_angle + sin_z_angle * sin_y_angle * sin_x_angle) + PointTemp1.z * (sin_z_angle * sin_y_angle * cos_x_angle - cos_z_angle * sin_x_angle);
                float transformed_z = (-sin_y_angle * PointTemp1.x + cos_y_angle * sin_x_angle * PointTemp1.y + cos_y_angle * cos_x_angle * PointTemp1.z);


                //点转换
                PointTemp1.x = transformed_x + Base_X;
                PointTemp1.y = transformed_y + Base_Y;
                PointTemp1.z = transformed_z;

                if (lidardata.intensity[i][j] <= 63)
                {
                    PointTemp1.r = 0;
                    PointTemp1.g = 254 - 4 * lidardata.intensity[i][j];
                    PointTemp1.b = 255;
                }
                else if (lidardata.intensity[i][j] > 63 && lidardata.intensity[i][j] <= 127)
                {
                    PointTemp1.r = 0;
                    PointTemp1.g = 4 * lidardata.intensity[i][j] - 254;
                    PointTemp1.b = 510 - 4 * lidardata.intensity[i][j];
                }
                else if (lidardata.intensity[i][j] > 127 && lidardata.intensity[i][j] <= 191)
                {
                    PointTemp1.r = 4 * lidardata.intensity[i][j] - 510;
                    PointTemp1.g = 255;
                    PointTemp1.b = 0;
                }
                else if (lidardata.intensity[i][j] > 191 && lidardata.intensity[i][j] <= 255)
                {
                    PointTemp1.r = 255;
                    PointTemp1.g = 1022 - 4 * lidardata.intensity[i][j];
                    PointTemp1.b = 0;
                }
                //PointTemp1.a = lidardata.intensity[i][j];
                tCloud->points.push_back(PointTemp1);
            }
        }
    }

    emit send_CH128X1(tCloud);

}

Maindeal::~Maindeal() {
}

PTZ* Maindeal::getPtz()
{
    return m_ptz;
}

Algonrithm* Maindeal::getAlgonrithm()
{
    return algonrithm;
}

LidarClustem* Maindeal::getLidarClustem()
{
    return lidarClustem;
}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr  Maindeal::getAllCloud()
{
    return allcloud;
}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr * Maindeal::getCluCloud()
{
    return Clu_cloud;
}

boost::shared_ptr<pcl::visualization::PCLVisualizer> Maindeal::getViewr()
{
    return this->viewer;
}

void Maindeal::getCalibAngle()
{
    float lidarA1 = 0;
    float lidarA2 = 0;
    float lidarA3 = 0;
    float lidarA4 = 0;

    float sinTheta_1[128];
    float sinTheta_2[128];
    float cosTheta_1[128];
    float cosTheta_2[128];
    float G_Angle[32] = {-17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4.125f, -4, -3.125f,
                         -3, -2.125f, -2, -1.125f, -1, -0.125f, 0, 0.875f, 1, 1.875f, 2, 3, 4, 5, 6, 7};
    float prismAngle[4];

    //创建socket
    int sock1 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    //定义地址
    struct sockaddr_in sockAddr1;
    sockAddr1.sin_family = AF_INET;
    sockAddr1.sin_port = htons(2369);
    sockAddr1.sin_addr.s_addr = inet_addr("192.168.1.102");
    int retVal1 = bind(sock1, (struct sockaddr *)&sockAddr1, sizeof(sockAddr1));
    unsigned int len1 = sizeof(sockaddr_in);
    //接收数据
    char recvBuf1[1206] = { 0 };
    //获取套接字接收内容
    int recvLen1 = recvfrom(sock1, recvBuf1, sizeof(recvBuf1), MSG_DONTWAIT, (struct sockaddr *)&sockAddr1, &len1);
    if (recvLen1 > 0 &&recvBuf1[0] == -91 && recvBuf1[1] == -1 && recvBuf1[2] == 0 && recvBuf1[3] == 90) //接收到数据
    {
        //处理接收的数据
        std::vector<unsigned char> data;
        for (int i = 0; i < 1200; i++)
        {
            data.push_back(recvBuf1[i]);	//只保留每包数据的前1200个字节，去掉尾部4个字节时间戳，2个字节参数
        }
        //设备包中储存的雷达4个垂直prsimAngle角度
        lidarA1 = (data[242] * 256 + data[243]) / 100.f;
        lidarA2 = (data[244] * 256 + data[245]) / 100.f;
        lidarA3 = (data[246] * 256 + data[247]) / 100.f;
        lidarA4 = (data[248] * 256 + data[249]) / 100.f;
        //角度转换
        lidarA1 = lidarA1 > 327.68 ? 327.68 - lidarA1 : lidarA1;
        lidarA2 = lidarA2 > 327.68 ? 327.68 - lidarA2 : lidarA2;
        lidarA3 = lidarA3 > 327.68 ? 327.68 - lidarA3 : lidarA3;
        lidarA4 = lidarA4 > 327.68 ? 327.68 - lidarA4 : lidarA4;
        std::cout << "lidarA1: " << lidarA1  << "lidarA2: " << lidarA2 << "lidarA3: " << lidarA3  << "lidarA4: " << lidarA4 << std::endl;
    }

    if(lidarA1 == 0 && lidarA2 == 0 && lidarA3 == 0 && lidarA4 == 0)
    {
        prismAngle[0] = 0;
        prismAngle[1] = -0.17;
        prismAngle[2] = -0.34;
        prismAngle[3] = -0.51;
    }
    else
    {
        prismAngle[0] = lidarA1;
        prismAngle[1] = lidarA2;
        prismAngle[2] = lidarA3;
        prismAngle[3] = lidarA4;
    }
    float sinAngles[19000] = { 0 };
    float cosAngles[19000] = { 0 };

    for (int i = 0; i < 19000; i++)
    {
        sinAngles[i] = sin(i * PI / 18000);
        cosAngles[i] = cos(i * PI / 18000);
    }

    for (int i = 0; i < 128; i++)
    {
        sinTheta_1[i] = sin(G_Angle[i / 4] * PI / 180.f);
        sinTheta_2[i] = sin((prismAngle[i % 4]) * PI / 180.f);
        cosTheta_1[i] = cos(G_Angle[ i / 4] * PI / 180.f);
        cosTheta_2[i] = cos((prismAngle[i % 4]) * PI / 180.f);
    }
}
