#include "mainwindow.h"

MainWindow::MainWindow(QApplication *my_app_, QWidget *parent)
    : QMainWindow(parent), my_app(my_app_)
{

    setWindowTitle(tr("PortMonitor"));

    initObeject();
    initConnect();
    initPointCShow();
    initMenu();
    initToolBar();
    mainLayOut();
    mainEventCallback();

    /******************************************** 设置qss样式表 ********************************************/
    QFile file(":/qss/darkblue.css");
    if (file.open(QFile::ReadOnly))
    {
        QString qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        my_app->setPalette(QPalette(QColor(paletteColor)));
        my_app->setStyleSheet(qss);
        file.close();
    }

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->main_title_bar->setParentWidget(this);
    this->setWindowIcon(QIcon(":/images/leishen.ico"));

    //    /******************************************** 加载启动动画 ********************************************/
    QPixmap pixmap(":/images/logo.png");
    screen = new QSplashScreen(pixmap);
    screen->show();
}

void MainWindow::initObeject()
{
    main_title_bar = new MainTitleBar();
    imageWidget = new ImageWidget();
    imageWidget2 = new ImageWidget();
    mainImageWidget = new ImageWidget();
    add_lidar = new AddLidar();
    paint_area = new PaintArea();
    setROI = new SetROI();

    paint_area->scroll = setROI->scrollarea;
    setROI->scrollarea->takeWidget();
    setROI->scrollarea->setWidget(paint_area);

    diary = new Diary();
    alarm = new Alarm();

    camera_viewer = new CameraViewer();
    camera_viewer2 = new CameraViewer();
    web_ui = new WebUi();
}

void MainWindow::mainEventCallback()
{
    my_timer = new QTimer(this);
    my_timer->start(5);
    connect(my_timer, &QTimer::timeout, [=]()
            {

        if(lidarDriveInterface != nullptr)
        {
            //updatePointCould();
        }
        if(algorithmInterface != nullptr)
        {
            updateAlgPointCould();
        }
        if(cameraDriveInterface != nullptr)
        {
            updateCameraImage();
        } });
}

void MainWindow::updateCameraImage()
{
    cv::Mat cur_image;
    if (!this->cameraDriveInterface->get_camera_data(cur_image))
    {
        return;
    }

    this->camera_viewer->setCameraMat(cur_image);
    this->camera_viewer2->setCameraMat(cur_image);
}

