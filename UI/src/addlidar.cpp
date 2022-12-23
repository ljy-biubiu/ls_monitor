#include "addlidar.h"
#include "ui_addlidar.h"
#include "QMetaType"
#include <QIntValidator>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QRegExp>
#include <QDebug>

AddLidar::AddLidar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLidar)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/leishen.ico"));
    setModal(true);
    //setFixedSize(size());
    this->setWindowFlags(Qt::FramelessWindowHint);
    //ui->widget->setParentWidget(this);
    //ui->widget->setTitleName(QStringLiteral("摄像头设置"));
    ui->comboBox->setEditable(true);
    ui->comboBox->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->comboBox->lineEdit()->setReadOnly(true);
//    ShowData();


}

AddLidar::~AddLidar()
{
    delete ui;
}

void AddLidar::initcombox(QList<int> &items)
{

}
void AddLidar::ShowData(TotalParams &msg)
{
    msg_ = msg;
    //ui->view_x_3->setText(QString("%1").arg(data.setDis));

    //ui->JDis->setText(QString("%1").arg(data.setDis));
    //ui->JAngle->setText(QString("%1").arg(msg_.baseParams.lidarPreset.  .setAng));
    ui->XAngle->setText(QString("%1").arg(msg_.baseParams.lidarPreset.XAngle));
    ui->YAngle->setText(QString("%1").arg(msg_.baseParams.lidarPreset.YAngle));
    ui->ZAngle->setText(QString("%1").arg(msg_.baseParams.lidarPreset.ZAngle));

    ui->base_x->setText(QString("%1").arg(msg_.baseParams.lidarPreset.Base_X));
    ui->base_y->setText(QString("%1").arg(msg_.baseParams.lidarPreset.Base_Y));
    ui->base_z->setText(QString("%1").arg(msg_.baseParams.lidarPreset.Base_Z));

    ui->setradius->setText(QString("%1").arg(msg_.baseParams.lidarPreset.paintarea_Radius));
    //ui->clusterTolerance->setText(QString("%1").arg(msg_.baseParams.lidarCluster.ClusterTolerance));

    //ui->minClusterSize->setText(QString("%1").arg(msg_.baseParams.lidarCluster.MinClusterSize));
    //ui->maxClusterSize->setText(QString("%1").arg(msg_.baseParams.lidarCluster.MaxClusterSize));
    //ui->resolution->setText(QString("%1").arg(msg_.baseParams.lidarCluster.Resolution));
    //ui->difference_threshold->setText(QString("%1").arg(msg_.baseParams.lidarCluster.Difference_threshold));

    ui->comboBox->setCurrentText(QString(msg_.baseParams.lidarBase.LidarModel));
    ui->pos_x->setText(QString("%1").arg(msg_.baseParams.lidarCameraBase.Pos_X));
    ui->pos_y->setText(QString("%1").arg(msg_.baseParams.lidarCameraBase.Pos_Y));
    ui->pos_z->setText(QString("%1").arg(msg_.baseParams.lidarCameraBase.Pos_Z));
    ui->up_x->setText(QString("%1").arg(msg_.baseParams.lidarCameraBase.Up_X));
    ui->up_y->setText(QString("%1").arg(msg_.baseParams.lidarCameraBase.Up_Y));
    ui->up_z->setText(QString("%1").arg(msg_.baseParams.lidarCameraBase.Up_Z));
    ui->view_x->setText(QString("%1").arg(msg_.baseParams.lidarCameraBase.View_X));
    ui->view_y->setText(QString("%1").arg(msg_.baseParams.lidarCameraBase.View_Y));
    ui->view_z->setText(QString("%1").arg(msg_.baseParams.lidarCameraBase.View_Z));

    ui->lidarPort->setText(QString("%1").arg(msg_.baseParams.lidarBase.lidarPort));
    //ui->kValue->setText(QString("%1").arg(msg_.baseParams.lidarCluster.Kvalue));

    ui->dataAddress->setText(QString::fromStdString(msg_.baseParams.lidarBase.DataAddress));
    ui->lidarAddress->setText(QString::fromStdString(msg_.baseParams.lidarBase.LidarAddress));
    ui->serverIP->setText(QString::fromStdString(msg_.baseParams.lidarBase.ServerAddress));
    ui->serverPort->setText(QString("%1").arg(msg_.baseParams.lidarBase.ServerPort));


    ui->camera_ip->setText(QString::fromStdString(msg_.baseParams.cameraBase.ip));
    ui->camera_name->setText(QString::fromStdString(msg_.baseParams.cameraBase.name));
    ui->camera_key->setText(QString::fromStdString(msg_.baseParams.cameraBase.code));
    ui->lower_machine_ip->setText(QString::fromStdString(msg_.baseParams.lowerMachineBase.ip));
    ui->lower_machine_port->setText(QString("%1").arg(msg_.baseParams.lowerMachineBase.port));


    ui->gound_grid_X->setText(QString("%1").arg( msg_.baseParams.groundParamIn.gridNumX));
    ui->gound_grid_Y->setText(QString("%1").arg(msg_.baseParams.groundParamIn.gridNumY));
    ui->gound_max_angle->setText(QString("%1").arg(msg_.baseParams.groundParamIn.max_monitor_angle));
    ui->gound_min_angle->setText(QString("%1").arg(msg_.baseParams.groundParamIn.min_monitor_angle));

    ui->ship_grid_X->setText(QString("%1").arg(msg_.baseParams.shipParamIn.gridNumX));
    ui->ship_grid_Y->setText(QString("%1").arg(msg_.baseParams.shipParamIn.gridNumY));
    ui->ship_max_angle->setText(QString("%1").arg(msg_.baseParams.shipParamIn.max_monitor_angle));
    ui->ship_min_angle->setText(QString("%1").arg(msg_.baseParams.shipParamIn.min_monitor_angle));
    ui->ship_bound_radius->setText(QString("%1").arg(msg_.baseParams.shipParamIn.boundRadius));
    ui->ship_normal_radius->setText(QString("%1").arg(msg_.baseParams.shipParamIn.normalRadius));


}

