#ifndef CHAT_PLC_H
#define CHAT_PLC_H

// tcp客户端端的代码
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

#include "communication_interface.h"
#include "protocol.hpp"

class ChatPlc : public ComunicateInterface
{
public:
    // using ComunicateInterface::ComunicateInterface;

    virtual void run() override;
    virtual void init() override;
    virtual void globalParamsCallback(TotalParams msg, bool save_flag) override;

    void init_thread();

    bool tcp_init();

    void UnInitialize();

    void packData(char *buf, const ReadData &msg);

    virtual bool send_data(WriteData &msg) override;

    void anlysisReceiveData();

    bool ask_read_data();

    void sendWriteDataEvent();

    // bool get_lidar_data(pcl::PointCloud<pcl::PointXYZRGB>::Ptr msg);

private:
    struct sockaddr_in myaddr;
    struct sockaddr_in myClientAddr;
    int my_sockfd;
    bool rece_read_data_flag{false};

    AskPlcReadHead ask_plc_read;
    ReturnAskPlcReadHead ret_head;
    PlcWriteHead write_head;

    unsigned char buff[RECEIVE_BUFFER_SIZE] = {0};
};

#endif // CHAT_PLC_H