void MainWindow::updateAlgPointCould()
{

    static ProcessParamsOut msg;

    if (!this->algorithmInterface->get_lidar_data(msg))
    {
        return;
    }

    auto a = *msg.groundParamOut.groundCloud + *msg.shipParamOut.deckCloud;
    a += *msg.groundParamOut.cloudSrcRT;

    paint_area->xCloud->clear();
    *paint_area->xCloud += a;
    paint_area->update();

    std::string ground_groundCloud_name = "ground_groundCloud";
    std::string ground_cloudSrcRT_name = "ground_cloudSrcRT";
    std::string ground_highestCloud_name = "ground_highestCloud";

    std::string ship_sample_cloud_name = "ship_sample_cloud";
    std::string intersectionCloud_name = "intersectionCloud";
    std::string bottomHighestCloud_name = "bottomHighestCloud";

    std::string polarCloud_name = "polarCloud";
    std::string bottomHighestCloud2_name = "bottomHighestCloud2";

    std::string cloud_boundary1_name = "cloud_boundary1";
    std::string deckBottomCloud_name = "deckBottomCloud";

    //
    this->viewer->removeAllPointClouds();
    this->viewer->removeAllShapes();

    // 大地点云处理
    pcl::visualization::PointCloudColorHandlerGenericField<PointT> findColor(msg.groundParamOut.groundCloud, "z"); // 按照I字段进行渲染
    this->viewer->addPointCloud(msg.groundParamOut.cloudSrcRT, ground_cloudSrcRT_name);
    this->viewer->addPointCloud<PointT>(msg.groundParamOut.groundCloud, findColor, ground_groundCloud_name);

    PointCloudTPtr highestCloud(new PointCloudT); // 底部最高点点云
    for (int i = 0; i < msg.groundParamOut.materialHighestPoint.size(); ++i)
    {
        highestCloud->push_back(msg.groundParamOut.materialHighestPoint.at(i));
    }
    this->viewer->addPointCloud<PointT>(highestCloud, ground_highestCloud_name);
    this->viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 1, 0, 0, ground_highestCloud_name);
    this->viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 10, ground_highestCloud_name);

    for (int i = 0; i < msg.groundParamOut.materialHighestPoint.size(); ++i)
    {
        PointT p = msg.groundParamOut.materialHighestPoint.at(i);
        string text = Util::formatValue(p.x, 2) + "," + Util::formatValue(p.y, 2) + "," + Util::formatValue(p.z, 2);
        this->viewer->addText3D(text, p, 1.0, 1.0, 1.0, 1.0, "point" + to_string(i));
        this->viewer->addText3D(text, p, 1.0, 1.0, 1.0, 1.0, "point1" + to_string(i));
    }
    // 船板点云处理
    /////////////////////////////////////////////////////////

    PointCloudTPtr intersectionCloud(new PointCloudT); // 矩形角点点云
    vector<AutomatedPort::LineInfo> lineInfoVec;
    for (int i = 0; i < msg.shipParamOut.rectangleInfoVec.size(); ++i)
    {
        lineInfoVec.push_back(msg.shipParamOut.rectangleInfoVec.at(i).linesL.at(0));
        lineInfoVec.push_back(msg.shipParamOut.rectangleInfoVec.at(i).linesL.at(1));
        lineInfoVec.push_back(msg.shipParamOut.rectangleInfoVec.at(i).linesW.at(0));
        lineInfoVec.push_back(msg.shipParamOut.rectangleInfoVec.at(i).linesW.at(1));
        for (int j = 0; j < 4; ++j)
        {
            intersectionCloud->push_back(msg.shipParamOut.rectangleInfoVec.at(i).cornerPoints.at(j));
        }
    }
    PointCloudTPtr bottomHighestCloud(new PointCloudT); // 底部最高点点云
    for (int i = 0; i < msg.shipParamOut.bottomHighestPoint.size(); ++i)
    {
        bottomHighestCloud->push_back(msg.shipParamOut.bottomHighestPoint.at(i));
    }
    vector<PointCloudTPtr> allLineCloudVec;
    allLineCloudVec.clear();
    for (int i = 0; i < lineInfoVec.size(); ++i)
    {
        allLineCloudVec.push_back(lineInfoVec.at(i).cloud);
    }
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr colorCloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    Algorithm::getColorCloud(allLineCloudVec, colorCloud, 50, 250);

    this->viewer->addPointCloud<PointT>(msg.shipParamOut.deckCloud, ship_sample_cloud_name);
    pcl::visualization::PointCloudColorHandlerGenericField<PointT> findColor2(msg.shipParamOut.deckBottomCloud, "z"); // 按照I字段进行渲染
    this->viewer->addPointCloud<PointT>(msg.shipParamOut.deckBottomCloud, findColor2, deckBottomCloud_name);

    this->viewer->addPointCloud(colorCloud, cloud_boundary1_name);
    this->viewer->addPointCloud<PointT>(intersectionCloud, intersectionCloud_name);
    this->viewer->addPointCloud<PointT>(bottomHighestCloud, bottomHighestCloud_name);
    this->viewer->addPointCloud<PointT>(bottomHighestCloud, bottomHighestCloud2_name);
    this->viewer->addPointCloud<PointT>(msg.shipParamOut.polarCloud, polarCloud_name);
    this->viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 1, 0, 0, ship_sample_cloud_name);
    this->viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 1, 1, 0, intersectionCloud_name);
    this->viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, intersectionCloud_name);
    this->viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 0, 1, 1, bottomHighestCloud_name);
    this->viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 10, bottomHighestCloud_name);
    this->viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 0, 1, 1, bottomHighestCloud2_name);
    this->viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 10, bottomHighestCloud2_name);
    this->viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR, 1, 0, 1, polarCloud_name);

    for (int i = 0; i < msg.shipParamOut.allClusters.size(); ++i)
    {
        lshapedfit::ObjectInfo &_cluster = msg.shipParamOut.allClusters.at(i);
        Eigen::Vector3f translation(_cluster.x, _cluster.y, _cluster.z);
        Eigen::Quaternionf rotation(cos(_cluster.heading / 2), 0, 0, sin(_cluster.heading / 2)); //_cluster.heading * M_PI / 180.0
        this->viewer->addCube(translation, rotation, _cluster.l, _cluster.w, _cluster.h, to_string(i) + "cube");
        this->viewer->setRepresentationToWireframeForAllActors();
    }
    for (int i = 0; i < lineInfoVec.size(); ++i)
    {
        this->viewer->addLine(*lineInfoVec.at(i).coefficients, "line" + to_string(i));
    }
    for (int i = 0; i < msg.shipParamOut.rectangleInfoVec.size(); ++i)
    {

        this->viewer->removeText3D("line" + to_string(i));
        this->viewer->removeText3D("line1" + to_string(i));

        this->viewer->addText3D(Util::formatValue(msg.shipParamOut.rectangleInfoVec.at(i).l, 2), msg.shipParamOut.rectangleInfoVec.at(i).linesL.at(0).centerPoint, 1.0,
                                1.0, 1.0,
                                1.0, "line" + to_string(i));
        this->viewer->addText3D(Util::formatValue(msg.shipParamOut.rectangleInfoVec.at(i).w, 2), msg.shipParamOut.rectangleInfoVec.at(i).linesW.at(0).centerPoint, 1.0,
                                1.0, 1.0,
                                1.0, "line1" + to_string(i));
    }
    for (int i = 0; i < msg.shipParamOut.bottomHighestPoint.size(); ++i)
    {
        this->viewer->removeText3D("point" + to_string(i));
        PointT p = msg.shipParamOut.bottomHighestPoint.at(i);
        string text = Util::formatValue(p.x, 2) + "," + Util::formatValue(p.y, 2) + "," + Util::formatValue(p.z, 2);
        this->viewer->addText3D(text, p, 1.0, 1.0, 1.0, 1.0, "point" + to_string(i));
    }
    this->viewer->getRenderWindow()->GetInteractor()->Render();
    qvtkOpenglNativeWidget->update();
}

