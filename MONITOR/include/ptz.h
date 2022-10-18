#ifndef PTZ_H
#define PTZ_H

#include <QObject>
#include <HCNetSDK.h>
#include <QThread>
#include <QMutex>
#include <QFrame>
#include <QMouseEvent>
#include <QTextStream>
#include <QSettings>
#include "math.h"


class PTZ : public QThread
{
    Q_OBJECT
public:
    PTZ();

    void PTZ_init();
    void PTZ_Left(int speed , int flag);/*左移*/

    void PTZ_Right(int speed , int flag);/*右移*/

    void PTZ_Up(int speed , int flag);/*上移*/

    void PTZ_Down(int speed , int flag);/*下移*/

    void PTZ_Zoom_In(int speed , int flag);/**/
    void PTZ_Zoom_Out(int speed , int flag);/**/

    void PTZ_Focus_Near(int speed , int flag);/**/
    void PTZ_Focus_Far(int speed , int flag);/**/

    void PTZ_Iris_Open(int speed , int flag);/**/
    void PTZ_Iris_Close(int speed , int flag);/**/

    void PTZ_Cruise_Open(); //巡航开始
    void PTZ_Cruise_Close(); //巡航结束

    void FollowTarget(float Angle,float Dist);//追踪目标

    void *ReadCamera(void *IpParameter);

    bool PTZ_GOTO_Preset(int num);


    void getPara();
    void mouseReleaseEvent(QMouseEvent *);


    int ToHex(int n);

    QString cam_IP;
    QString cam_ID;
    QString cam_Pass;
    int PTZPreset_num;
    float war_ang;
    float war_dist;
    float war_horizontal;
    float war_azimuth;
    float ang;
    float dist;
    int num = 6;
    QString error;
    QString mas;
    bool isRun;
    int m_sock;
    QMutex m_lock;
    void run();

    LONG lUserID;

    LONG lRealPlayHandle;


signals:


public slots:
    void OnButtonUpChanged();
    void OffButtonUpChanged();
    void OnButtonDownChanged();
    void OffButtonDownChanged();
    void OnButtonLeftChanged();
    void OffButtonLeftChanged();
    void OnButtonRightChanged();
    void OffButtonRightChanged();
    //调焦
    void OnButtonInChanged();
    void OffButtonInChanged();
    void OnButtonOutChanged();
    void OffButtonOutChanged();

    //聚焦
    void OnButtonNearChanged();
    void OffButtonNearChanged();
    void OnButtonFarChanged();
    void OffButtonFarChanged();

    //光圈
    void OnButtonOpenChanged();
    void OffButtonOpenChanged();
    void OnButtonCloseChanged();
    void OffButtonCloseChanged();


private:
    int currentnum;

};

#endif // PTZ_H
