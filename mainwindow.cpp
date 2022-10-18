#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vtkRenderWindow.h>
#include <QDebug>
#include <QVector2D>
#include <qmath.h>
#include <pcl/surface/concave_hull.h>
#include <pcl/surface/convex_hull.h>
#include <QTimer>
#include <QDateTime>
#include <QDir>
#include "LED_RS232_API.h"
#include "LED_serverAPI.h"
#include <pcl/io/pcd_io.h>
#include <thread>
#include <QDebug>
#include <cstdlib>
#include <iostream>


int j;
int lastSize;
// TODO:WUZHENFENG20220406
// 该代码PTZ思路==由y确定m_ptz->war_angle，再由m_ptz->war_angle确定预置点num。
// 巡航路径由一系列预置点构成，预置点是保留当前画面云台的位姿。目前还不确定其Qt界面设置的预置点角度和距离在代码里面哪里应用到？
#define DB_INPUT_IMAGE_PATH (128)


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->ui->widgetTitle->setParentWidget(this);
    this->setWindowIcon(QIcon(":/images/leishen.ico"));
    ClustemSwitch = true;//三维聚类开关
    viewer_Cloud_id = 0;
    alarm_flag = 0;
    cruise_flag = 0;
    isShow = true;
    isTrick = false;
    isSendSms = true;
    getCalibAngle();
    //pushButton左图标右文字

    ui->pushButton->setIcon(QIcon(tr(":/images/leishen.ico"))); //给按钮添加图标
    ui->pushButton->setIconSize(QSize(26,26));//重置图标大小

    ui->pushButton_addlidar->setIcon(QIcon(tr(":/images/video.png")));
    ui->pushButton_addlidar->setIconSize(QSize(26,26));

    ui->pushButton_sms->setIcon(QIcon(tr(":/images/sms.png")));
    ui->pushButton_sms->setIconSize(QSize(26,26));

    viewer.reset (new pcl::visualization::PCLVisualizer ("viewer", false));

    ui->qvtkWidget->SetRenderWindow(viewer->getRenderWindow());

    viewer->setupInteractor(ui->qvtkWidget->GetInteractor(), ui->qvtkWidget->GetRenderWindow());

    ui->qvtkWidget->update();

    viewer->addCoordinateSystem(1.0);

    viewer->initCameraParameters();
    /*******设置按钮分组***********************************************************/
    view_Cluster_group =  new QButtonGroup();
    view_Area_group    =  new QButtonGroup();
    view_Cloud_group   =  new QButtonGroup();

    view_Cluster_group->setExclusive(true);
    view_Area_group->setExclusive(true);//设置互斥
    view_Cloud_group->setExclusive(true);

    view_Cluster_group->addButton(ui->radioButton_Cluster,0);
    view_Cluster_group->addButton(ui->radioButton_Cluster_none,1);
    ui->radioButton_Cluster->setChecked(1);

    view_Area_group->addButton(ui->radioButton_Area_2d,0);
    view_Area_group->addButton(ui->radioButton_Area_none,1);
    ui->radioButton_Area_2d->setChecked(1);


    view_Cloud_group->addButton(ui->radioButton_Cloud_all,0);
    view_Cloud_group->addButton(ui->radioButton_cloud_ob,1);
    view_Cloud_group->addButton(ui->radioButton_cloud_none,2);
    ui->radioButton_Cloud_all->setChecked(1);
    flagAllCloud = true;
    flagPartCloud = false;


    connect(view_Cluster_group,SIGNAL(buttonClicked(int)),this,SLOT(slot_view_Cluster_group(int)));
    connect(view_Area_group,SIGNAL(buttonClicked(int)),this,SLOT(slot_view_Area_group(int)));
    connect(view_Cloud_group,SIGNAL(buttonClicked(int)),this,SLOT(slot_view_Cloud_group(int)));
    connect(ui->widgetTitle,&MainTitleBar::sig_about_clicked,this,&MainWindow::showAbout);
    /*************************************************************************************************/
    //行人轨迹
    for(int i = 0;i < 255;i++)
    {
        Clu_cloud[i].reset(new pcl::PointCloud<pcl::PointXYZRGB>);
    }
    allcloud.reset(new pcl::PointCloud<pcl::PointXYZRGB>);
    saveDataFlag = 0;
    paintarea =new PaintArea();
    setROI = new SetROI();
    paintarea->scroll = setROI->scrollarea;
    setROI->scrollarea->takeWidget();
    setROI->scrollarea->setWidget(paintarea);

    connect(paintarea, SIGNAL(sigShowData()),this,SLOT(showData()));

    connect(setROI,SIGNAL(sigChangeArea_index(int)),paintarea,SLOT(UpdateArea_index(int)));
    connect(setROI,SIGNAL(sigaltablepaint()),this,SLOT(updatePainter2D()));


    fs =new FileSystem();
    qRegisterMetaType<Object>("Object");
    qRegisterMetaType<QString>("QString");


    lidarClustem = new LidarClustem;
    connect(lidarClustem, SIGNAL(SendClus_Object(QVariant)), this, SLOT(showClustem_Obj(QVariant)));

    addlidar =new AddLidar();
    connect(addlidar,SIGNAL(SendSet(SetData)),this,SLOT(addLidarSlot(SetData)));
    //摄像头
    m_ptz =new PTZ();
    ReadDevice();
    viewer->setCameraPosition(addlidar->data.pos_x, addlidar->data.pos_y, addlidar->data.pos_z,\
                              addlidar->data.view_x,addlidar->data.view_y,addlidar->data.view_z,\
                              addlidar->data.up_x, addlidar->data.up_y, addlidar->data.up_z);

    lidarClustem->setClusterTolerance(addlidar->data.clusterTolerance);
    lidarClustem->setMaxClusterSize(addlidar->data.maxClusterSize);
    lidarClustem->setMinClusterSize(addlidar->data.minClusterSize);

    m_ptz->PTZ_init();//该函数包含有回到预置点GOTO和开始巡航
    m_ptz->start();
    ui->textEdit->append(m_ptz->error);
    ui->textEdit->append(m_ptz->mas);
    showMovie();

    /*******界面按钮控制摄像头转动************************************************************************/
    connect(ui->toolButton_up,SIGNAL(pressed()),m_ptz,SLOT(OnButtonUpChanged()));
    connect(ui->toolButton_up,SIGNAL(released()),m_ptz,SLOT(OffButtonUpChanged()));
    connect(ui->toolButton_down,SIGNAL(pressed()),m_ptz,SLOT(OnButtonDownChanged()));
    connect(ui->toolButton_down,SIGNAL(released()),m_ptz,SLOT(OffButtonDownChanged()));
    connect(ui->toolButton_left,SIGNAL(pressed()),m_ptz,SLOT(OnButtonLeftChanged()));
    connect(ui->toolButton_left,SIGNAL(released()),m_ptz,SLOT(OffButtonLeftChanged()));
    connect(ui->toolButton_right,SIGNAL(pressed()),m_ptz,SLOT(OnButtonRightChanged()));
    connect(ui->toolButton_right,SIGNAL(released()),m_ptz,SLOT(OffButtonRightChanged()));

    connect(ui->toolButton,SIGNAL(pressed()),m_ptz,SLOT(OnButtonInChanged()));
    connect(ui->toolButton,SIGNAL(released()),m_ptz,SLOT(OffButtonInChanged()));
    connect(ui->toolButton_2,SIGNAL(pressed()),m_ptz,SLOT(OnButtonOutChanged()));
    connect(ui->toolButton_2,SIGNAL(released()),m_ptz,SLOT(OffButtonOutChanged()));


    connect(ui->toolButton_3,SIGNAL(pressed()),m_ptz,SLOT(OnButtonNearChanged()));
    connect(ui->toolButton_3,SIGNAL(released()),m_ptz,SLOT(OffButtonNearChanged()));
    connect(ui->toolButton_4,SIGNAL(pressed()),m_ptz,SLOT(OnButtonFarChanged()));
    connect(ui->toolButton_4,SIGNAL(released()),m_ptz,SLOT(OffButtonFarChanged()));

    connect(ui->toolButton_5,SIGNAL(pressed()),m_ptz,SLOT(OnButtonOpenChanged()));
    connect(ui->toolButton_5,SIGNAL(released()),m_ptz,SLOT(OffButtonOpenChanged()));
    connect(ui->toolButton_6,SIGNAL(pressed()),m_ptz,SLOT(OnButtonCloseChanged()));
    connect(ui->toolButton_6,SIGNAL(released()),m_ptz,SLOT(OffButtonCloseChanged()));
    /*******************************************************************************************************************/
    if("CH128X1" == addlidar->data.lidarModel)
    {
        qRegisterMetaType<struct LidarDataCHXXX>("struct LidarDataCHXXX");
        getCH128X1 = new GetlidarCH128X1(addlidar->data.lidarPort);
        connect(getCH128X1, SIGNAL(SendData(struct LidarDataCHXXX)), this, SLOT(CalculateCoordinatesCH128X1(struct LidarDataCHXXX)));
        getCH128X1->start();
    }
    else if("C16" == addlidar->data.lidarModel)
    {
        qRegisterMetaType<struct LidarData>("struct LidarData");
        getC16 = new GetlidarC16(addlidar->data.lidarPort);
        connect(getC16, SIGNAL(SendData(struct LidarData)), this, SLOT(CalculateCoordinates(struct LidarData)));
        getC16->start();
    }
    //防护区域内点云
    algonrithm =new Algonrithm(addlidar->data.resolution,addlidar->data.difference_threshold);
    connect(algonrithm,SIGNAL(sigShow(lidarIntruder)),this,SLOT(showFiltcloud(lidarIntruder)));


    ReadConfig();//读取配置文件参数并更新

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(scalePalyfram()));
    timer->start(10);

    // TODO:WUZHENFENG 20220407
    // 添加报警器服务端线程
    std::thread alarm_light_thread(StartAlarmLight);
    alarm_light_thread.detach();
    std::thread alarmIP_light_thread(StartAlarmLight_IP);
    alarmIP_light_thread.detach();

    saveMovie_timer=new QTimer(this);
    connect(saveMovie_timer,&QTimer::timeout,this,&MainWindow::onTimeout);

    sendSmsTimer = new QTimer(this);
    connect(sendSmsTimer,&QTimer::timeout,this,&MainWindow::do_sendSms);
    sendSmsStatus = false;

    if(0 == saveDataStatus)
    {
        ui->toolButton_savedata->setStyleSheet("border-image: url(:/images/OFF.png);");
    }
    if(0 == inAalarmLampStatus)
    {
        ui->toolButton_indoorlight->setStyleSheet("border-image: url(:/images/OFF.png);");
    }
    if(0 == outAalarmLampStatus)
    {
        ui->toolButton_Portlight->setStyleSheet("border-image: url(:/images/OFF.png);");
    }

    this->showMaximized();
    Creat_DataFileDir();// 启动先创建文件夹
    smsDialog = new SMSDialog(this);
    paboutDialog = new aboutDialog(this);
    Ali = new AliSmsAPIClient();
}