void MainWindow::updatePointCould()
{
    static PointCloudTPtr ptr(new PointCloudT);

    if (!this->lidarDriveInterface->get_lidar_data(ptr))
    {
        return;
    }

    std::string name = "All_cloud";
    this->viewer->removePointCloud(name);
    this->viewer->addPointCloud(ptr, name);
    this->viewer->updatePointCloud(ptr, name);

    this->viewer->getRenderWindow()->GetInteractor()->Render();
    qvtkOpenglNativeWidget->update();
}

void MainWindow::initPointCShow()
{
    qvtkOpenglNativeWidget = new QVTKOpenGLNativeWidget();

    auto renderer2 = vtkSmartPointer<vtkRenderer>::New();
    auto renderWindow2 = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    renderWindow2->AddRenderer(renderer2);
    this->viewer.reset(new pcl::visualization::PCLVisualizer(renderer2, renderWindow2, "All_cloud", false));

    qvtkOpenglNativeWidget->SetRenderWindow(viewer->getRenderWindow());
    viewer->setupInteractor(qvtkOpenglNativeWidget->GetInteractor(), qvtkOpenglNativeWidget->GetRenderWindow());
    qvtkOpenglNativeWidget->update();

    viewer->addCoordinateSystem(1.0);
    viewer->initCameraParameters();

    viewer->setCameraPosition(0, 0, 50, 0, 0, 0, 0, 0, 0);
}

