#ifndef MAINDEAL_H
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

#include <pcl/io/ifs_io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/vtk.h>
#include <pcl/visualization/common/common.h>
#include <pcl/visualization/point_cloud_geometry_handlers.h>




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

private:
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr Clu_cloud[255];
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr allcloud;

    LidarClustem *lidarClustem;
    Algonrithm *algonrithm;
    AddLidar *addidar_;
    PTZ *m_ptz;



signals:

public slots:

};

#endif  // MAINDEAL_H
