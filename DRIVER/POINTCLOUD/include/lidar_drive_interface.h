#ifndef LIDARDRIVEINTERFACE_H
#define LIDARDRIVEINTERFACE_H

#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

#include <pcl/io/ifs_io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <common.h>

#include "paramsevent.hpp"

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloudT;
typedef pcl::PointCloud<PointT>::Ptr PointCloudTPtr;


class LidarDriveInterface
{
public:

    virtual void init() = 0;
    virtual void run() = 0;
    virtual void generatePclCould() = 0;
    virtual void globalParamsCallback(TotalParams msg,bool save_flag) = 0;
    virtual void initParamsEvent(std::shared_ptr<ParamsEvent<ObserverFunc>> params_event_) ;
    
    bool get_lidar_data(PointCloudTPtr msg);
    void setParams(const int port, const std::string ip);

protected:
    int my_port;
    std::string my_ip;
    std::mutex m_lock;
    std::shared_ptr<ParamsEvent<ObserverFunc>> params_event;
    std::queue<PointCloudTPtr> recv_lidar_queue_;
};

#endif // LIDARDRIVEINTERFACE_H
