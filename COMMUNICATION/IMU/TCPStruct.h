#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <vector>

#define MAX_BYTE_NUM 1024 * 8 //从网络获取的最大字节数

struct Client {
	int id;
	std::string ip;
	int port;
};
struct NetPort {
	int conIdClient;
	int state;
	const char *ip;
	int port;
	struct sockaddr_in clientAddr;
};

struct DataBuff {
	unsigned char buff[MAX_BYTE_NUM];
	int size;
};


