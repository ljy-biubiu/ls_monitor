﻿#ifndef MAINDEAL_H
#define MAINDEAL_H


#include <QDebug>
#include <QObject>

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <qmath.h>
#include <common.h>
#include <filesystem.h>
#include <lidarclustem.h>
#include "algonrithm.h"
#include "addlidar.h"
#include "LED_RS232_API.h"
#include "LED_serverAPI.h"
#include <ptz.h>
#include <getlidarc16.h>
#include "getlidarch128x1.h"

#include <pcl/io/ifs_io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/vtk.h>
#include <pcl/visualization/common/common.h>
#include <pcl/visualization/point_cloud_geometry_handlers.h>


Q_DECLARE_METATYPE(pcl::PointCloud<pcl::PointXYZRGB>::Ptr);

class Maindeal : public QObject {
    Q_OBJECT
public:
    explicit Maindeal( AddLidar* addidar ,QObject* parent = nullptr );
    ~Maindeal();

    void getCalibAngle();
    boost::shared_ptr<pcl::visualization::PCLVisualizer> getViewr();
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr * getCluCloud();
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr  getAllCloud();
    LidarClustem* getLidarClustem();
    Algonrithm* getAlgonrithm();
    PTZ* getPtz();

    int saveDataFlag;
    static void search_max_min(QList<pcl::PointXYZRGB> box);
    static void quickSort(float s[], int l, int r);

private:
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr Clu_cloud[255];
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr allcloud;

    LidarClustem *lidarClustem;
    Algonrithm *algonrithm;
    AddLidar *addidar_;
    PTZ *m_ptz;

    GetlidarC16 *getC16;
    GetlidarCH128X1 *getCH128X1;

    float XAngle = 0;
    float YAngle = 0;

    float Base_X = 0;
    float Base_Y = 0;

    double BigAngle[32] = {-17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4.125, -4, -3.125,
                            -3, -2.125, -2, -1.125, -1, -0.125, 0, 0.875, 1, 1.875, 2, 3, 4, 5, 6, 7};


signals:
    void send_CH128X1(pcl::PointCloud<pcl::PointXYZRGB>::Ptr prt);
    void send_lidarC16(pcl::PointCloud<pcl::PointXYZRGB>::Ptr prt);

public slots:
    void CalculateCoordinates(LidarData lidardata);
    void CalculateCoordinatesCH128X1(LidarDataCHXXX lidardata);
};

#endif  // MAINDEAL_H