MainWindow::~MainWindow()
{
}

void MainWindow::initParamsEvent(std::shared_ptr<ParamsEvent<ObserverFunc>> params_event_)
{
    params_event = params_event_;

    // std::lock_guard<std::mutex> LockGuard(params_event->getMylock());

    // params_event->getTotalParams().protocol_data.write_data.inCabinArea.inCabin_A_X = 998.998;
    // params_event->Notify(params_event->getTotalParams(), false);
}

void MainWindow::globalParamsCallback(TotalParams msg, bool save_flag)
{
    static TotalParams msg_ = msg;
    static bool fir_flag{false};

    if (MyUtil::compare_write_data((char *)&msg.baseParams, (char *)&msg.baseParams) && fir_flag != true)
    {
        fir_flag = true;
        this->add_lidar->ShowData(msg);
        viewer->setCameraPosition(msg.baseParams.lidarCameraBase.Pos_X, msg.baseParams.lidarCameraBase.Pos_Y, msg.baseParams.lidarCameraBase.Pos_Z,
                                  msg.baseParams.lidarCameraBase.View_X, msg.baseParams.lidarCameraBase.View_Y, msg.baseParams.lidarCameraBase.View_Z,
                                  msg.baseParams.lidarCameraBase.Up_X, msg.baseParams.lidarCameraBase.Up_Y, msg.baseParams.lidarCameraBase.Up_Z);
    }

    if (msg.log.flag == true)
    {
        msg.log.flag = false;
        diary->pushLogData(msg.log);
    }

    alarm->setLEDStatus(msg.alarm_status);
}

// bool compare_write_data(char *buf1, char *buf2)
// {
//     for (int i = 0; i < sizeof(buf1); i++)
//     {
//         if (buf1[i] != buf2[i])
//         {
//             return true;
//         }
//     }
//     return false;
// }

void MainWindow::params_set(TotalParams msg)
{
    // msg.printData();
    std::lock_guard<std::mutex> LockGuard(params_event->getMylock());
    msg.protocol_data = params_event->getTotalParams().protocol_data;
    params_event->getTotalParams() = msg;
    params_event->Notify(params_event->getTotalParams(), false);
    params_event->saveData();
}

