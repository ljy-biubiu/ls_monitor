/***********************************************************
*  Copyright (c) 2022 LeiShenLidar . All rights reserved.
*  @filename    LED_RS232_API.cpp
*  @author      WuZhenFeng
*  @date        2022/7/15-17:07
*  @version     v1.0
************************************************************/



#ifndef PORTSECURITY_LED_RS232_API_H
#define PORTSECURITY_LED_RS232_API_H

#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <signal.h>

int StartAlarmLight();
void *test_fun(void *);
int LEDContrlAPI(int AlarmState);
void *ContrlPthread_func(void *);
void *RS232_ReceiveDataProcess(void *);
int RS232_SendBytes(int fd,  void * sendbuf, size_t count);
int CheckDataPackage(unsigned char *data_buff,unsigned int  rx_size);

#endif //PORTSECURITY_LED_RS232_API_H
