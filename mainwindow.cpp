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
    initUi();

    fs =new FileSystem();
    Ali = new AliSmsAPIClient();
    maindeal = new Maindeal(addlidar);

    timer = new QTimer(this);
    saveMovie_timer=new QTimer(this);
    sendSmsTimer = new QTimer(this);

    Creat_DataFileDir();// 启动先创建文件夹
    ReadDevice();


    qRegisterMetaType<Object>("Object");
    qRegisterMetaType<QString>("QString");
    //////////////////////////////////////////////////


    flagAllCloud = true;
    flagPartCloud = false;

    ClustemSwitch = true;//三维聚类开关
    viewer_Cloud_id = 0;
    alarm_flag = 0;
    cruise_flag = 0;
    isShow = true;
    isTrick = false;
    isSendSms = true;
    sendSmsStatus = false;

    initPointCShow();
    initCameraShow();
    ReadConfig();//读取配置文件参数并更新
    initControlPanel();
    initConnect();

    timer->start(10);
    this->showMaximized();

}

MainWindow::~MainWindow()
{
    if(saveMovie_timer->isActive())
    {
        saveMovie_timer->stop();
    }
    delete ui;
}

void MainWindow::initPointCShow()
{
    ui->qvtkWidget->SetRenderWindow(this->maindeal->getViewr()->getRenderWindow());
    this->maindeal->getViewr()->setupInteractor(ui->qvtkWidget->GetInteractor(), ui->qvtkWidget->GetRenderWindow());
    ui->qvtkWidget->update();
    this->maindeal->getViewr()->addCoordinateSystem(1.0);
    this->maindeal->getViewr()->initCameraParameters();
}

void MainWindow::initCameraShow()
{
    //摄像头

    this->maindeal->getViewr()->setCameraPosition(addlidar->data.pos_x, addlidar->data.pos_y, addlidar->data.pos_z,\
                              addlidar->data.view_x,addlidar->data.view_y,addlidar->data.view_z,\
                              addlidar->data.up_x, addlidar->data.up_y, addlidar->data.up_z);

    this->maindeal->getLidarClustem()->setClusterTolerance(addlidar->data.clusterTolerance);
    this->maindeal->getLidarClustem()->setMaxClusterSize(addlidar->data.maxClusterSize);
    this->maindeal->getLidarClustem()->setMinClusterSize(addlidar->data.minClusterSize);

    this->maindeal->getPtz()->PTZ_init();//该函数包含有回到预置点GOTO和开始巡航
    this->maindeal->getPtz()->start();
    ui->textEdit->append(this->maindeal->getPtz()->error);
    ui->textEdit->append(this->maindeal->getPtz()->mas);

    showMovie();
}


void MainWindow::initControlPanel()
{
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
}

void MainWindow::initUi()
{
    setROI = new SetROI();
    addlidar =new AddLidar();
    paintarea =new PaintArea();
    smsDialog = new SMSDialog(this);
    paboutDialog = new aboutDialog(this);

    view_Cluster_group =  new QButtonGroup();
    view_Area_group    =  new QButtonGroup();
    view_Cloud_group   =  new QButtonGroup();

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->ui->widgetTitle->setParentWidget(this);
    this->setWindowIcon(QIcon(":/images/leishen.ico"));

    ui->pushButton->setIcon(QIcon(tr(":/images/leishen.ico"))); //给按钮添加图标
    ui->pushButton->setIconSize(QSize(26,26));//重置图标大小

    ui->pushButton_addlidar->setIcon(QIcon(tr(":/images/video.png")));
    ui->pushButton_addlidar->setIconSize(QSize(26,26));

    ui->pushButton_sms->setIcon(QIcon(tr(":/images/sms.png")));
    ui->pushButton_sms->setIconSize(QSize(26,26));

    /*******设置按钮分组***********************************************************/

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

    paintarea->scroll = setROI->scrollarea;
    setROI->scrollarea->takeWidget();
    setROI->scrollarea->setWidget(paintarea);

}

