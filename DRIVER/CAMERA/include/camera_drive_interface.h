#ifndef CAMERADRIVEINTERFACE_H
#define CAMERADRIVEINTERFACE_H

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <opencv2/core/core.hpp>

#include "paramsevent.hpp"

class CameraDriveInterface
{
public:
    virtual void init() = 0;
    virtual void run() = 0;
    virtual cv::Mat getFFmpegImage() = 0;
    virtual void globalParamsCallback(TotalParams msg, bool save_flag) = 0;

    void initParamsEvent(std::shared_ptr<ParamsEvent<ObserverFunc>> params_event_);
    bool get_camera_data(cv::Mat &msg);

    std::mutex m_lock;
    std::queue<cv::Mat> recv_lmages_queue_;

protected:
    std::string my_ip;
    std::string my_name;
    std::string key_word;
    std::shared_ptr<ParamsEvent<ObserverFunc>> params_event;
};

#endif // CAMERADRIVEINTERFACE_H
