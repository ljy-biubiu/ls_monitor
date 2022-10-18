#include "lidarclustem.h"


LidarClustem::LidarClustem()
{
    lidar_points = new std::vector<Cloud_Point>;
    lidarroaddetect = new LidarRoadDetect();

    m_stop = false;

}

LidarClustem::~LidarClustem()
{
    delete lidar_points;
    delete lidarroaddetect;
}


void LidarClustem::run()
{
    Clustem_Obj Cl_obj;


    Cl_obj.Obj = new std::vector<Object>;
    qRegisterMetaType<QVariant>("QVariant");

    QVariant var;

    // TODO:Memory Leaking, No Delect
    std::vector<Object>* all_objects_out = new (std::vector<Object>);


    //lidar_points为防护区域内点云
    lidarroaddetect->LidarCluster(lidar_points, all_objects_out,m_clusterTolerance,m_minClusterSize,m_maxClusterSize);

    m_stop = false;

    // qDebug()<< "all_objects_out->size()" << all_objects_out->size();
    Cl_obj.Obj->clear();
    for (int i = 0; i < all_objects_out->size(); i++)
    {
        Cl_obj.Obj->push_back(all_objects_out->at(i));
    }
    var.setValue(Cl_obj);

    emit SendClus_Object(var);


}


void LidarClustem::setClusterTolerance(const float clusterTolerance)
{
    m_clusterTolerance = clusterTolerance;
}
void LidarClustem::setMinClusterSize(const int  minClusterSize)
{
    m_minClusterSize = minClusterSize;
}
void LidarClustem::setMaxClusterSize(const int  maxClusterSize)
{
    m_maxClusterSize = maxClusterSize;
}

