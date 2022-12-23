//
// Created by ls on 2022/12/10.
//

#include "LPMSIG1.h"

namespace imu
{
    LPMSIG1::LPMSIG1()
    {
        imuData = {};
        imuDataCur = {};
        running = true;
        dataUsed = true;
    }

    void LPMSIG1::init()
    {
    }

    bool LPMSIG1::send_data(WriteData &msg)
    {
    }

    LPMSIG1::~LPMSIG1()
    {
    }

    void LPMSIG1::run()
    {

        // if (!lpmsig1.isDataUsed())
        // {
        //     imu::IMUData imuData = lpmsig1.getImuData();
        //     lpmsig1.printData(imuData);
        //     lpmsig1.setDataUsed(true);
        // }
        // else
        // {
        //     usleep(1000 * 1);
        // }

        // tcpClient.setIp("192.168.1.7");
        // tcpClient.setPort(8235);
        // int ret = tcpClient.connectTcp();
        // // int ret = 1;
        // if (ret > 0)
        // {
        //     running = true;
        // }
        // else
        // {
        //     running = false;
        // }
        // 启动获取数据线程
        /*boost::thread getData(boost::bind(&RadarHW::getRadarData, this));
        getData.detach();*/
        std::thread getData(&LPMSIG1::imuThread, this);
        getData.detach();
    }

    void LPMSIG1::globalParamsCallback(TotalParams msg, bool save_flag)
    {
        // this->my_port = msg.lowerMachineBase.port;
        // this->my_ip = msg.lowerMachineBase.ip;
    }

    bool LPMSIG1::imuThread()
    {

        tcpClient.setIp("192.168.0.62");
        tcpClient.setPort(8235);
        int ret = tcpClient.connectTcp();
        // int ret = 1;
        if (ret > 0)
        {
            running = true;
        }
        else
        {
            running = false;
        }

        int count = 0;
        double st = Util::timeMs();
        while (running)
        {
            st = Util::timeMs();
            tcpClient.getTcpData(); // 在线数据
            if (Util::timeMs() - st > 1000)
            {
                this->setStreamingMode();
            }
            if (tcpClient.dataBuff.size > 0)
            {
                // cout << "--------------------------------" << endl;
                /*for (int i = 0; i < tcpClient.dataBuff.size; ++i) {
                    cout << std::hex << (int) tcpClient.dataBuff.buff[i] << " ";
                }
                cout << endl;*/

                int len = tcpClient.dataBuff.size;
                unsigned char dataBuf[191];
                int validLen = 191;
                validLen = this->getValidData(tcpClient.dataBuff.buff, tcpClient.dataBuff.size, dataBuf, 191);
                // memcpy(dataBuf, tcpClient.dataBuff.buff, len);
                //                cout << dec << validLen << endl;
                if (validLen > 0)
                {
                    /* for (int i = 0; i < validLen; ++i) {
                         cout << std::hex << (int) dataBuf[i] << " ";
                     }
                     cout << endl;*/
                    count++;
                    imuDataCur = {};
                    imuDataCur.count = count;
                    imuDataCur.sensorId = dataBuf[2] * 256 + dataBuf[1];
                    imuDataCur.commandId = dataBuf[4] * 256 + dataBuf[3];
                    imuDataCur.timestamp = (dataBuf[10] * 256 * 256 * 256 + dataBuf[9] * 256 * 256 + dataBuf[8] * 256 + dataBuf[7]) * 0.002;
                    memcpy(imuDataCur.data.byte, dataBuf + 11, sizeof(imuDataCur.data.info));
                    //                    cout << "sizeof(imuDataCur.data.info) = " << dec << sizeof(imuDataCur.data.info) << endl;
                    /*for (int i = 0; i < sizeof(imuDataCur.data.info); ++i) {
                        cout << std::hex << (int) imuDataCur.data.byte[i] << " ";
                    }
                    cout << endl;*/

                    // this->printData(imuDataCur);

                    static int fitter_flag{0};
                    fitter_flag++;
                    if (fitter_flag %10== 0)
                    {
                        imuData = imuDataCur;
                        std::lock_guard<std::mutex> LockGuard(params_event->getMylock());

                        params_event->getTotalParams().protocol_data.read_data.quaternion_w = imuData.data.info.quaternion.w;
                        params_event->getTotalParams().protocol_data.read_data.quaternion_x = imuData.data.info.quaternion.x;
                        params_event->getTotalParams().protocol_data.read_data.quaternion_y = imuData.data.info.quaternion.y;
                        params_event->getTotalParams().protocol_data.read_data.quaternion_z = imuData.data.info.quaternion.z;

                        params_event->getTotalParams().protocol_data.read_data.x_roll = imuData.data.info.euler.x;
                        params_event->getTotalParams().protocol_data.read_data.y_pitch = imuData.data.info.euler.y;
                        params_event->getTotalParams().protocol_data.read_data.z_yaw = imuData.data.info.euler.z;

                        params_event->Notify(params_event->getTotalParams(), false);
                    }
                }
            }
        }
    }