void MainWindow::initConnect()
{
    connect(view_Cluster_group,SIGNAL(buttonClicked(int)),this,SLOT(slot_view_Cluster_group(int)));
    connect(view_Area_group,SIGNAL(buttonClicked(int)),this,SLOT(slot_view_Area_group(int)));
    connect(view_Cloud_group,SIGNAL(buttonClicked(int)),this,SLOT(slot_view_Cloud_group(int)));
    connect(ui->widgetTitle,&MainTitleBar::sig_about_clicked,this,&MainWindow::showAbout);
    /*************************************************************************************************/

    /*******界面按钮控制摄像头转动************************************************************************/
    connect(ui->toolButton_up,SIGNAL(pressed()),this->maindeal->getPtz(),SLOT(OnButtonUpChanged()));
    connect(ui->toolButton_up,SIGNAL(released()),this->maindeal->getPtz(),SLOT(OffButtonUpChanged()));
    connect(ui->toolButton_down,SIGNAL(pressed()),this->maindeal->getPtz(),SLOT(OnButtonDownChanged()));
    connect(ui->toolButton_down,SIGNAL(released()),this->maindeal->getPtz(),SLOT(OffButtonDownChanged()));
    connect(ui->toolButton_left,SIGNAL(pressed()),this->maindeal->getPtz(),SLOT(OnButtonLeftChanged()));
    connect(ui->toolButton_left,SIGNAL(released()),this->maindeal->getPtz(),SLOT(OffButtonLeftChanged()));
    connect(ui->toolButton_right,SIGNAL(pressed()),this->maindeal->getPtz(),SLOT(OnButtonRightChanged()));
    connect(ui->toolButton_right,SIGNAL(released()),this->maindeal->getPtz(),SLOT(OffButtonRightChanged()));

    connect(ui->toolButton,SIGNAL(pressed()),this->maindeal->getPtz(),SLOT(OnButtonInChanged()));
    connect(ui->toolButton,SIGNAL(released()),this->maindeal->getPtz(),SLOT(OffButtonInChanged()));
    connect(ui->toolButton_2,SIGNAL(pressed()),this->maindeal->getPtz(),SLOT(OnButtonOutChanged()));
    connect(ui->toolButton_2,SIGNAL(released()),this->maindeal->getPtz(),SLOT(OffButtonOutChanged()));


    connect(ui->toolButton_3,SIGNAL(pressed()),this->maindeal->getPtz(),SLOT(OnButtonNearChanged()));
    connect(ui->toolButton_3,SIGNAL(released()),this->maindeal->getPtz(),SLOT(OffButtonNearChanged()));
    connect(ui->toolButton_4,SIGNAL(pressed()),this->maindeal->getPtz(),SLOT(OnButtonFarChanged()));
    connect(ui->toolButton_4,SIGNAL(released()),this->maindeal->getPtz(),SLOT(OffButtonFarChanged()));

    connect(ui->toolButton_5,SIGNAL(pressed()),this->maindeal->getPtz(),SLOT(OnButtonOpenChanged()));
    connect(ui->toolButton_5,SIGNAL(released()),this->maindeal->getPtz(),SLOT(OffButtonOpenChanged()));
    connect(ui->toolButton_6,SIGNAL(pressed()),this->maindeal->getPtz(),SLOT(OnButtonCloseChanged()));
    connect(ui->toolButton_6,SIGNAL(released()),this->maindeal->getPtz(),SLOT(OffButtonCloseChanged()));
    /*******************************************************************************************************************/

    connect(paintarea, SIGNAL(sigShowData()),this,SLOT(showData()));
    connect(setROI,SIGNAL(sigChangeArea_index(int)),paintarea,SLOT(UpdateArea_index(int)));
    connect(setROI,SIGNAL(sigaltablepaint()),this,SLOT(updatePainter2D()));

    connect(this->maindeal->getLidarClustem(), SIGNAL(SendClus_Object(QVariant)), this, SLOT(showClustem_Obj(QVariant)));
    connect(addlidar,SIGNAL(SendSet(SetData)),this,SLOT(addLidarSlot(SetData)));
    /********************************************************************************************************************/
    connect(timer,SIGNAL(timeout()),this,SLOT(scalePalyfram()));
    connect(saveMovie_timer,&QTimer::timeout,this,&MainWindow::onTimeout);
    connect(sendSmsTimer,&QTimer::timeout,this,&MainWindow::do_sendSms);

    //防护区域内点云
    connect(this->maindeal->getAlgonrithm(),SIGNAL(sigShow(lidarIntruder)),this,SLOT(showFiltcloud(lidarIntruder)));

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
    if(this->maindeal->getAllCloud()->points.size() > 0)
    {
        QString filePathName = QString::fromStdString(m_cloudFilePath) + strTime + ".pcd";
        pcl::io::savePCDFileBinary(filePathName.toStdString(),*this->maindeal->getAllCloud());
        this->maindeal->getAllCloud()->points.clear();
        this->maindeal->getAllCloud()->clear();
    }
    saveTime--;
    if(0 == saveTime)
    {
        this->maindeal->saveDataFlag = 0;
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
        this->maindeal->getViewr()->removeAllShapes();
        ui->qvtkWidget->update();
        ClustemSwitch = false;
        LEDContrlAPI(0);
        LEDContrlAPI_IP(addlidar->data.ledIp.c_str(),0);
        if(cruise_flag == 0)
        {
            this->maindeal->getPtz()->PTZ_Cruise_Open();
            cruise_flag = 1;
        }

        this->maindeal->getViewr()->removeAllShapes();
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

    this->maindeal->getPtz()->dist = data.setDis;
    this->maindeal->getPtz()->ang = data.setAng;
    XAngle = data.setXAngle;
    YAngle = data.setYAngle;
    Base_X = data.setBase_X;
    Base_Y = data.setBase_Y;
    paintarea->Radius = data.setRadius;
    this->maindeal->getLidarClustem()->setClusterTolerance(data.clusterTolerance);
    this->maindeal->getLidarClustem()->setMaxClusterSize(data.maxClusterSize);
    this->maindeal->getLidarClustem()->setMinClusterSize(data.minClusterSize);
    this->maindeal->getAlgonrithm()->setResolution(data.resolution);
    this->maindeal->getAlgonrithm()->setDifference_threshold(data.difference_threshold);

    WriteDevice(data);
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
        this->maindeal->getViewr()->removePointCloud(name);
        this->maindeal->getViewr()->addPointCloud(intruder.tCloud,name);
        this->maindeal->getViewr()->updatePointCloud(intruder.tCloud,name);
    }

    //聚类
    if(tCloud->size()>0)
    {
        this->maindeal->getLidarClustem()->lidar_points->clear();
        if (ClustemSwitch == true)
        {
            for (int i = 0; i < tCloud->size(); i++)
            {
                Cloud_Point point;
                point.x = tCloud->at(i).x;
                point.y = tCloud->at(i).y;
                point.z = tCloud->at(i).z;
                this->maindeal->getLidarClustem()->lidar_points->push_back(point);
            }

            if (this->maindeal->getLidarClustem()->m_stop == false)
            {
                this->maindeal->getLidarClustem()->m_stop = true;
                this->maindeal->getLidarClustem()->start();
                this->maindeal->getLidarClustem()->wait();
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
            this->maindeal->getPtz()->PTZ_Cruise_Open();
            cruise_flag = 1;
//            std::cout << "888882222count time milliseconds: " << count_time << std::endl;
        }
    }

}

void MainWindow::get_lidarC16(pcl::PointCloud<pcl::PointXYZRGB>::Ptr ptr)
{
    this->maindeal->getAlgonrithm()->tCloud->clear();
    *this->maindeal->getAlgonrithm()->tCloud += *ptr;
    this->maindeal->getAlgonrithm()->start();
    this->maindeal->getAlgonrithm()->wait();


    paintarea->tCloud->clear();
    *paintarea->tCloud  += *ptr;
    paintarea->update();


    if(viewer_Cloud_id ==0)
    {
        std::string name ="All_cloud";
        this->maindeal->getViewr()->removePointCloud(name);
        this->maindeal->getViewr()->addPointCloud(ptr,name);
        this->maindeal->getViewr()->updatePointCloud(ptr,name);
    }
    ui->qvtkWidget->update();

}

void MainWindow::get_CH128X1(pcl::PointCloud<pcl::PointXYZRGB>::Ptr ptr)
{
    this->maindeal->getAlgonrithm()->tCloud->clear();
    *this->maindeal->getAlgonrithm()->tCloud += *ptr;
    this->maindeal->getAlgonrithm()->start();
    this->maindeal->getAlgonrithm()->wait();


    paintarea->tCloud->clear();
    *paintarea->tCloud  += *ptr;
    paintarea->update();
    if(1 == this->maindeal->saveDataFlag)
    {
        *this->maindeal->getAllCloud() = *ptr;
    }

    if(viewer_Cloud_id ==0)
    {
        std::string name ="All_cloud";
        this->maindeal->getViewr()->removePointCloud(name);
        this->maindeal->getViewr()->addPointCloud(ptr,name);
        this->maindeal->getViewr()->updatePointCloud(ptr,name);
    }

    ui->qvtkWidget->update();
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
        this->maindeal->getViewr()->removeShape(cube);
    }
    // TODO:20220407 根据聚类目标的个数来触发报警灯
    if(Cl_obj.Obj->size() > 0)
    {
        if(1 == saveDataStatus)
        {
            if(!saveMovie_timer->isActive())
            {
                saveMovie_timer->start(1000);
                this->maindeal->saveDataFlag = 1;
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
            this->maindeal->getCluCloud()[i]->clear();
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
        this->maindeal->getViewr()->removePointCloud(ball);
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
        if(this->maindeal->getCluCloud()[Cl_obj.Obj->at(i).ID]->size() > 10)
        {

            this->maindeal->getCluCloud()[Cl_obj.Obj->at(i).ID]->erase( this->maindeal->getCluCloud()[Cl_obj.Obj->at(i).ID]->begin(), this->maindeal->getCluCloud()[Cl_obj.Obj->at(i).ID]->begin()+5);

        }

        if(this->maindeal->getCluCloud()[Cl_obj.Obj->at(i).ID]->size() > 30)
        {

            this->maindeal->getCluCloud()[Cl_obj.Obj->at(i).ID]->erase( this->maindeal->getCluCloud()[Cl_obj.Obj->at(i).ID]->begin(), this->maindeal->getCluCloud()[Cl_obj.Obj->at(i).ID]->begin()+20);

        }


        if(isTrick == true)
        {
            this->maindeal->getCluCloud()[Cl_obj.Obj->at(i).ID]->push_back(point);

            std::string ball =  QString("ball%1").arg(Cl_obj.Obj->at(i).ID).toStdString();


            this->maindeal->getViewr()->removePointCloud(ball);
            this->maindeal->getViewr()->addPointCloud(this->maindeal->getCluCloud()[Cl_obj.Obj->at(i).ID],ball);
            //this->maindeal->getViewr()->addPointCloud(Clu.at(Cl_obj.Obj->at(i).ID),ball);
            this->maindeal->getViewr()->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE,4,ball);
            this->maindeal->getViewr()->updatePointCloud(this->maindeal->getCluCloud()[Cl_obj.Obj->at(i).ID],ball);
        }

        std::string cube = "box" + std::to_string(i);
        this->maindeal->getViewr()->addCube(Cl_obj.Obj->at(i).xmin, Cl_obj.Obj->at(i).xmax, Cl_obj.Obj->at(i).ymin, Cl_obj.Obj->at(i).ymax, Cl_obj.Obj->at(i).zmin, Cl_obj.Obj->at(i).zmax, 0, 255, 0,cube);
        this->maindeal->getViewr()->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_REPRESENTATION, pcl::visualization::PCL_VISUALIZER_REPRESENTATION_SURFACE, cube);
        this->maindeal->getViewr()->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 0, 1, 0, cube);
        this->maindeal->getViewr()->setShapeRenderingProperties(pcl::visualization::PCL_VISUALIZER_OPACITY, 0.4, cube);
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
    this->maindeal->getPtz()->war_horizontal = horizontal;
    this->maindeal->getPtz()->war_azimuth = azimuth;
    this->maindeal->getPtz()->war_dist = r;

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

    this->maindeal->getViewr()->addLine(p1, p2, 0, 1, 0, line1);
    this->maindeal->getViewr()->addLine(p2, p3, 0, 1, 0, line2);
    this->maindeal->getViewr()->addLine(p3, p4, 0, 1, 0, line3);
    this->maindeal->getViewr()->addLine(p1, p4, 0, 1, 0, line4);

    this->maindeal->getViewr()->addLine(p5, p6, 0, 1, 0, line5);
    this->maindeal->getViewr()->addLine(p6, p7, 0, 1, 0, line6);
    this->maindeal->getViewr()->addLine(p7, p8, 0, 1, 0, line7);
    this->maindeal->getViewr()->addLine(p8, p5, 0, 1, 0, line8);

    this->maindeal->getViewr()->addLine(p1, p5, 0, 1, 0, line9);
    this->maindeal->getViewr()->addLine(p2, p6, 0, 1, 0, line10);
    this->maindeal->getViewr()->addLine(p3, p7, 0, 1, 0, line11);
    this->maindeal->getViewr()->addLine(p4, p8, 0, 1, 0, line12);
}