MainWindow::~MainWindow()
{
    if(saveMovie_timer->isActive())
    {
        saveMovie_timer->stop();
    }
    delete ui;
}


void MainWindow::Creat_DataFileDir()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString todayDate = currentTime.toString("yyyy-MM-dd");
    dataTime = new QTimer(this);
    connect(dataTime,&QTimer::timeout,this,&MainWindow::update_Time);
    dataTime->start(60000);
    CreateAndCheckPath();
}

bool MainWindow::CreateCheck(std::string& strPath)
{
    char cstrDir[DB_INPUT_IMAGE_PATH] = { 0 };
    strncpy(cstrDir, strPath.c_str(), sizeof(cstrDir) > strPath.size() ? strPath.size() : sizeof(cstrDir) - 1);
    size_t i = 2, nLen = strlen(cstrDir);
    for (; i < nLen; ++i) {
        if ('/' == cstrDir[i]) {
            cstrDir[i] = '\0';
            if (0 == opendir(cstrDir)) {
                if (-1 == mkdir(cstrDir, 0777))
                    return false;
            }
            cstrDir[i] = '/';
        }
    }
    return true;
}

bool MainWindow::CreateAndCheckPath()
{
    QString fileName = ".";
    QDateTime dateTime= QDateTime::currentDateTime();
    QString strTime = dateTime.toString("yyyy-MM-dd");
    m_movieFilePath = fileName.toStdString()+ "/"+"Data" + "/" + "Movie" + "/" +strTime.toStdString()+"/";
    if(!CreateCheck(m_movieFilePath)){
        qDebug()<<"Create movieFileDir failed:"<<QString::fromStdString(m_movieFilePath);
        return false;
    }
    m_cloudFilePath = fileName.toStdString()+ "/"+"Data" + "/" + "Cloud" + "/" +strTime.toStdString()+"/";
    if(!CreateCheck(m_cloudFilePath)){
        qDebug()<<"Create cloudFileDir failed:"<<QString::fromStdString(m_cloudFilePath);
        return false;
    }

    return true;
}

