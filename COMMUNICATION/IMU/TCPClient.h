#pragma once

#include <iostream>
#include <cstring>
#include "TCPStruct.h"

class TCPClient {
public:
    TCPClient();

    TCPClient(const char *_ip, int _port);

    ~TCPClient();

    DataBuff dataBuff{};//字节缓存

    int connectTcp();

    void getTcpData();

    int sendTcpData(char *data,int len);

    void closeTcp();

public:
    const std::string &getIp() const;

    void setIp(const std::string &_ip);

    int getPort() const;

    void setPort(int _port);

private:
    NetPort netPort{};
    std::string ip;
    int port;

};

