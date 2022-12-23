#include "camera_drive_interface.h"

bool CameraDriveInterface::get_camera_data(cv::Mat &msg)
{
    std::lock_guard<std::mutex> LockGuard(this->m_lock);
    if (recv_lmages_queue_.size() > 0)
    {
        msg = std::move(this->recv_lmages_queue_.front());
        this->recv_lmages_queue_.pop();
        return true;
    }
    else
    {
        return false;
    }
}


void CameraDriveInterface::initParamsEvent(std::shared_ptr<ParamsEvent<ObserverFunc>> params_event_)
{
    params_event = params_event_;
}