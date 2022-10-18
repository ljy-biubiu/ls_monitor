#ifndef GETLIDARC16_H
#define GETLIDARC16_H

#include <QObject>
#include <QObject>
#include <QThread>
#include <iostream>
#include <QMetaType>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <QMutex>

#include <common.h>


Q_DECLARE_METATYPE(LidarData);
class GetlidarC16:public QThread
{
    Q_OBJECT
public:
    GetlidarC16(const int port);

    int count = 0;
    bool contrl = false;

    void udp_init(int* sock_num, sockaddr_in* sockaddr, int server_port);
    void UnInitialize(int *sock_num);
    int m_sock;
    QMutex m_lock;
    void run();

    int sock1;
    struct sockaddr_in addr1;
    struct sockaddr_in clientAddr1;

signals:
    void SendData(LidarData lidardata);
};


#endif // GETLIDARC16_H
