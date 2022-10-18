#ifndef LIDARCLUSTEM_H
#define LIDARCLUSTEM_H
#include <QObject>
#include <QThread>
#include <QDebug>
#include "lidarroaddetect.h"
#include "QMutex"
#include "common_struct.h"

class LidarClustem : public QThread
{
    Q_OBJECT

public:
    LidarClustem();

    ~LidarClustem();

    void run();

    QMutex m_lock;
    bool m_stop;
    std::vector<Cloud_Point>* lidar_points;
    void setClusterTolerance(const float clusterTolerance);
    void setMinClusterSize(const int  minClusterSize);
    void setMaxClusterSize(const int  maxClusterSize);
signals:
    void SendClus_Object(QVariant dataVar2);


private:
    LidarRoadDetect *lidarroaddetect;
    float m_clusterTolerance;
    int  m_minClusterSize;
    int  m_maxClusterSize;
};

#endif // LIDARCLUSTEM_H
