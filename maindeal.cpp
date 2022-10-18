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
