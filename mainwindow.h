#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <pcl/io/ifs_io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/vtk.h>
#include <pcl/visualization/common/common.h>
#include <pcl/visualization/point_cloud_geometry_handlers.h>
#include <QStyleFactory>
#include <QSplitter>
#include <QVTKWidget.h>
#include <vtkRenderWindow.h>
#include <QThread>
#include "qmutex.h"
#include <QSplitter>
#include <QButtonGroup>
#include <common.h>
#include <filesystem.h>
#include <getlidarc16.h>
#include "getlidarch128x1.h"
#include <UI/include/paintarea.h>
#include <UI/include/setroi.h>
#include <UI/include/addlidar.h>
#include <algonrithm.h>
#include <ptz.h>
#include <lidarclustem.h>
#include <lidarroaddetect.h>
#include <map>
#include <iostream>
#include <chrono>
#include "UI/include/smsdialog.h"
//#include <AliSmsAPIClient.h>
#include "UI/include/aboutdialog.h"
#include "maindeal.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void ReadDevice();//读取配置文件
    void WriteDevice(SetData data);//
    void ReadConfig();

    void initConnect();
    void initUi();
    void initParam();
    void initControlPanel();
    void initCameraShow();
    void initPointCShow();

    //防区
    void drawArea();
    void draw2DArea(int idx);
    void ListtoConvex();
//    void quickSort(float s[], int l, int r);
//    void search_max_min(QList<pcl::PointXYZRGB> box);
    //

    void showMovie();


    float XAngle = 0;
    float YAngle = 0;

    float Base_X = 0;
    float Base_Y = 0;

    float sinTheta_1[128];
    float sinTheta_2[128];
    float cosTheta_1[128];
    float cosTheta_2[128];
    float G_Angle[32] = {-17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4.125f, -4, -3.125f,
                         -3, -2.125f, -2, -1.125f, -1, -0.125f, 0, 0.875f, 1, 1.875f, 2, 3, 4, 5, 6, 7};
    float prismAngle[4];
    float lidarA1 = 0;
    float lidarA2 = 0;
    float lidarA3 = 0;
    float lidarA4 = 0;


    AddLidar *addlidar;
    lidar temlidar;
    SetROI *setROI;
    PTZ *m_ptz;

    double BigAngle[32] = {-17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4.125, -4, -3.125,
                            -3, -2.125, -2, -1.125, -1, -0.125, 0, 0.875, 1, 1.875, 2, 3, 4, 5, 6, 7};
//    float sinTheta1[128];                                   //ÊúÖ±œÇ
//    float sinTheta2[128];                                   //ÊúÖ±œÇ
signals:
    void new_Day();
private:
    Maindeal* maindeal;
    Ui::MainWindow *ui;
//    FileSystem *fs;
//    GetlidarC16 *getC16;
//    GetlidarCH128X1 *getCH128X1;
    PaintArea *paintarea;

    QList<pcl::PointXYZRGB> Area2D_point[AREAS];
//    Algonrithm *algonrithm;

    LONG lRealPlayHandle;

    //创建对象
//    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
//    pcl::PointCloud<pcl::PointXYZRGB>::Ptr Clu_cloud[255];
//    pcl::PointCloud<pcl::PointXYZRGB>::Ptr allcloud;
//    int saveDataFlag;
    QButtonGroup *view_Area_group;
    QButtonGroup *view_Cloud_group;
    QButtonGroup *view_Cluster_group;
    int Area_index=0;
    QList<struct tableRow> list_tableItem;

    int viewer_Area_id;
    int viewer_Cloud_id;
//    bool ClustemSwitch;
    bool isShow;
    bool isTrick;
//    bool isSendSms;     // 短信开关
////    int alarm_flag = 0; // 报警开关
////    int cruise_flag = 1;// 巡航开关

    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point end_time;

    QTimer *saveMovie_timer;
    QTimer *timer;
    int saveDataStatus;
    int inAalarmLampStatus;
    int outAalarmLampStatus;
    QTimer *dataTime;
    QTimer *sendSmsTimer;
    bool sendSmsStatus;
    std::string m_movieFilePath;
    std::string m_cloudFilePath;
    QString todayDate;
    SMSDialog *smsDialog;
//    AliSmsAPIClient *Ali;
    aboutDialog *paboutDialog;
protected slots:
    void slot_view_Area_group(int id);
    void slot_view_Cloud_group(int id);
    void slot_view_Cluster_group(int id);

    //
//    void CalculateCoordinates(LidarData lidardata);
//    void CalculateCoordinatesCH128X1(LidarDataCHXXX lidardata);
    void showData();
    void addLidarSlot(SetData data);

    //聚类
    void showClustem_Obj(QVariant DataVar);
    void addcuboid(Object obj, int id);
    void SearchIntruder(Object obj);
    void showAbout();

    //
    void get_CH128X1(QVariant ptr);
    void get_lidarC16(pcl::PointCloud<pcl::PointXYZRGB>::Ptr ptr);


private slots:
    void showFiltcloud(lidarIntruder intruder);

    void on_pushButton_clicked();
    void on_pushButton_addlidar_clicked();

    void on_toolButton_7_clicked();
    //防区
    void updatePainter2D();
    void scalePalyfram();//窗口大小改变要调用该函数
    void onTimeout();
    void on_toolButton_savedata_clicked();
    void on_toolButton_Portlight_clicked();
    void on_toolButton_indoorlight_clicked();
    void on_toolButton_actionOpengrid_clicked();
    void on_toolButton_actionTrick_clicked();
    void update_Time();
    void on_pushButton_sms_clicked();
    void do_sendSms();
    void on_toolButton_sms_clicked();

private:
    void Creat_DataFileDir();
    bool CreateAndCheckPath();
    bool CreateCheck(std::string& strPath);
};

#endif // MAINWINDOW_H
