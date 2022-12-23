#include "cffmpegInterface.h"
#include "camera_drive_interface.h"

CFFmpegInterface::CFFmpegInterface()
{
}

CFFmpegInterface::~CFFmpegInterface()
{
}

void CFFmpegInterface::globalParamsCallback(TotalParams msg, bool save_flag)
{
    this->my_ip = msg.baseParams.cameraBase.ip;
    this->my_name = msg.baseParams.cameraBase.name;
    this->key_word = msg.baseParams.cameraBase.code;
}

void CFFmpegInterface::init()
{
    std::thread dowork_thread(std::bind(&CFFmpegInterface::run, this));
    dowork_thread.detach();
}

void CFFmpegInterface::run()
{
    qDebug() << "摄像头IP:" << QString::fromStdString(this->my_ip);
    qDebug() << "摄像头用户名:" << QString::fromStdString(this->my_name);
    qDebug() << "摄像头秘钥:" << QString::fromStdString(this->key_word);

    std::string deviceName = "rtsp://" + this->my_name + ":" + this->key_word + "@" + this->my_ip + "/h264/ch1/main/av_stream";
    // std::string deviceName = "rtsp://admin:ls123456@192.168.2.127/h264/ch1/main/av_stream";
    if (!openDevice(deviceName))
    {
        qCritical() << "打開攝像頭設備失敗";

        std::lock_guard<std::mutex> LockGuard(params_event->getMylock());
        params_event->getTotalParams().alarm_status.communicate_status.bits.camera = 0;
        params_event->Notify(params_event->getTotalParams(), false);
        return;
    }
    while (1)
    {
        usleep(1000 * 1);

        cv::Mat cur_image = this->getFFmpegImage().clone();

        if (!cur_image.empty())
        {
            std::lock_guard<std::mutex> LockGuard(m_lock);
            recv_lmages_queue_.push(cur_image);

            if (recv_lmages_queue_.size() > 3)
            {
                recv_lmages_queue_.pop();

                // qWarning() << "警告：接收到camera驱动队列超过3！";
            }
        }
    }
}

cv::Mat CFFmpegInterface::getFFmpegImage()
{
    AVPacket packet;
    cv::Mat imageSrc;

    if (av_read_frame(context, &packet) >= 0)
    {

        if (packet.stream_index == video_index)
        {
            avcodec_send_packet(codecContext, &packet);

            while (avcodec_receive_frame(codecContext, avFrame) == 0)
            {
                imageSrc.create(codecContext->height, codecContext->width, CV_8UC3);
                int imageStep = imageSrc.step1();
                sws_scale(conversion, avFrame->data, avFrame->linesize, 0, codecContext->height, &imageSrc.data, &imageStep);
            }
        }
        av_packet_unref(&packet);
    }
    return imageSrc;
}
void CFFmpegInterface::closeDevice()
{
    sws_freeContext(conversion);
    av_frame_free(&avFrame);
    avcodec_close(codecContext);
    //    avcodec_parameters_free(&params);
    avformat_close_input(&context);
}

bool CFFmpegInterface::openDevice(const std::string &deviceName)
{
    AVDictionary *avdic = NULL;
    av_dict_set(&avdic, "rtsp_transport", "tcp", 0);
    av_dict_set(&avdic, "max_delay", "500000", 0);
    av_dict_set(&avdic, "stimeout", "500000", 0); // 设置超时断开连接时间(ms) 500ms
    av_dict_set(&avdic, "fps", "25", 0);          // 设置帧数

    avformat_network_init(); /// 初始化FFmpeg网络模块
    av_register_all();       // 初始化FFMPEG调用了这个才能正常适用编码器和解码器
    context = avformat_alloc_context();
    AVInputFormat *inputFormat = av_find_input_format("dshow");

    if (avformat_open_input(&context, deviceName.c_str(), inputFormat, &avdic) != 0)
    {
        printf("can't open the input\n");
        return false;
    }

    if (avformat_find_stream_info(context, NULL) < 0)
    {
        printf("Could't find stream infomation.\n");
        return false;
    }

    video_index = av_find_best_stream(context, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    if (video_index == -1)
    {
        printf("Could not find a video stream\n");
        avformat_close_input(&context);
        return false;
    }

    // 获取流参数
    AVCodecParameters *params = context->streams[video_index]->codecpar;

    // 获取解码器
    AVCodec *codec = avcodec_find_decoder(params->codec_id);
    if (codec == NULL)
    {
        printf("Could not find decoder\n");
        avformat_close_input(&context);
        return false;
    }

    // 初始化一个解码器的上下文
    codecContext = avcodec_alloc_context3(codec);
    if (avcodec_parameters_to_context(codecContext, params) != 0)
    {
        printf("Could not copy codec context\n");
        avformat_close_input(&context);
        return false;
    }

    if (avcodec_open2(codecContext, codec, NULL) < 0)
    {
        printf("Could not open codec\n");
        return false;
    }

    conversion = sws_getContext(codecContext->width, codecContext->height, codecContext->pix_fmt, codecContext->width, codecContext->height, AV_PIX_FMT_BGR24, SWS_FAST_BILINEAR, NULL, NULL, NULL);

    avFrame = av_frame_alloc();

    return true;
}
