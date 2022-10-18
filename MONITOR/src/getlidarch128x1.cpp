#include "getlidarch128x1.h"
#include <QDebug>

void GetlidarCH128X1::run()
{
    unsigned int size = sizeof(sockaddr_in);
    clientAddr1 =addr1;
	char recvBuf[1206] = {0};
	int recvLen;
    LidarDataCHXXX lidardata;
    lidardata.angle.resize(128);
    lidardata.distance.resize(128);
    lidardata.intensity.resize(128);
    std::vector<std::vector<float> >angle;
    std::vector<std::vector<float> >distance;
    std::vector<std::vector<int> >intensity;
    angle.clear();
    angle.resize(128);
    distance.clear();
    distance.resize(128);
    intensity.clear();
    intensity.resize(128);
	while (true)
	{
        recvLen = recvfrom(sock1, recvBuf, sizeof(recvBuf), 0, (struct sockaddr *)&clientAddr1, &size);
        if (recvLen > 0)
		{
			std::vector<unsigned char> data;
			for (int i = 0; i < 1200; i++)
			{
				data.push_back(recvBuf[i]);
			}
			for (int i = 0; i < 1197; i+=7) 
			{
				
				if(data[i] == 0xff && data[i + 1] == 0xaa && data[i + 2] == 0xbb && data[i + 3] == 0xcc && data[i + 4] == 0xdd && data[i + 5] == 0xee && data[i + 6] == 0x11)
				{
                    lidardata.distance.clear();
                    lidardata.intensity.clear();
                    lidardata.angle.clear();
					if (lidardata.angle.empty())
					{
						lidardata.distance = distance;
						lidardata.intensity = intensity;
						lidardata.angle = angle;
                        emit SendData(lidardata);
                        //std::cout << "192.168.1.102" << std::endl;
					}
					angle.clear();
					angle.resize(128);
					distance.clear();
					distance.resize(128);
					intensity.clear();
					intensity.resize(128);
				}
				else
				{				
					int linenum = data[i];
					angle[linenum].push_back((data[i + 1] * 256 + data[i + 2]) / 100.f);
					distance[linenum].push_back((data[3 + i] * 256 + data[4 + i] + data[5 + i] / 256.f) / 100.f);
					intensity[linenum].push_back(data[6 + i]);		
				}
			}
		}
	}
}