void MainWindow::update_Time()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QString currentDate = currentTime.toString("yyyy-MM-dd");
    if(todayDate != currentDate)
    {
        CreateAndCheckPath();
        todayDate = currentDate; // 更新今天的日期
    }
}

void MainWindow::onTimeout()
{
    static int saveTime = 10;
    static int saveFlag = 1;//视频保存标志，启动保存之后设置为0
    QDateTime dateTime= QDateTime::currentDateTime();
    QString strTime = dateTime.toString("yyyyMMddhhmmss");
    if(saveFlag)
    {
        QString filePathName = QString::fromStdString(m_movieFilePath) + strTime + ".mp4";
        saveFlag = 0;
     //   ui->textEdit->append(filePathName);
        if (!NET_DVR_SaveRealData(lRealPlayHandle, filePathName.toLatin1().data()))
        {
//            printf("保存到文件失败 错误码:, %d\n", NET_DVR_GetLastError());
            ui->textEdit->append(QString("保存到文件失败 错误码:, %1").arg(NET_DVR_GetLastError()));
        }
    }
    if(allcloud->points.size() > 0)
    {
        QString filePathName = QString::fromStdString(m_cloudFilePath) + strTime + ".pcd";
        pcl::io::savePCDFileBinary(filePathName.toStdString(),*allcloud);
        allcloud->points.clear();
        allcloud->clear();
    }
    saveTime--;
    if(0 == saveTime)
    {
        saveDataFlag = 0;
        saveTime = 10;
        saveFlag = 1;
        NET_DVR_StopSaveRealData(lRealPlayHandle); // 停止取流
        saveMovie_timer->stop();
    }
}

void MainWindow::do_sendSms()
{
    sendSmsTimer->stop();
}

//读取配置文件
void MainWindow::ReadConfig()
{
    fs->LoadFile(this);
    updatePainter2D();
    showData();
}


/*******************************************************************/
void MainWindow::on_pushButton_clicked()
{
    setROI->show();
    setROI->showMaximized();
}

void MainWindow::on_pushButton_addlidar_clicked()
{
    addlidar->show();
}

/****************************************************************************************/
//聚类开关
void MainWindow::slot_view_Cluster_group(int id)
{
    if(id == 0)
    {
        alarm_flag = 0;
        cruise_flag = 0;
        ClustemSwitch = true;
    }
    else if(id == 1)
    {
        viewer->removeAllShapes();
        ui->qvtkWidget->update();
        ClustemSwitch = false;
        LEDContrlAPI(0);
        LEDContrlAPI_IP(addlidar->data.ledIp.c_str(),0);
        if(cruise_flag == 0)
        {
            m_ptz->PTZ_Cruise_Open();
            cruise_flag = 1;
        }

        viewer->removeAllShapes();
    }
}
//区域图形显示模式
void MainWindow::slot_view_Area_group(int id)
{
    viewer_Area_id =id;
    drawArea();
    fs->SaveDataToFile(this);
}

//点云显示模式
void MainWindow::slot_view_Cloud_group(int id)
{
    if(id == 0)
    {
        flagAllCloud = true;
        flagPartCloud = false;
    }
    else
    {
        flagAllCloud = false;
        flagPartCloud = true;
    }

    viewer_Cloud_id =id;
    drawArea();
}

//参数显示
void MainWindow::addLidarSlot(SetData data)
{

    m_ptz->dist = data.setDis;
    m_ptz->ang = data.setAng;
    XAngle = data.setXAngle;
    YAngle = data.setYAngle;
    Base_X = data.setBase_X;
    Base_Y = data.setBase_Y;
    paintarea->Radius = data.setRadius;
    lidarClustem->setClusterTolerance(data.clusterTolerance);
    lidarClustem->setMaxClusterSize(data.maxClusterSize);
    lidarClustem->setMinClusterSize(data.minClusterSize);
    algonrithm->setResolution(data.resolution);
    algonrithm->setDifference_threshold(data.difference_threshold);

    WriteDevice(data);
}


/*********************点云显示**********************************/
//添加雷达安装角度与高度调整

void MainWindow::CalculateCoordinates(LidarData lidardata)
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

    algonrithm->tCloud->clear();
    *algonrithm->tCloud += *tCloud;
    algonrithm->start();
    algonrithm->wait();


    paintarea->tCloud->clear();
    *paintarea->tCloud  += *tCloud;
    paintarea->update();


    if(viewer_Cloud_id ==0)
    {
        std::string name ="All_cloud";
        viewer->removePointCloud(name);
        viewer->addPointCloud(tCloud,name);
        viewer->updatePointCloud(tCloud,name);
    }
    ui->qvtkWidget->update();

}