/*******************************二维绘制图形*************************************************/
void MainWindow::drawArea()
{
    this->maindeal->getViewr()->removeAllShapes();
    if(viewer_Area_id ==0)
    {
        for(int index=0;index<3;index++)
        {
            for(int i = 0; i < paintarea->Area2d_point[index].size()-1; i++)
            {
                char buffer[20];
                sprintf(buffer,"2Darea_%d_%d",index,i);
                std::string name =buffer;
                this->maindeal->getViewr()->addLine<pcl::PointXYZRGB> (paintarea->Area2d_point[index][i],paintarea->Area2d_point[index][i+1],255,0,0,name);
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
    this->maindeal->getViewr()->removeAllShapes();
    for(int index=0;index<3;index++)
    {
        paintarea->Area2d_point[index].clear();
        Maindeal::search_max_min(paintarea->area[index].Area2D_point_T);
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
            this->maindeal->getViewr()->addLine<pcl::PointXYZRGB> (paintarea->Area2d_point[index][i],paintarea->Area2d_point[index][i+1],r,g,b,name);
            ui->qvtkWidget->update();
        }

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

        this->maindeal->getAlgonrithm()->area[index].Area2D_point_T= setROI->area[index].Area2D_point_T;
        this->maindeal->getAlgonrithm()->area[index].Area2D_point= setROI->area[index].Area2D_point;
        this->maindeal->getAlgonrithm()->area[index].Area_height_down =setROI->area[index].Area_height_down;
        this->maindeal->getAlgonrithm()->area[index].Area_height_top = setROI->area[index].Area_height_top;
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

    lRealPlayHandle = NET_DVR_RealPlay_V40(this->maindeal->getPtz()->lUserID, &struPlayInfo, NULL, NULL);
    QString  message1=QString("lrealpal %1").arg(lRealPlayHandle);
    QString  message2=QString("error = %1").arg(NET_DVR_GetLastError());
    ui->textEdit->append(message1);
    ui->textEdit->append(message2);
    //    NET_DVR_SetLogToFile(1,"/home/ls/work3/ls_safe/build");

    if (lRealPlayHandle < 0)
    {
        NET_DVR_Logout(this->maindeal->getPtz()->lUserID);
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

    this->maindeal->getPtz()->cam_IP = config.value(QString("camera/IP")).toString();
    this->maindeal->getPtz()->cam_ID = config.value(QString("camera/ID")).toString();
    this->maindeal->getPtz()->cam_Pass = config.value(QString("camera/Pass")).toString();


    this->maindeal->getPtz()->dist = config.value(QString("preset/Dis")).toFloat();
    this->maindeal->getPtz()->ang = config.value(QString("preset/Ang")).toFloat();
    XAngle = config.value(QString("preset/XAngle")).toFloat();
    YAngle = config.value(QString("preset/YAngle")).toFloat();
    Base_X = config.value(QString("preset/Base_X")).toFloat();
    Base_Y = config.value(QString("preset/Base_Y")).toFloat();
    paintarea->Radius = config.value(QString("preset/Radius")).toFloat();
    saveDataStatus = config.value(QString("other/SaveDataStatus")).toInt();
    inAalarmLampStatus = config.value(QString("other/InAalarmLampStatus")).toInt();
    outAalarmLampStatus = config.value(QString("other/OutAalarmLampStatus")).toInt();
    addlidar->data.setDis =  this->maindeal->getPtz()->dist;
    addlidar->data.setAng = this->maindeal->getPtz()->ang;
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
    config.setValue("IP",this->maindeal->getPtz()->cam_IP);
    config.setValue("ID",this->maindeal->getPtz()->cam_ID);
    config.setValue("Pass",this->maindeal->getPtz()->cam_Pass);
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
    if(this->maindeal->getPtz()->isRun == true)
    {
        ui->toolButton_7->setStyleSheet("border-image: url(:/images/OFF.png);");
        this->maindeal->getPtz()->isRun = false;
    }
    else if(this->maindeal->getPtz()->isRun == false)
    {
        ui->toolButton_7->setStyleSheet("border-image: url(:/images/ON.png);");
        this->maindeal->getPtz()->isRun = true;
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
        this->maindeal->getViewr()->removeAllShapes();


        ui->qvtkWidget->update();
    }
    else if (isShow == false)
    {
        ui->toolButton_actionOpengrid->setStyleSheet("border-image: url(:/images/ON.png);");
        isShow = true;
        for (int i = -200; i < 210; i = i + 10)
        {
            this->maindeal->getViewr()->addLine(pcl::PointXYZ(i,0,0), pcl::PointXYZ(i,200,0), 150, 150, 150, "Line_x" + std::to_string(i));
            this->maindeal->getViewr()->setShapeRenderingProperties(1, 0.2, "Line_x" + std::to_string(i));
        }
        for (int i = 0; i < 210; i = i + 10)
        {
            this->maindeal->getViewr()->addLine(pcl::PointXYZ(-200,i,0), pcl::PointXYZ(200,i,0), 150, 150, 150, "Line_y" + std::to_string(i));
            this->maindeal->getViewr()->setShapeRenderingProperties(1, 0.2, "Line_y" + std::to_string(i));
        }

        this->maindeal->getViewr()->addLine(pcl::PointXYZ(0,0,0), pcl::PointXYZ(-200,115,0), 150, 150, 150, "Lineleft" );
        this->maindeal->getViewr()->setShapeRenderingProperties(1, 0.4, "Lineleft");
        this->maindeal->getViewr()->addLine(pcl::PointXYZ(0,0,0), pcl::PointXYZ(200,115,0), 150, 150, 150, "Lineright" );
        this->maindeal->getViewr()->setShapeRenderingProperties(1, 0.4, "Lineright");
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
