#ifndef GETLIDARCH128X1
#define GETLIDARCH128X1

#include "getlidarc16.h"

Q_DECLARE_METATYPE(LidarDataCHXXX);
class GetlidarCH128X1:public GetlidarC16
{
    Q_OBJECT
public:
    // 使用继承构造函数
    using GetlidarC16::GetlidarC16;
    void run() override;
signals:
    void SendData(LidarDataCHXXX lidardata);
};


#endif // GETLIDARCH128X1