void MainWindow::getCalibAngle()
{
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

void MainWindow::CalculateCoordinatesCH128X1(LidarDataCHXXX lidardata)
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
    algonrithm->tCloud->clear();
    *algonrithm->tCloud += *tCloud;
    algonrithm->start();
    algonrithm->wait();


    paintarea->tCloud->clear();
    *paintarea->tCloud  += *tCloud;
    paintarea->update();
    if(1 == saveDataFlag)
    {
        *allcloud = *tCloud;
    }

    if(viewer_Cloud_id ==0)
    {
        std::string name ="All_cloud";
        viewer->removePointCloud(name);
        viewer->addPointCloud(tCloud,name);
        viewer->updatePointCloud(tCloud,name);
    }

    ui->qvtkWidget->update();
}

//防护区域内点云
void MainWindow::showFiltcloud(lidarIntruder intruder)
{
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr tCloud(new pcl::PointCloud<pcl::PointXYZRGB>);

    //二维绘制区域显示防护区域内点云
    tCloud->clear();
    *tCloud +=*intruder.tCloud;

    paintarea->xCloud->clear();
    *paintarea->xCloud += *intruder.tCloud;
    paintarea->update();

    if(viewer_Cloud_id ==1)
    {
        std::string name ="All_cloud";
        viewer->removePointCloud(name);
        viewer->addPointCloud(intruder.tCloud,name);
        viewer->updatePointCloud(intruder.tCloud,name);
    }

    //聚类
    if(tCloud->size()>0)
    {
        lidarClustem->lidar_points->clear();
        if (ClustemSwitch == true)
        {
            for (int i = 0; i < tCloud->size(); i++)
            {
                Cloud_Point point;
                point.x = tCloud->at(i).x;
                point.y = tCloud->at(i).y;
                point.z = tCloud->at(i).z;
                lidarClustem->lidar_points->push_back(point);
            }

            if (lidarClustem->m_stop == false)
            {
                lidarClustem->m_stop = true;
                lidarClustem->start();
                lidarClustem->wait();
            }
            cruise_flag = 0;
            start_time = std::chrono::system_clock::now();
        }
    }else if (cruise_flag == 0)
    {

        end_time = std::chrono::system_clock::now();
        auto count_time = std::chrono::duration_cast<std::chrono::milliseconds> (end_time - start_time ).count();
//        std::cout << "cruise_flag ==  " << cruise_flag << std::endl;
        if (count_time > 60000)
        {
            m_ptz->PTZ_Cruise_Open();
            cruise_flag = 1;
//            std::cout << "888882222count time milliseconds: " << count_time << std::endl;
        }
    }

}
/*****************************************************************************
函 数 名  : showClustem_Obj(Clustem_Obj Cl_obj)
功能描述  : sudo
输入参数  :
输出参数  :
返 回 值  :
*****************************************************************************/
void MainWindow::showClustem_Obj(QVariant DataVar)
{
    Clustem_Obj Cl_obj = DataVar.value<Clustem_Obj>();

    float minx = 999.0;
    int id = -1;
    ui->qvtkWidget->update();

    for(int i = 0;i <  lastSize ; i++)
    {
        std::string cube = "box" + std::to_string(i);
        viewer->removeShape(cube);
    }
    // TODO:20220407 根据聚类目标的个数来触发报警灯
    if(Cl_obj.Obj->size() > 0)
    {
        if(1 == saveDataStatus)
        {
            if(!saveMovie_timer->isActive())
            {
                saveMovie_timer->start(1000);
                saveDataFlag = 1;
            }
        }
        if(true == isSendSms)
        {
            if(!sendSmsTimer->isActive())
            {
                for (int i = 0; i < Cl_obj.Obj->size(); i++)
                {
                    pcl::PointXYZRGB point;
                    point.x = Cl_obj.Obj->at(i).x;
                    point.y = Cl_obj.Obj->at(i).y;
                    float dist = sqrt(point.x * point.x + point.y*point.y);
                    if(dist < smsDialog->getWarningDistance())
                    {
                        int time = smsDialog->getSmsTimeInterval();
                        sendSmsTimer->start(60*1000*time);
                        sendSmsStatus = true;
                    }

                }

            }
            if(true == sendSmsStatus)
            {
                sendSmsStatus = false;
                std::vector<std::string> numberList = smsDialog->getSmsNumbers();
                if(1 == numberList.size())
                {
                    Ali->SendSMS(numberList[0],"1号港");
                }
                else
                {
                    Ali->SendSMSList(numberList,"1号港");
                }
            }
        }
    }

    if(Cl_obj.Obj->size() == 0)
    {
        std::cout << "========ALARM OFF ============" << std::endl;
        alarm_flag = 0;
        LEDContrlAPI(alarm_flag);
        LEDContrlAPI_IP(addlidar->data.ledIp.c_str(),alarm_flag);
        for(int i =0; i < 255; i++)
        {
            Clu_cloud[i]->clear();
        }
    }
    else if(alarm_flag == 0)
    {
        alarm_flag = 1;
        if(1 == inAalarmLampStatus)
        {
            LEDContrlAPI(alarm_flag);
        }

        if(1 == outAalarmLampStatus)
        {
            LEDContrlAPI_IP(addlidar->data.ledIp.c_str(),alarm_flag);
        }
        std::cout << "========ALARM ON **************" << std::endl;
    }
    if(0 == inAalarmLampStatus||0 == outAalarmLampStatus)
    {
        alarm_flag = 0;
    }

    for(int i =0; i < 255; i++)
    {
        std::string ball =  QString("ball%1").arg(i).toStdString();
        viewer->removePointCloud(ball);
        ui->qvtkWidget->update();
    }

    for (int i = 0; i < Cl_obj.Obj->size(); i++)
    {
        pcl::PointXYZRGB point;

        point.x = Cl_obj.Obj->at(i).x;
        point.y = Cl_obj.Obj->at(i).y;
        point.z = Cl_obj.Obj->at(i).z;
        point.r = 0;
        point.g = 255;
        point.b = 0;
        if(Clu_cloud[Cl_obj.Obj->at(i).ID]->size() > 10)
        {

            Clu_cloud[Cl_obj.Obj->at(i).ID]->erase( Clu_cloud[Cl_obj.Obj->at(i).ID]->begin(), Clu_cloud[Cl_obj.Obj->at(i).ID]->begin()+5);

        }

        if(Clu_cloud[Cl_obj.Obj->at(i).ID]->size() > 30)
        {

            Clu_cloud[Cl_obj.Obj->at(i).ID]->erase( Clu_cloud[Cl_obj.Obj->at(i).ID]->begin(), Clu_cloud[Cl_obj.Obj->at(i).ID]->begin()+20);

        }


        if(isTrick == true)
        {
            Clu_cloud[Cl_obj.Obj->at(i).ID]->push_back(point);

            std::string ball =  QString("ball%1").arg(Cl_obj.Obj->at(i).ID).toStdString();


            viewer->removePointCloud(ball);
            viewer->addPointCloud(Clu_cloud[Cl_obj.Obj->at(i).ID],ball);
            //viewer->addPointCloud(Clu.at(Cl_obj.Obj->at(i).ID),ball);
            viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE,4,ball);
            viewer->updatePointCloud(Clu_cloud[Cl_obj.Obj->at(i).ID],ball);
        }

        std::string cube = "box" + std::to_string(i);
        viewer->addCube(Cl_obj.Obj->at(i).xmin, Cl_obj.Obj->at(i).xmax, Cl_obj.Obj->at(i).ymin, Cl_obj.Obj->at(i).ymax, Cl_obj.Obj->at(i).zmin, Cl_obj.Obj->at(i).zmax, 0, 255, 0,cube);
        viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_REPRESENTATION, pcl::visualization::PCL_VISUALIZER_REPRESENTATION_SURFACE, cube);
        viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 0, 1, 0, cube);
        viewer->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_OPACITY, 0.4, cube);
        if (minx > fabs(sqrt(Cl_obj.Obj->at(i).x * Cl_obj.Obj->at(i).x + Cl_obj.Obj->at(i).y * Cl_obj.Obj->at(i).y)))//平方根
        {
            minx = fabs(sqrt(Cl_obj.Obj->at(i).x * Cl_obj.Obj->at(i).x + Cl_obj.Obj->at(i).y * Cl_obj.Obj->at(i).y));
            id = i;
        }
    }
    ui->qvtkWidget->update();
    lastSize = Cl_obj.Obj->size();

    if ( id > -1 )
    {
        SearchIntruder(Cl_obj.Obj->at(id));
    }
}


