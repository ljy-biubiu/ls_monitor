#include "maindeal.h"

using namespace imu;

Maindeal::Maindeal(int my_argc_, char **my_argv_) : my_argc(my_argc_), my_argv(my_argv_)
{
    /******************************************** 设置保存日志文件 *******************************************/
    createLogFile();
    /******************************************** 初始化雷达驱动线程 ******************************************/
    initLidarDrive();
    /******************************************** 初始化摄像头驱动线程 ****************************************/
    initCameraDrive();
    /******************************************** 初始化下位机通讯线程 ****************************************/
    chatLowerMachine();
    /******************************************** 初始化算法线程 *********************************************/
    initAlcorithm();
    /******************************************** 初始化UI **************************************************/
    initUI();
    /******************************************** 初始化参数服务  ********************************************/
    initParamsServer();
    /********************************************  执行程序   ***********************************************/
    startProcess();
}

void Maindeal::initAlcorithm()
{
    algorithmInterface = new Algorithm();
    algorithmInterface->initLidarDrive(lidarDriveInterface);
}

void Maindeal::initParamsServer()
{
    params_event = std::make_shared<ParamsEvent<ObserverFunc>>();

    if (w != nullptr)
        params_event->Connect(std::bind(&MainWindow::globalParamsCallback, w, std::placeholders::_1, std::placeholders::_2));
    if (lidarDriveInterface != nullptr)
        params_event->Connect(std::bind(&LidarDriveInterface::globalParamsCallback, lidarDriveInterface, std::placeholders::_1, std::placeholders::_2));
    if (ptz != nullptr)
        params_event->Connect(std::bind(&PTZ::globalParamsCallback, ptz, std::placeholders::_1, std::placeholders::_2));
    if (comunicateInterface != nullptr)
        params_event->Connect(std::bind(&ComunicateInterface::globalParamsCallback, comunicateInterface, std::placeholders::_1, std::placeholders::_2));
    if (algorithmInterface != nullptr)
        params_event->Connect(std::bind(&AlgorithmInterface::globalParamsCallback, algorithmInterface, std::placeholders::_1, std::placeholders::_2));
    if (comunicateInterface_imu != nullptr)
        params_event->Connect(std::bind(&ComunicateInterface::globalParamsCallback, comunicateInterface_imu, std::placeholders::_1, std::placeholders::_2));
    if (cameraDriveInterface != nullptr)
        params_event->Connect(std::bind(&CameraDriveInterface::globalParamsCallback, cameraDriveInterface, std::placeholders::_1, std::placeholders::_2));

    cameraDriveInterface->initParamsEvent(params_event);
    comunicateInterface->initParamsEvent(params_event);
    comunicateInterface_imu->initParamsEvent(params_event);
    initParamEventLog(params_event);
    w->initParamsEvent(params_event);
}

void Maindeal::initLog()
{
    createLogFile();
}

void Maindeal::chatLowerMachine()
{
    comunicateInterface = new ChatPlc();
    comunicateInterface_imu = new LPMSIG1();
}

void Maindeal::initLidarDrive()
{
    lidarDriveInterface = std::make_shared<LidarDrive128S1>();
}

void Maindeal::initCameraDrive()
{
    // this->ptz = new PTZ();
    cameraDriveInterface = std::make_shared<CFFmpegInterface>();
}

void Maindeal::initUI()
{
    app = new QApplication(this->my_argc, this->my_argv);
    dw = new QDesktopWidget();
    w = new MainWindow(qApp);
    w->initAlgorithmInterface(algorithmInterface);
    w->initLidarDriveInterface(lidarDriveInterface);
    w->initCameraDriveInterface(cameraDriveInterface);
}

void Maindeal::startProcess()
{
    // this->ptz->PTZ_init((HWND)this->w->getCameraWidget()->winId());
    this->params_event->Notify(params_event->getTotalParams(), false);

    if (lidarDriveInterface != nullptr)
        this->lidarDriveInterface->init();
    if (comunicateInterface != nullptr)
        this->comunicateInterface->init();
    if (algorithmInterface != nullptr)
        this->algorithmInterface->run();
    if (cameraDriveInterface != nullptr)
        this->cameraDriveInterface->init();
    if (comunicateInterface_imu != nullptr)
        this->comunicateInterface_imu->run();

    usleep(1000 * 1000 * 2);
    this->w->getqSplashScreen()->close(); // 关闭启动动画
    this->w->showMaximized();
    this->w->show();
}

const QApplication *Maindeal::getApp()
{
    return app;
}
