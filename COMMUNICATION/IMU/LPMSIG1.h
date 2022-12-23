#ifndef LPMSIG1_H
#define LPMSIG1_H

#include <iostream>
#include <thread>
#include <cstring>
#include <cmath>
#include "TCPClient.h"
#include "Util.h"
#include "communication_interface.h"

using namespace std;

namespace imu
{
    struct Axis3f
    {
        float x;
        float y;
        float z;
    };
    struct Axis4f
    {
        float w;
        float x;
        float y;
        float z;
    };
    union Param
    {
        struct Info
        {
            Axis3f accRaw;                // 原始加速度，g
            Axis3f accCalibrated;         // 校准后加速度,g
            Axis3f gyroIRaw;              // 原始陀螺仪(GyroI)数据 (dps / rad/s)
            Axis3f gyroIIRaw;             // 原始陀螺仪(GyroII)数据 (dps / rad/s)
            Axis3f gyroIBiasCalibrated;   // 静止偏差校准后的陀螺仪(GyroI)数据 (dps / rad/s)
            Axis3f gyroIIBiasCalibrated;  // 静止偏差校准后的陀螺仪(GyroII)数据 (dps / rad/s)
            Axis3f gyroIAlignCalibrated;  // 坐标轴校准后的陀螺仪(GyroI)数据 (dps / rad/s)
            Axis3f gyroIIAlignCalibrated; // 坐标轴校准后的陀螺仪(GyroII)数据 (dps / rad/s)
            Axis3f magRaw;                // 原始磁力计数据 ( T)
            Axis3f magCalibrated;         // 校准后的磁力计数据 ( T)
            Axis3f angularVel;            // 角速度 (dps / rad/s)
            Axis4f quaternion;            // 四元数 (归一化单位)
            Axis3f euler;                 // 欧拉角数据 (deg / rad)
            Axis3f linearAcc;             // 线性加速度 (g)
            // Axis3f pressure;
            // Axis3f altitude;
            float temperature; // 温度 (°C)
        } info = {};
        unsigned char byte[sizeof(info)];
    };

    struct IMUData
    {
        int sensorId;
        int commandId;
        double timestamp; // 时间戳 (500Hz 更新率,即 0.002s)
        Param data;
        int count;
    };

    struct ParamIn
    {
        string ip;
        int port;

        ParamIn()
        {
            ip = "192.168.1.7";
            port = 8235;
        }

        ParamIn(string _ip, int _port)
        {
            ip = _ip;
            port = _port;
        }
    };

    class LPMSIG1 : public ComunicateInterface
    {
    public:
        LPMSIG1();

        ~LPMSIG1();

    public:
        virtual void run() override;
        virtual void init() override;
        virtual bool send_data(WriteData &msg) override;
        virtual void globalParamsCallback(TotalParams msg, bool save_flag) override;
        

        void printData(IMUData _imuData);

    public:
        const IMUData &getImuData() const;

        void setImuData(const IMUData &imuData);
        bool isDataUsed() const;

        void setDataUsed(bool _dataUsed);

    private:
        ParamIn param;
        IMUData imuData, imuDataCur;
        TCPClient tcpClient;
        bool dataUsed;
        bool running;

    private:
        bool imuThread();

        bool convertData(unsigned char *data, int startIndex, int n);

        int setStreamingMode();

        int getValidData(unsigned char *data, int dataLen, unsigned char *validData, int validDataLen);
    };

} // imu

#endif // CHAT_PLC_H