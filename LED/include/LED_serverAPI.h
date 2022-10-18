#ifndef LED_SERVER_API_H
#define LED_SERVER_API_H
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

int StartAlarmLight_IP();
int LEDContrlAPI_IP(const char *chose_ip,unsigned char AlarmState);
void DisplayListDeviceInfo_IP();
void *ContrlPthread_func_IP(void *);
void *SocketPthread_func_IP(void *);
void *test_fun_IP();
#endif // LED_SERVER_API_H