void AddLidar::on_btn_sure_clicked()
{
//    data.setDis = ui->JDis->text().toFloat();
//    data.setAng = ui->JAngle->text().toFloat();//设置预置点时的每份角度
    msg_.baseParams.lidarPreset.XAngle = ui->XAngle->text().toFloat();
    msg_.baseParams.lidarPreset.YAngle = ui->YAngle->text().toFloat();
    msg_.baseParams.lidarPreset.ZAngle = ui->ZAngle->text().toFloat();
    msg_.baseParams.lidarPreset.Base_X = ui->base_x->text().toFloat();
    msg_.baseParams.lidarPreset.Base_Y = ui->base_y->text().toFloat();
    msg_.baseParams.lidarPreset.Base_Z = ui->base_z->text().toFloat();

    msg_.baseParams.lidarPreset.paintarea_Radius = ui->setradius->text().toFloat();
    //msg_.baseParams.lidarCluster.ClusterTolerance = ui->clusterTolerance->text().toFloat();
    //msg_.baseParams.lidarCluster.MinClusterSize = ui->minClusterSize->text().toInt();

    //msg_.baseParams.lidarCluster.MaxClusterSize = ui->maxClusterSize->text().toInt();
    //msg_.baseParams.lidarCluster.Resolution = ui->resolution->text().toFloat();
    //msg_.baseParams.lidarCluster.Difference_threshold = ui->difference_threshold->text().toFloat();

    msg_.baseParams.lidarBase.LidarModel = ui->comboBox->currentText().toInt();
    msg_.baseParams.lidarCameraBase.Pos_X = ui->pos_x->text().toFloat();
    msg_.baseParams.lidarCameraBase.Pos_Y = ui->pos_y->text().toFloat();
    msg_.baseParams.lidarCameraBase.Pos_Z = ui->pos_z->text().toFloat();
    msg_.baseParams.lidarCameraBase.Up_X = ui->up_x->text().toFloat();
    msg_.baseParams.lidarCameraBase.Up_Y = ui->up_y->text().toFloat();
    msg_.baseParams.lidarCameraBase.Up_Z = ui->up_z->text().toFloat();
    msg_.baseParams.lidarCameraBase.View_X = ui->view_x->text().toFloat();
    msg_.baseParams.lidarCameraBase.View_Y = ui->view_y->text().toFloat();
    msg_.baseParams.lidarCameraBase.View_Z = ui->view_z->text().toFloat();

    msg_.baseParams.lidarBase.lidarPort = ui->lidarPort->text().toInt();
    //msg_.baseParams.lidarCluster.Kvalue = ui->kValue->text().toFloat();

    //data.distance = ui->distance->text().toFloat();
    msg_.baseParams.lidarBase.DataAddress = ui->dataAddress->text().toStdString();
    msg_.baseParams.lidarBase.LidarAddress = ui->lidarAddress->text().toStdString();
    msg_.baseParams.lidarBase.ServerAddress = ui->serverIP->text().toStdString();
    msg_.baseParams.lidarBase.ServerPort = ui->serverPort->text().toInt();


    msg_.baseParams.cameraBase.ip = ui->camera_ip->text().toStdString();
    msg_.baseParams.cameraBase.name = ui->camera_name->text().toStdString();
    msg_.baseParams.cameraBase.code = ui->camera_key->text().toStdString();

    msg_.baseParams.lowerMachineBase.ip = ui->lower_machine_ip->text().toStdString();
    msg_.baseParams.lowerMachineBase.port = ui->lower_machine_port->text().toInt();

    msg_.baseParams.groundParamIn.gridNumX = ui->gound_grid_X->text().toFloat();
    msg_.baseParams.groundParamIn.gridNumY = ui->gound_grid_Y->text().toFloat();
    msg_.baseParams.groundParamIn.max_monitor_angle = ui->gound_max_angle->text().toDouble();
    msg_.baseParams.groundParamIn.min_monitor_angle = ui->gound_min_angle->text().toDouble();

    msg_.baseParams.shipParamIn.gridNumX = ui->ship_grid_X->text().toFloat();
    msg_.baseParams.shipParamIn.gridNumY = ui->ship_grid_Y->text().toFloat();
    msg_.baseParams.shipParamIn.max_monitor_angle = ui->ship_max_angle->text().toDouble();
    msg_.baseParams.shipParamIn.min_monitor_angle = ui->ship_min_angle->text().toDouble();
    msg_.baseParams.shipParamIn.boundRadius = ui->ship_bound_radius->text().toFloat();
    msg_.baseParams.shipParamIn.normalRadius = ui->ship_normal_radius->text().toFloat();

//    GroundParamIn groundParamIn;
//    ShipParamIn shipParamIn;


    emit SendSet(msg_);
    this->close();
}

void AddLidar::on_btn_no_clicked()
{
    this->close();
}