// TODO:此部分可以雷达和相机联动可以修改一下逻辑，
// 比如：障碍物目标中心点的向量求水平角和方位角，
// 再根据雷达的水平垂直视野范围进行栅格化处理定位调整相机云台位姿
// 此部分将障碍物传到摄像头
void MainWindow::SearchIntruder(Object obj)
{

    pcl::PointXYZRGB point;
    point.x = obj.x;
    point.y = obj.y;
    point.z = obj.z;
    float r = sqrt(point.x*point.x + point.y*point.y);//平方根,距离原点距离
    float horizontal = atan(obj.x / obj.y) / PI * 180;
    float azimuth = atan(obj.z / obj.y) /  PI * 180;
    m_ptz->war_horizontal = horizontal;
    m_ptz->war_azimuth = azimuth;
    m_ptz->war_dist = r;

}

/*****************************************************************************
函 数 名  : addcuboid(Object obj,int id)
功能描述  : 添加矩形框
输入参数  :
输出参数  :
返 回 值  :
*****************************************************************************/
void MainWindow::addcuboid(Object obj, int id)
{
    pcl::PointXYZ p1, p2, p3, p4, p5, p6, p7, p8;
    const std::string line1 = QString("line1%1").arg(id).toStdString();
    const std::string line2 = QString("line2%1").arg(id).toStdString();
    const std::string line3 = QString("line3%1").arg(id).toStdString();
    const std::string line4 = QString("line4%1").arg(id).toStdString();
    const std::string line5 = QString("line5%1").arg(id).toStdString();
    const std::string line6 = QString("line6%1").arg(id).toStdString();
    const std::string line7 = QString("line7%1").arg(id).toStdString();
    const std::string line8 = QString("line8%1").arg(id).toStdString();
    const std::string line9 = QString("line9%1").arg(id).toStdString();
    const std::string line10 = QString("line10%1").arg(id).toStdString();
    const std::string line11 = QString("line11%1").arg(id).toStdString();
    const std::string line12 = QString("line12%1").arg(id).toStdString();

    p1.x = obj.x - obj.length / 2;
    p1.y = obj.y + obj.width / 2;
    p1.z = obj.z + obj.height / 2;

    p2.x = obj.x + obj.length / 2;
    p2.y = obj.y + obj.width / 2;
    p2.z = obj.z + obj.height / 2;

    p3.x = obj.x + obj.length / 2;
    p3.y = obj.y - obj.width / 2;
    p3.z = obj.z + obj.height / 2;

    p4.x = obj.x - obj.length / 2;
    p4.y = obj.y - obj.width / 2;
    p4.z = obj.z + obj.height / 2;

    p5.x = obj.x - obj.length / 2;
    p5.y = obj.y + obj.width / 2;
    p5.z = obj.z - obj.height / 2;

    p6.x = obj.x + obj.length / 2;
    p6.y = obj.y + obj.width / 2;
    p6.z = obj.z - obj.height / 2;

    p7.x = obj.x + obj.length / 2;
    p7.y = obj.y - obj.width / 2;
    p7.z = obj.z - obj.height / 2;

    p8.x = obj.x - obj.length / 2;
    p8.y = obj.y - obj.width / 2;
    p8.z = obj.z - obj.height / 2;

    viewer->addLine(p1, p2, 0, 1, 0, line1);
    viewer->addLine(p2, p3, 0, 1, 0, line2);
    viewer->addLine(p3, p4, 0, 1, 0, line3);
    viewer->addLine(p1, p4, 0, 1, 0, line4);

    viewer->addLine(p5, p6, 0, 1, 0, line5);
    viewer->addLine(p6, p7, 0, 1, 0, line6);
    viewer->addLine(p7, p8, 0, 1, 0, line7);
    viewer->addLine(p8, p5, 0, 1, 0, line8);

    viewer->addLine(p1, p5, 0, 1, 0, line9);
    viewer->addLine(p2, p6, 0, 1, 0, line10);
    viewer->addLine(p3, p7, 0, 1, 0, line11);
    viewer->addLine(p4, p8, 0, 1, 0, line12);
}



