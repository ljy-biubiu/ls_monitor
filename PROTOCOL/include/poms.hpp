#ifndef POMS_H
#define POMS_H

/*recv ring buffer size*/
#define RECEIVE_BUFFER_SIZE 1024
#define BUF_SIZE 16

#include "memory.h"

//***********define GPFDP_info**************
struct GPFPD_INFO
{
    unsigned int GPSWeek{0}; // 自1980-1-6至当前的星期数
    char GPSTime[BUF_SIZE];  // 本周00：00：00至当前的秒数
    float Heading{0};        // 偏航角
    float Pitch{0};          // 俯仰角
    float Roll{0};           // 滚转角
    double Latitude{0};      // 纬度 deg
    double Longitude{0};     // 经度 deg  35
    float Altitude{0};       // 高度 m     29
    float Ve{0};             // 东 速度 m/s
    float Vn{0};             // 北 速度 m/s
    float Vu{0};             // 天 速度 m/s
    float Baseline{0};       // 基线长度
    int NSV1{0};             // 天线1卫星数
    int NSV2{0};             // 天线2卫星数
    char Status[4];          // 系统状态

    GPFPD_INFO()
    {
        memset(this->GPSTime, 0, BUF_SIZE);
        memset(this->Status, 0, 4);
    }
};
#endif
