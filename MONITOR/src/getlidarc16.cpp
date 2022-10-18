#include "getlidarc16.h"
#include <QDebug>

GetlidarC16::GetlidarC16(const int port)
{
    LidarData lidardata;
    QVariant DataVar;
    DataVar.setValue(lidardata);
    qRegisterMetaType<QVariant>("QVariant");
    udp_init(&sock1,&clientAddr1,port);
}


void GetlidarC16::udp_init(int* sock_num, sockaddr_in* sockaddr, int server_port)
{
    UnInitialize(sock_num);
    sockaddr->sin_family = AF_INET;
    sockaddr->sin_addr.s_addr = htonl(INADDR_ANY);
    sockaddr->sin_port = htons(server_port);
    *sock_num = socket(AF_INET, SOCK_DGRAM, 0);
    bind(*sock_num, (struct sockaddr *)sockaddr, sizeof(*sockaddr));
}

void GetlidarC16::UnInitialize(int* sock_num)
{
    shutdown(*sock_num,SHUT_RDWR);
}


void GetlidarC16::run()
{
    unsigned int size = sizeof(sockaddr_in);
    clientAddr1 =addr1;

    int recvLen;
    char recvBuf[1206] = { 0 };
    u_char data[1206] = { 0 };
    LidarData lidardata;
    lidardata.distance.resize(16);
    lidardata.intensity.resize(16);
    lidardata.LaserID.resize(16);

    while(1)
    {
        recvLen = recvfrom(sock1, recvBuf, sizeof(recvBuf), 0,(struct sockaddr*)&(clientAddr1), &size);

        //每个包(Packet)包含 12 个发射序列的数据。每个数据块只返回一个方位角。
        if (recvLen >= 1206) //一个数据包
        {
            memset(data,0,1206);
            memcpy(data, recvBuf, 1206);
            if (data[0] == 0xff && data[1] == 0xee)//
            {
                for (int i = 0; i < 12; i = i + 2)  //LS16线协议和Velodyne有区别
                {
                    if ((data[3 + 100 * i] * 256 + data[2 + 100 * i]) / 100.f >= 360.0)
                    {
                        lidardata.angle.push_back(0);
                    }
                    else
                    {
                        lidardata.angle.push_back((data[3 + 100 * i] * 256 + data[2 + 100 * i]) / 100.f);        //提取出一圈中的方位角度值
                    }
                    for (int j = 0; j < 16; j++)
                    {
                        lidardata.distance[j].push_back((data[5 + 3 * j + 100 * i] * 256 + data[4 + 3 * j + 100 * i]));
                        lidardata.intensity[j].push_back(data[6 + 3 * j + 100 * i]);
                        lidardata.LaserID[j].push_back(j);
                    }
                    if (lidardata.angle.size() >= 2)
                    {
                        if (lidardata.angle[lidardata.angle.size() - 1] < 1.0 && lidardata.angle[lidardata.angle.size() - 2] > 359.0)
                        {
                            if (lidardata.angle[lidardata.angle.size() - 1] + lidardata.angle[lidardata.angle.size() - 2] > 360.0)
                            {
                                lidardata.angle.push_back(lidardata.angle[lidardata.angle.size() - 1] + lidardata.angle[lidardata.angle.size() - 2] - 360.0);
                            }
                            else
                            {
                                lidardata.angle.push_back(lidardata.angle[lidardata.angle.size() - 2] + 0.2);
                            }
                        }
                        else
                        {
                            lidardata.angle.push_back((lidardata.angle[lidardata.angle.size() - 1] + lidardata.angle[lidardata.angle.size() - 2]) / 2);  //插入后半部数据
                        }
                        for (int j = 0; j < 16; j++)
                        {
                            lidardata.distance[j].push_back((data[53 + 3 * j + 100 * i] * 256 + data[52 + 3 * j + 100 * i]));
                            lidardata.intensity[j].push_back(data[54 + 3 * j + 100 * i]);
                            lidardata.LaserID[j].push_back(j);

                        }
                    }
                    if (lidardata.angle[lidardata.angle.size() - 1] >= 90 && lidardata.angle[lidardata.angle.size() - 1] <= 91 && lidardata.angle.size() > 1500 && lidardata.angle.size()<5000)
                    {
                        emit SendData(lidardata);


                        msleep(20);
                        lidardata.angle.clear();
                        lidardata.LaserID.clear();
                        lidardata.LaserID.resize(16);
                        lidardata.distance.clear();
                        lidardata.distance.resize(16);
                        lidardata.intensity.clear();
                        lidardata.intensity.resize(16);
                    }
                    if (lidardata.angle.size() >= 5000){
                        lidardata.angle.clear();
                        lidardata.LaserID.clear();
                        lidardata.LaserID.resize(16);
                        lidardata.distance.clear();
                        lidardata.distance.resize(16);
                        lidardata.intensity.clear();
                        lidardata.intensity.resize(16);
                    }
                }
            }
        }
        else
        {
            sleep(1);
        }
    }

}