/*******************************二维绘制图形*************************************************/
void MainWindow::drawArea()
{
    viewer->removeAllShapes();
    if(viewer_Area_id ==0)
    {
        for(int index=0;index<3;index++)
        {
            for(int i = 0; i < paintarea->Area2d_point[index].size()-1; i++)
            {
                char buffer[20];
                sprintf(buffer,"2Darea_%d_%d",index,i);
                std::string name =buffer;
                viewer->addLine<pcl::PointXYZRGB> (paintarea->Area2d_point[index][i],paintarea->Area2d_point[index][i+1],255,0,0,name);
                ui->qvtkWidget->update();
            }
        }
    }
    else
    {

    }
    ui->qvtkWidget->update();
}



//绘制2D防护区域
//
void MainWindow::draw2DArea(int idx)
{
    int r,g,b;
    if(idx<5)
    {
        r =255 -30*idx;
        g=0;b=0;

    }
    else if(idx>=5 &&idx<10)
    {
        r=255;
        g=255;b=0;
    }
    else
    {
        r=255;
        g=0;b=255;
    }

}


void MainWindow::showData()
{

    ListtoConvex();
    for(int i=0;i<AREAS;i++)
    {
        setROI->area[i].Area_height_down = paintarea->area[i].Area_height_down;
        setROI->area[i].Area_height_top = paintarea->area[i].Area_height_top;
        setROI->area[i].Area2D_point.clear(); setROI->area[i].Area2D_point.append(paintarea->area[i].Area2D_point);
        setROI->area[i].Area2D_point_T.clear();setROI->area[i].Area2D_point_T.append(paintarea->area[i].Area2D_point_T);
    }

    setROI->showPoint();
    fs->SaveDataToFile(this);
}

void MainWindow::ListtoConvex()
{
    int r,g,b;
    pcl::PointXYZRGB pt;
    QPointF pf;
    float x, y;
    viewer->removeAllShapes();
    for(int index=0;index<3;index++)
    {
        paintarea->Area2d_point[index].clear();
        search_max_min(paintarea->area[index].Area2D_point_T);
        for (int i = 0; i < paintarea->area[index].Area2D_point_T.size(); i++)
        {
            pt.x = paintarea->area[index].Area2D_point_T[i].x;
            pt.y = paintarea->area[index].Area2D_point_T[i].y;
            paintarea->Area2d_point[index].push_back(pt);
        }
        if(paintarea->area[index].Area2D_point_T.size()!= 0)
        {
            pt.x = paintarea->area[index].Area2D_point_T[0].x;
            pt.y = paintarea->area[index].Area2D_point_T[0].y;
            paintarea->Area2d_point[index].push_back(pt);
        }

        r=255;
        g=0;
        b=0;
        for(int i = 0; i < paintarea->Area2d_point[index].size()-1; i++)
        {
            char buffer[20];
            sprintf(buffer,"2Darea_%d_%d",index,i);

            std::string name =buffer;
            viewer->addLine<pcl::PointXYZRGB> (paintarea->Area2d_point[index][i],paintarea->Area2d_point[index][i+1],r,g,b,name);
            ui->qvtkWidget->update();
        }

    }

}


//计算最大最小
void MainWindow::search_max_min(QList<pcl::PointXYZRGB> box)
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

void MainWindow::quickSort(float s[], int l, int r)
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



void MainWindow::updatePainter2D()
{

    float msx = PAINT_SIZE/2/paintarea->LidarInstance.lidar_Radius;
    float msy = PAINT_SIZE/2/paintarea->LidarInstance.lidar_Radius;
    for(int index =0;index<3;index++)
    {

        setROI->area[index].Area2D_point.clear();

        for(int i = 0;i < setROI->area[index].Area2D_point_T.size();i++)
        {
            qreal x = setROI->area[index].Area2D_point_T[i].x*msx;
            qreal y = setROI->area[index].Area2D_point_T[i].y/(-1.0)*msy;
            pcl::PointXYZRGB point;
            point.x =x;
            point.y=y;
            setROI->area[index].Area2D_point.push_back(point);
        }
        paintarea->area[index].Area2D_point_T= setROI->area[index].Area2D_point_T;
        paintarea->area[index].Area2D_point= setROI->area[index].Area2D_point;
        paintarea->area[index].Area_height_down =setROI->area[index].Area_height_down;
        paintarea->area[index].Area_height_top = setROI->area[index].Area_height_top;

        algonrithm->area[index].Area2D_point_T= setROI->area[index].Area2D_point_T;
        algonrithm->area[index].Area2D_point= setROI->area[index].Area2D_point;
        algonrithm->area[index].Area_height_down =setROI->area[index].Area_height_down;
        algonrithm->area[index].Area_height_top = setROI->area[index].Area_height_top;
    }
    fs->SaveDataToFile(this);
    paintarea->update();
}



