#pragma once
#ifndef LIDARROADDETECT_H
#define LIDARROADDETECT_H
//#include "stdafx.h"

#include "common_struct.h"
#include <Eigen/Dense>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <opencv2/opencv.hpp>
#include <math.h>

#include <iostream>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/project_inliers.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/features/normal_3d.h>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/segmentation/extract_clusters.h>
#include <Eigen/Core>
#include <pcl/common/transforms.h>
#include <pcl/common/common.h>
#include <pcl/common/time.h>
#include <pcl/common/angles.h>
#include <pcl/registration/transformation_estimation_svd.h>

#define CV_PI 3.1415926535897932384626433832795
struct lidtrk
{
    Eigen::MatrixXf  state;
    Eigen::MatrixXf P;
    int discount;
    int ID;
    float width;
    float length;
    float height;
};

struct lidlist
{
    int tracknum;
    std::vector<lidtrk> track;
};

struct trackld
{
    float centerx;
    float centery;
    float width;
    float length;
    float height;
};

struct tracklist0
{
    int tracknum;
    std::vector<trackld> track;
};

struct ptset
{
    struct trackld track;
    int numframe;
    int traframe;
};

struct trackobs
{
    float ID;
    float centerx;
    float speedx;
    float centery;
    float speedy;
    float width;
    float length;
    float height;
};

typedef struct
{
    int label;
    double left_x, left_y, right_x, right_y;
    double probability;
}Original;

struct point4f {
    float x;
    float y;
    float z;
    int state;
};

class LidarRoadDetect
{
public:
    LidarRoadDetect();
    ~LidarRoadDetect();
    void LidarInit(uchar _lidar_index, float lidar_height);
    void LidarCluster(std::vector<Cloud_Point>* lidar_points, std::vector<Object>* all_objects_out,const float clusterTolerance,const int  minClusterSize,const int  maxClusterSize);

    int sockPython = -1;


    void trackinit();
    void LidarTracking(std::vector<Object> all_objects);
    std::vector<lidlist> lidarlist;//
    std::vector<tracklist0> tracklist;//


    double range = 0.0;			// We only filter point with local coordinates x, y in [-range, range] inmeters
    double cell_size = 0.0;		// Hight and width of grid in bitmap
    double extend_dist = 0.0;	// The distance extended away from the ROI boundary
 //   cv::Mat binary;

    int idmax = 0;
    int noobsframe = 0;

    float Lidar_Height = 0.0;
    int iterateNum = 40;
    int sampleNum = 4;
    float land_height_scale = 150.0;//地面高度差，单位mm

    const float disthd = 5;
    const float T = 0.1;
    Eigen::MatrixXf G;
    Eigen::MatrixXf A;
    Eigen::MatrixXf C;
    Eigen::MatrixXf V_Ob;
    float g_sigma = 4;
    float lambda = 0.1;
    float qq = 0.9;
    float rr = 0.9;
    Eigen::MatrixXf Q;
    Eigen::MatrixXf R;
    float tvthd = 3;
    Eigen::MatrixXf P_predic;
    Eigen::MatrixXf S;
    Eigen::MatrixXf K;
    Eigen::MatrixXf pointdistance;
    std::vector<ptset> pointset;

    uchar lidar_index = 0;

    double temp_detect[1][9];
    /*{
        0.00162690750, -0.0177743770, 0.999840736, 5.88664865, 0.0510192923, -0.0148897609, 0.998586714, 6.07632923, -1.5
    };*/
};


#endif // LIDARROADDETECT_H
