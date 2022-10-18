#ifndef ALGONRITHM_H
#define ALGONRITHM_H

#include <QObject>
#include <QThread>
#include <common.h>
#include <opencv2/opencv.hpp>
#include <memory>
#include "paintarea.h"
//#include <pcl/common/common.h>
//#include <pcl/sample_consensus/ransac.h>
//#include <pcl/sample_consensus/sac_model_line.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/filters/passthrough.h>
#include "grid_height_difference.h"

struct PassThroughConfig
{
    float kx_min;
    float kx_max;
    float ky_min;
    float ky_max;
    float kz_min;
    float kz_max;
};

class Algonrithm : public QThread
{
    Q_OBJECT
public:
    Algonrithm(const float resolution,const float difference_threshold);
    void run();
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr tCloud;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr filttCloud[AREAS];
    std::vector<cv::Point2f> points[3];//opencv方法
    void useRANSAC(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_in, pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_out,
                                 pcl::ModelCoefficients &coefficients, int sac_model, int max_iterations, float threshold);
    void passThrough(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_in, pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_out, std::shared_ptr<PassThroughConfig> config);
    inline
    void getGridHeightDifference(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_in, pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_out, float resolution, float difference_threshold);

    float zmin=-10,zmax=10,xmin=0,xmax=10,ymin=0,ymax=10;

     Area area[AREAS];
     void setResolution(const float resolution);
     void setDifference_threshold(const float difference_threshold);
private:
    float m_resolution;
    float m_difference_threshold;

signals:
     void sigShow(lidarIntruder cloud );

public slots:


};

#endif // ALGONRITHM_H
