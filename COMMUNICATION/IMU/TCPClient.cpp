
#include "TCPClient.h"

TCPClient::TCPClient() {
    netPort.conIdClient = -1;
    netPort.state = -1;
}

TCPClient::TCPClient(const char *_ip, int _port) {
    netPort.ip = _ip;
    netPort.port = _port;
    netPort.conIdClient = -1;
    netPort.state = -1;
}

TCPClient::~TCPClient() {
    this->closeTcp();
}

int TCPClient::connectTcp() {
    netPort.clientAddr.sin_family = AF_INET;
    netPort.clientAddr.sin_port = htons(netPort.port);
    netPort.clientAddr.sin_addr.s_addr = inet_addr(netPort.ip);
    // 创建
    int connectNum = 0;// 重连计数
    while ((netPort.state < 0 || netPort.conIdClient < 0) && connectNum < 3) {
        netPort.conIdClient = socket(AF_INET, SOCK_STREAM, 0);
        std::cout << "netPort.conIdClient = " << netPort.conIdClient << std::endl;

        int opt;
        socklen_t len = sizeof(int);
        int clientState = getsockopt(netPort.conIdClient, SOL_SOCKET, SO_KEEPALIVE, &opt, (socklen_t *) &len);
        std::cout << "opt = " << opt << std::endl;
        std::cout << "clientState = " << clientState << std::endl;

        if (netPort.conIdClient >= 0) {
            // 向服务器发出连接请求
            netPort.state = connect(netPort.conIdClient, (struct sockaddr *) &netPort.clientAddr, sizeof(netPort.clientAddr));
            std::cout << "netPort.state = " << netPort.state << std::endl;
            if (netPort.state < 0) {
                this->closeTcp();
                sleep(1);
                connectNum++;
                std::cout << netPort.ip << ":" << netPort.port << ", connect again ......" << connectNum << std::endl;
            }
        }
    }
    if (netPort.state < 0 || netPort.conIdClient < 0) {
        this->closeTcp();
        return -1;
    }
    // set socket timeout
    struct timeval timeOut{2, 0};
    setsockopt(netPort.conIdClient, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeOut, sizeof(struct timeval));
    return 1;
}

void TCPClient::getTcpData() {
    int opt;
    socklen_t len = sizeof(int);
    int clientState = getsockopt(netPort.conIdClient, SOL_SOCKET, SO_KEEPALIVE, &opt, (socklen_t *) &len);

    dataBuff.size = recv(netPort.conIdClient, reinterpret_cast<char *>(dataBuff.buff), sizeof(dataBuff.buff), 0);
    //std::cout << "dataBuff.size = " << dataBuff.size << std::endl;
    //std::cout << "opt = " << opt << std::endl;
    //std::cout << "clientState = " << clientState << std::endl;
    if (dataBuff.size <= 0) {
        this->closeTcp();
        netPort.state = -1;
        netPort.conIdClient = -1;
        this->connectTcp();
    }
}

void TCPClient::closeTcp() {
    close(netPort.conIdClient);
    shutdown(netPort.conIdClient, SHUT_RDWR);
}

const std::string &TCPClient::getIp() const {
    return ip;
}

void TCPClient::setIp(const std::string &_ip) {
    TCPClient::ip = _ip;
    netPort.ip = _ip.c_str();
}

int TCPClient::getPort() const {
    return port;
}

void TCPClient::setPort(int _port) {
    TCPClient::port = _port;
    netPort.port = _port;
}

int TCPClient::sendTcpData(char *data, int len) {
    int sendLen = send(netPort.conIdClient, data, len, MSG_NOSIGNAL);
    return sendLen;
}