/********************************摄像头***********************************************/
void MainWindow::showMovie()
{
    HWND hwnd = (HWND)ui->frame->winId();

    NET_DVR_PREVIEWINFO struPlayInfo = {0};

    // struPlayInfo.hPlayWnd = hwnd;
    //  struPlayInfo.hPlayWnd = (HWND)palyfram->winId();

    struPlayInfo.hPlayWnd = hwnd;

    struPlayInfo.lChannel     = 1;       //预览通道号
    struPlayInfo.dwStreamType = 0;       //0-主码流，1-子码流，2-码流3，3-码流4，以此类推
    struPlayInfo.dwLinkMode   = 0;       //0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP
    struPlayInfo.bBlocked     = 0;       //0- 非阻塞取流，1- 阻塞取流

    lRealPlayHandle = NET_DVR_RealPlay_V40(m_ptz->lUserID, &struPlayInfo, NULL, NULL);
    QString  message1=QString("lrealpal %1").arg(lRealPlayHandle);
    QString  message2=QString("error = %1").arg(NET_DVR_GetLastError());
    ui->textEdit->append(message1);
    ui->textEdit->append(message2);
    //    NET_DVR_SetLogToFile(1,"/home/ls/work3/ls_safe/build");

    if (lRealPlayHandle < 0)
    {
        NET_DVR_Logout(m_ptz->lUserID);
        NET_DVR_Cleanup();
    }
//    if (!NET_DVR_SaveRealData(lRealPlayHandle, (char *)"./test.mp4")) {
//           printf("保存到文件失败 错误码:, %d\n", NET_DVR_GetLastError());
//       }
//       printf("保存到文件test.mp4\n");
//    sleep(5); // 取流时间长度 秒
//    NET_DVR_StopRealPlay(lRealPlayHandle); // 停止取流

}

void MainWindow::scalePalyfram()//窗口大小改变要调用该函数
{
    bool ret = NET_DVR_ChangeWndResolution(lRealPlayHandle);
}

void MainWindow::ReadDevice()
{
    QSettings config("device.ini",QSettings::IniFormat);

    m_ptz->cam_IP = config.value(QString("camera/IP")).toString();
    m_ptz->cam_ID = config.value(QString("camera/ID")).toString();
    m_ptz->cam_Pass = config.value(QString("camera/Pass")).toString();


    m_ptz->dist = config.value(QString("preset/Dis")).toFloat();
    m_ptz->ang = config.value(QString("preset/Ang")).toFloat();
    XAngle = config.value(QString("preset/XAngle")).toFloat();
    YAngle = config.value(QString("preset/YAngle")).toFloat();
    Base_X = config.value(QString("preset/Base_X")).toFloat();
    Base_Y = config.value(QString("preset/Base_Y")).toFloat();
    paintarea->Radius = config.value(QString("preset/Radius")).toFloat();
    saveDataStatus = config.value(QString("other/SaveDataStatus")).toInt();
    inAalarmLampStatus = config.value(QString("other/InAalarmLampStatus")).toInt();
    outAalarmLampStatus = config.value(QString("other/OutAalarmLampStatus")).toInt();
    addlidar->data.setDis =  m_ptz->dist;
    addlidar->data.setAng = m_ptz->ang;
    addlidar->data.setXAngle = XAngle;
    addlidar->data.setYAngle = YAngle;
    addlidar->data.setBase_X = Base_X;
    addlidar->data.setBase_Y = Base_Y;
    addlidar->data.setRadius = paintarea->Radius;
    addlidar->data.clusterTolerance = config.value(QString("Cluster/ClusterTolerance")).toFloat();
    addlidar->data.minClusterSize = config.value(QString("Cluster/MinClusterSize")).toFloat();
    addlidar->data.maxClusterSize = config.value(QString("Cluster/MaxClusterSize")).toFloat();
    addlidar->data.resolution = config.value(QString("Cluster/Resolution")).toFloat();
    addlidar->data.difference_threshold = config.value(QString("Cluster/Difference_threshold")).toFloat();
    addlidar->data.lidarModel = config.value(QStringLiteral("Lidar/LidarModel")).toString();
    addlidar->data.pos_x = config.value(QStringLiteral("Lidar/Pos_X")).toFloat();
    addlidar->data.pos_y = config.value(QStringLiteral("Lidar/Pos_Y")).toFloat();
    addlidar->data.pos_z = config.value(QStringLiteral("Lidar/Pos_Z")).toFloat();
    addlidar->data.view_x = config.value(QStringLiteral("Lidar/View_X")).toFloat();
    addlidar->data.view_y = config.value(QStringLiteral("Lidar/View_Y")).toFloat();
    addlidar->data.view_z = config.value(QStringLiteral("Lidar/View_Z")).toFloat();
    addlidar->data.up_x = config.value(QStringLiteral("Lidar/Up_X")).toFloat();
    addlidar->data.up_y = config.value(QStringLiteral("Lidar/Up_Y")).toFloat();
    addlidar->data.up_z = config.value(QStringLiteral("Lidar/Up_Z")).toFloat();
    addlidar->data.ledIp = config.value(QStringLiteral("Lidar/LedIP")).toString().toStdString();
    addlidar->data.lidarPort = config.value(QStringLiteral("Lidar/LidarPort")).toInt();


    addlidar->ShowData();


}

void MainWindow::WriteDevice(SetData data)
{
    QSettings config("device.ini",QSettings::IniFormat);
    qDebug("writedevice");
    config.beginGroup(QString("camera"));
    config.setValue("IP",m_ptz->cam_IP);
    config.setValue("ID",m_ptz->cam_ID);
    config.setValue("Pass",m_ptz->cam_Pass);
    config.endGroup();

    config.beginGroup(QString("preset"));
    config.setValue("Dis", QString("%1").arg(data.setDis));
    config.setValue("Ang", QString("%1").arg(data.setAng));
    config.setValue("XAngle", QString("%1").arg(data.setXAngle));
    config.setValue("YAngle", QString("%1").arg(data.setYAngle));
    config.setValue("Base_X", QString("%1").arg(data.setBase_X));
    config.setValue("Base_Y", QString("%1").arg(data.setBase_Y));
    config.setValue("Radius", QString("%1").arg(data.setRadius));
    config.endGroup();
    config.beginGroup(QString("Cluster"));

    config.setValue("ClusterTolerance", QString("%1").arg(data.clusterTolerance));
    config.setValue("MinClusterSize", QString("%1").arg(data.minClusterSize));
    config.setValue("MaxClusterSize", QString("%1").arg(data.maxClusterSize));
    config.setValue("Resolution", QString("%1").arg(data.resolution));
    config.setValue("Difference_threshold", QString("%1").arg(data.difference_threshold));
    config.endGroup();
    config.beginGroup(QString("Lidar"));
    config.setValue("LidarModel",data.lidarModel);
    config.setValue("Pos_X",QString("%1").arg(data.pos_x));
    config.setValue("Pos_Y",QString("%1").arg(data.pos_y));
    config.setValue("Pos_Z",QString("%1").arg(data.pos_z));
    config.setValue("View_X",QString("%1").arg(data.view_x));
    config.setValue("View_Y",QString("%1").arg(data.view_y));
    config.setValue("View_Z",QString("%1").arg(data.view_z));
    config.setValue("Up_X",QString("%1").arg(data.up_x));
    config.setValue("Up_Y",QString("%1").arg(data.up_y));
    config.setValue("Up_Z",QString("%1").arg(data.up_z));
    config.setValue("LedIP",QString::fromStdString(data.ledIp));
    config.setValue("LidarPort",QString("%1").arg(data.lidarPort));

    config.endGroup();
}