    const IMUData &LPMSIG1::getImuData() const
    {
        return imuData;
    }

    void LPMSIG1::setImuData(const IMUData &_imuData)
    {
        LPMSIG1::imuData = _imuData;
    }

    bool LPMSIG1::isDataUsed() const
    {
        return dataUsed;
    }

    void LPMSIG1::setDataUsed(bool _dataUsed)
    {
        LPMSIG1::dataUsed = _dataUsed;
    }

    bool LPMSIG1::convertData(unsigned char *data, int startIndex, int n)
    {
        if (n <= 1)
        {
            return false;
        }
        int mid = std::floor(n / 2.0) + startIndex;
        int endIndex = startIndex + n - 1;
        for (int i = startIndex; i < mid; ++i)
        {
            unsigned char tmp = data[i];
            data[i] = data[endIndex - (i - startIndex)];
            data[endIndex - (i - startIndex)] = tmp;
        }
        return true;
    }

    int LPMSIG1::setStreamingMode()
    {
        char sendData[] = {0x3A, 0x01, 0x00, 0x07, 0x00, 0x00, 0x00, 0x08, 0x00, 0x0D, 0x0A};
        return tcpClient.sendTcpData(sendData, sizeof(sendData));
    }

    int LPMSIG1::getValidData(unsigned char *data, int dataLen, unsigned char *validData, int validDataLen)
    {
        /*for (int i = 0; i < dataLen; ++i) {
            cout << std::hex << (int) data[i] << " ";
        }
        cout << endl;*/
        int retLen = 0;
        for (int i = 0; i < dataLen - 190; ++i)
        {
            if (data[i] == 0x3a && data[i + validDataLen - 2] == 0x0d && data[i + validDataLen - 1] == 0x0a)
            {
                memcpy(validData, data + i, validDataLen);
                retLen = validDataLen;
            }
        }
        return retLen;
    }

    void LPMSIG1::printData(IMUData _imuData)
    {
        cout << "printData --------------------------------" << dec << endl;
        cout << "count = " << _imuData.count << endl;
        cout << "sensorId = " << _imuData.sensorId << endl;
        cout << "commandId = " << _imuData.commandId << endl;
        cout << "timestamp = " << _imuData.timestamp << endl;
        Param::Info info = _imuData.data.info;
        cout << "accRaw = " << info.accRaw.x << " , " << info.accRaw.y << " , " << info.accRaw.z << endl;
        cout << "accCalibrated = " << info.accCalibrated.x << " , " << info.accCalibrated.y << " , " << info.accCalibrated.z << endl;
        cout << "angularVel = " << info.angularVel.x << " , " << info.angularVel.y << " , " << info.angularVel.z << endl;
        cout << "quaternion = " << info.quaternion.w << " , " << info.quaternion.x << " , " << info.quaternion.y << " , " << info.quaternion.z << endl;
        cout << "euler = " << info.euler.x << " , " << info.euler.y << " , " << info.euler.z << endl;
        cout << "temperature = " << info.temperature << endl;
    }

} // imu