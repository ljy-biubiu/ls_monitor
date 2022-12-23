#ifndef MAINDEAL_H
#define MAINDEAL_H

#include <QApplication>
#include <QDesktopWidget>

#include "mainwindow.h"
#include "ptz.h"
#include "lidardrive128s1.h"
#include "chat_plc.h"
#include "paramsevent.hpp"
#include "my_log.h"
#include "algorithm.h"
#include "cffmpegInterface.h"
#include "COMMUNICATION/IMU/LPMSIG1.h"


class Maindeal
{
public:
    Maindeal(int my_argc_,char **my_argv_);

    //UI
    const QApplication* getApp();
    void initUI();

private:

    void initAlcorithm();
    void chatLowerMachine();
    void initCameraDrive();
    void initLidarDrive();
    void initParamsServer();
    void startProcess();
    void startCamera();
    void initLog();


    int my_argc{0};
    char **my_argv;

    QApplication* app;
    QDesktopWidget* dw;
    MainWindow* w;
    AlgorithmInterface* algorithmInterface = nullptr;
    PTZ *ptz = nullptr;
    //LidarDriveInterface *lidarDriveInterface = nullptr;
    ComunicateInterface *comunicateInterface = nullptr;
    ComunicateInterface *comunicateInterface_imu = nullptr;

    std::shared_ptr<LidarDriveInterface> lidarDriveInterface;
    std::shared_ptr<CameraDriveInterface> cameraDriveInterface;
    std::shared_ptr<ParamsEvent<ObserverFunc>> params_event;
};

#endif // MAINDEAL_H