void MainWindow::on_toolButton_7_clicked()
{
    if(m_ptz->isRun == true)
    {
        ui->toolButton_7->setStyleSheet("border-image: url(:/images/OFF.png);");
        m_ptz->isRun = false;
    }
    else if(m_ptz->isRun == false)
    {
        ui->toolButton_7->setStyleSheet("border-image: url(:/images/ON.png);");
        m_ptz->isRun = true;
    }

}

void MainWindow::on_toolButton_savedata_clicked()
{
    QSettings config("device.ini",QSettings::IniFormat);
    config.beginGroup(QString("other"));

    if(1 == saveDataStatus)
    {
        ui->toolButton_savedata->setStyleSheet("border-image: url(:/images/OFF.png);");
        saveDataStatus = 0;
    }
    else if(0 == saveDataStatus)
    {
        ui->toolButton_savedata->setStyleSheet("border-image: url(:/images/ON.png);");
        saveDataStatus = 1;
    }
    config.setValue("SaveDataStatus",saveDataStatus);
    config.endGroup();
}

void MainWindow::on_toolButton_Portlight_clicked()
{
    QSettings config("device.ini",QSettings::IniFormat);
    config.beginGroup(QString("other"));

    if(1 == outAalarmLampStatus)
    {
        ui->toolButton_Portlight->setStyleSheet("border-image: url(:/images/OFF.png);");
        outAalarmLampStatus = 0;
        LEDContrlAPI_IP(addlidar->data.ledIp.c_str(),0);
    }
    else if(0 == outAalarmLampStatus)
    {
        ui->toolButton_Portlight->setStyleSheet("border-image: url(:/images/ON.png);");
        outAalarmLampStatus = 1;
    }
    config.setValue("OutAalarmLampStatus",outAalarmLampStatus);
    config.endGroup();
}

void MainWindow::on_toolButton_indoorlight_clicked()
{
    QSettings config("device.ini",QSettings::IniFormat);
    config.beginGroup(QString("other"));
    if(1 == inAalarmLampStatus)
    {
        ui->toolButton_indoorlight->setStyleSheet("border-image: url(:/images/OFF.png);");
        inAalarmLampStatus = 0;
        LEDContrlAPI(0);
    }
    else if(0 == inAalarmLampStatus)
    {
        ui->toolButton_indoorlight->setStyleSheet("border-image: url(:/images/ON.png);");
        inAalarmLampStatus = 1;
    }
    config.setValue("InAalarmLampStatus",inAalarmLampStatus);
    config.endGroup();

}

void MainWindow::on_toolButton_actionOpengrid_clicked()
{
    if (isShow == true)
    {
        ui->toolButton_actionOpengrid->setStyleSheet("border-image: url(:/images/OFF.png);");
        isShow = false;
        viewer->removeAllShapes();


        ui->qvtkWidget->update();
    }
    else if (isShow == false)
    {
        ui->toolButton_actionOpengrid->setStyleSheet("border-image: url(:/images/ON.png);");
        isShow = true;
        for (int i = -200; i < 210; i = i + 10)
        {
            viewer->addLine(pcl::PointXYZ(i,0,0), pcl::PointXYZ(i,200,0), 150, 150, 150, "Line_x" + std::to_string(i));
            viewer->setShapeRenderingProperties(1, 0.2, "Line_x" + std::to_string(i));
        }
        for (int i = 0; i < 210; i = i + 10)
        {
            viewer->addLine(pcl::PointXYZ(-200,i,0), pcl::PointXYZ(200,i,0), 150, 150, 150, "Line_y" + std::to_string(i));
            viewer->setShapeRenderingProperties(1, 0.2, "Line_y" + std::to_string(i));
        }

        viewer->addLine(pcl::PointXYZ(0,0,0), pcl::PointXYZ(-200,115,0), 150, 150, 150, "Lineleft" );
        viewer->setShapeRenderingProperties(1, 0.4, "Lineleft");
        viewer->addLine(pcl::PointXYZ(0,0,0), pcl::PointXYZ(200,115,0), 150, 150, 150, "Lineright" );
        viewer->setShapeRenderingProperties(1, 0.4, "Lineright");
        ui->qvtkWidget->update();
    }
}

void MainWindow::on_toolButton_actionTrick_clicked()
{
    if(isTrick == true)
    {
        ui->toolButton_actionTrick->setStyleSheet("border-image: url(:/images/OFF.png);");
        isTrick = false;
    }
    else if(isTrick == false)
    {
        ui->toolButton_actionTrick->setStyleSheet("border-image: url(:/images/ON.png);");
        isTrick = true;
    }
}

void MainWindow::on_pushButton_sms_clicked()
{
    smsDialog->show();
}

void MainWindow::on_toolButton_sms_clicked()
{
    if(isSendSms == true)
    {
        ui->toolButton_sms->setStyleSheet("border-image: url(:/images/OFF.png);");
        isSendSms = false;
    }
    else if(isSendSms == false)
    {
        ui->toolButton_sms->setStyleSheet("border-image: url(:/images/ON.png);");
        isSendSms = true;
    }
}

void MainWindow::showAbout()
{
    paboutDialog->show();
}