void MainWindow::mainLayOut()
{

    this->mainLayout = new QVBoxLayout();
    this->headLayout = new QVBoxLayout();
    this->body_frame_layout = new QVBoxLayout();
    this->body_layout = new QHBoxLayout();
    this->left_body_layout = new QVBoxLayout();
    this->right_body_layout = new QVBoxLayout();

    this->right_camera_layout = new QHBoxLayout();
    this->right_data_layout = new QHBoxLayout();
    this->right_table_layout = new QHBoxLayout();

    this->vtkLayout = new QVBoxLayout();
    this->cameraLayout = new QVBoxLayout();

    this->right_camera_widget = new QWidget(this);
    this->right_data_widget = new QWidget(this);
    this->right_table_widget = new QWidget(this);

    this->main_widget = new QWidget(this);

    main_widget->setLayout(mainLayout);
    this->setCentralWidget(main_widget);

    mainLayout->addLayout(headLayout);
    mainLayout->addLayout(body_frame_layout);
    mainLayout->setStretchFactor(headLayout, 1);
    mainLayout->setStretchFactor(body_frame_layout, 15);

    body_frame_layout->addWidget(mainImageWidget);
    mainImageWidget->setLayout(body_layout);

    headLayout->addWidget(main_title_bar);

    body_layout->addLayout(left_body_layout);
    body_layout->addLayout(right_body_layout);
    body_layout->setStretchFactor(left_body_layout, 9);
    body_layout->setStretchFactor(right_body_layout, 6);

    cameraLayout->addWidget(camera_viewer2);
    imageWidget2->setLayout(cameraLayout);

    ///////////////////////////////////////////////////////////////////////////////

    auto a = new QWidget();
    auto b = new QWidget();

    // 设置背景黑色
    QPalette palBackGround(a->palette());
    palBackGround.setColor(QPalette::Background, QColor(23, 23, 23));
    a->setAutoFillBackground(true);
    a->setPalette(palBackGround);

    // 设置背景黑色
    QPalette palBackGround_b(b->palette());
    palBackGround_b.setColor(QPalette::Background, QColor(23, 23, 23));
    b->setAutoFillBackground(true);
    b->setPalette(palBackGround_b);

    right_body_layout->setMargin(0);
    right_camera_layout->setMargin(0);
    right_body_layout->setSpacing(0);
    right_camera_layout->setSpacing(0);

    ////////////////////////////////////////////////////////////////////////////////

    right_camera_layout->addWidget(a);
    right_camera_layout->addWidget(camera_viewer);
    right_camera_layout->addWidget(b);

    right_camera_layout->setStretchFactor(a, 1);
    right_camera_layout->setStretchFactor(camera_viewer, 7);
    right_camera_layout->setStretchFactor(b, 1);

    right_data_layout->addWidget(diary);
    right_data_layout->addWidget(alarm);
    right_data_layout->setStretchFactor(diary, 7);
    right_data_layout->setStretchFactor(alarm, 5);

    //    right_body_layout->addWidget(camera_viewer);
    right_body_layout->addLayout(right_camera_layout);
    right_body_layout->addLayout(right_data_layout);
    right_body_layout->addLayout(right_table_layout);
    right_body_layout->setStretchFactor(right_camera_layout, 1);
    right_body_layout->setStretchFactor(right_data_layout, 1);
    right_body_layout->setStretchFactor(right_table_layout, 1);

    //    layoutBottomMargin

    right_table_layout->addWidget(web_ui);

    imageWidget->setLayout(vtkLayout);
    vtkLayout->addWidget(qvtkOpenglNativeWidget);
    left_body_layout->addWidget(imageWidget);
    // left_body_layout->addWidget(camera_viewer);
}

/*删除layout*/
void MainWindow::deleteItem(QLayout *layout)
{
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr)
    {
        //        // setParent为NULL，防止删除之后界面不消失
        //        if (child->widget())
        //        {
        //            child->widget()->setParent(nullptr);
        //            // delete child->widget();
        //        }
        //        else if (child->layout())
        //        {
        //            deleteItem(child->layout());
        //            child->layout()->deleteLater();
        //        }
        child->widget()->setParent(nullptr);
        delete child;
    }
}

void MainWindow::initMenu()
{
    // QMenuBar *menuBar = this->menuBar();
    // add three menus
    fileMenu = new QMenu(tr("&File"), this);
    viewMenu = new QMenu(tr("&View"), this);
    helpMenu = new QMenu(tr("&About"), this);

    // add actions and add it into corresponding menu
    view_mode = new QAction(tr("&Mode"), this);
    view_mode->setShortcut(tr("ctrl+O"));
    view1_mode = new QAction(tr("&Mode1"), this);
    view1_mode->setShortcut(tr("ctrl+P"));
    view2_mode = new QAction(tr("&Mode2"), this);
    view2_mode->setShortcut(tr("ctrl+Q"));

    param_set = new QAction(tr("&Params"), this);
    lidar_area_set = new QAction(tr("&Areas"), this);

    connect(view_mode, SIGNAL(triggered(bool)), this, SLOT(view_mode_Action()));
    connect(view1_mode, SIGNAL(triggered(bool)), this, SLOT(view_mode1_Action()));
    connect(view2_mode, SIGNAL(triggered(bool)), this, SLOT(view_mode2_Action()));
    connect(param_set, SIGNAL(triggered(bool)), this, SLOT(param_set_Action()));
    connect(lidar_area_set, SIGNAL(triggered(bool)), this, SLOT(lidar_area_set_Action()));
}

