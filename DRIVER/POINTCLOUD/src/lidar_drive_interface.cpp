#include "lidar_drive_interface.h"

bool LidarDriveInterface::get_lidar_data(PointCloudTPtr msg)
{
     std::lock_guard<std::mutex> LockGuard(this->m_lock);
    if (recv_lidar_queue_.size() > 0)
    {
        *msg = std::move(*this->recv_lidar_queue_.front());
        this->recv_lidar_queue_.pop();
        return true;
    }
    else
    {
        return false;
    }
}

void LidarDriveInterface::initParamsEvent(std::shared_ptr<ParamsEvent<ObserverFunc>> params_event_)
{
    params_event = params_event_;
}


// void LidarDriveInterface::globalParamsCallback(TotalParams msg,bool save_flag)
// {
//     this->my_ip  = msg.baseParams.lidarBase.LidarAddress;
//     this->my_port = msg.baseParams.lidarBase.lidarPort;

//     // this-
// }

void LidarDriveInterface::setParams(const int port, const std::string ip)
{
    this->my_ip = ip;
    this->my_port = port;
}
