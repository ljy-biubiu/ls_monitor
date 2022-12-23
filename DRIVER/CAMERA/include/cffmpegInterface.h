#ifndef CFFMPEGINTERFACE_H
#define CFFMPEGINTERFACE_H
#include <iostream>
#include "opencv2/opencv.hpp"
#include "camera_drive_interface.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/pixfmt.h"
#include "libswscale/swscale.h"
}

class CFFmpegInterface : public CameraDriveInterface
{

public:
    cv::Mat getFFmpegImage();                       // 获取相机帧
    bool openDevice(const std::string &deviceName); // 初始化相机设备
    void closeDevice();                             // 关闭相机设备
    CFFmpegInterface();
    ~CFFmpegInterface();

    virtual void run() override;
    virtual void init() override;
    virtual void globalParamsCallback(TotalParams msg, bool save_flag) override;

private:
    AVFormatContext *context;
    int video_index;
    AVCodecContext *codecContext;
    AVFrame *avFrame;
    SwsContext *conversion;
};

#endif