void MainWindow::initToolBar()
{
    // add a toolbar and add its actions
    fileToolBar = new QToolBar(this);

    fileToolBar->addAction(view_mode);
    fileToolBar->addAction(view1_mode);
    fileToolBar->addAction(view2_mode);

    fileToolBar->addSeparator();

    fileToolBar->addAction(param_set);
    fileToolBar->addAction(lidar_area_set);

    // addToolBar(Qt::LeftToolBarArea,fileToolBar);
    addToolBar(Qt::BottomToolBarArea, fileToolBar);
    //    addToolBarBreak(Qt::BottomToolBarArea);
    //    addToolBar(Qt::BottomToolBarArea, toolBar);
}

void MainWindow::initConnect()
{
    QObject::connect(add_lidar, SIGNAL(SendSet(TotalParams)), this, SLOT(params_set(TotalParams)));
    QObject::connect(setROI, SIGNAL(sigChangeArea_index(int)), paint_area, SLOT(UpdateArea_index(int)));
    QObject::connect(setROI, SIGNAL(sigSaveAreaData()), this, SLOT(getAreaDatas()));
}

void MainWindow::createActions()
{
}

void MainWindow::param_set_Action()
{
    this->add_lidar->show();
}

void MainWindow::lidar_area_set_Action()
{
    this->setROI->show();
    this->setROI->showMaximized();
}

void MainWindow::view_mode_Action()
{
    deleteItem(body_frame_layout);
    body_frame_layout->addWidget(mainImageWidget);
    mainImageWidget->setLayout(body_layout);

    left_body_layout->addWidget(imageWidget);
}

void MainWindow::view_mode1_Action()
{
    deleteItem(body_frame_layout);
    body_frame_layout->addWidget(imageWidget);
}

void MainWindow::view_mode2_Action()
{
    deleteItem(body_frame_layout);
    body_frame_layout->addWidget(imageWidget2);
}

CameraViewer *MainWindow::getCameraWidget()
{
    return this->camera_viewer;
}

void MainWindow::getAreaDatas()
{
    std::lock_guard<std::mutex> LockGuard(params_event->getMylock());

    // 地面层
    QList<PointT> tmp = this->paint_area->area[0].Area2D_point;
    for (int j = 0; j < tmp.size(); j++)
    {
        cv::Point2d point2D(tmp[j].x, tmp[j].y);
        params_event->getTotalParams().baseParams.roiArea.ground.push_back(point2D);
    }

    // 地面xx层
    tmp.clear();
    tmp = this->paint_area->area[1].Area2D_point;
    for (int j = 0; j < tmp.size(); j++)
    {
        cv::Point2d point2D(tmp[j].x, tmp[j].y);
        params_event->getTotalParams().baseParams.roiArea.rectangle_ground.push_back(point2D);
    }

    // 夹板层
    tmp.clear();
    tmp = this->paint_area->area[2].Area2D_point;
    for (int j = 0; j < tmp.size(); j++)
    {
        cv::Point2d point2D(tmp[j].x, tmp[j].y);
        params_event->getTotalParams().baseParams.roiArea.ship.push_back(point2D);
    }

    params_event->Notify(params_event->getTotalParams(), false);

    params_event->saveData();
}

// implement slot functions
// void MainWindow::open()
//{

//}

// void MainWindow::print()
//{

//}

// void MainWindow::exit()
//{

//}

// void MainWindow::zoomIn()
//{

//}

// void MainWindow::zoomOut()
//{

//}

// void MainWindow::normalSize()
//{

//}

// void MainWindow::fitToWindow()
//{

//}

// void MainWindow::about()
//{

//}

// void MainWindow::aboutQt()
//{

//}
