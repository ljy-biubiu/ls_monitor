#ifndef COMMOM_STRUCT_H
#define COMMOM_STRUCT_H

#include <sys/types.h>
#include <QVariant>
#include <QMetaType>

#define LIDAR_NUM 1
#define PI 3.1415926
#define LIDAR_INDEX0 2368

typedef unsigned long long int	uint_8B;
typedef unsigned  int uint;

enum LINES
{
    LINE16 = 0, LINE32
};

enum MACHINE
{
    SERVER = 0, CLIENT
};

enum DETECTMODE
{
    CLUSTERRING = 0, DEEPLEARNING
};

enum DISPLAYMODE
{
    ORIGINAL = 0, BOUNDING, NODISPLAY
};



typedef struct
{
    int ID;//0-4000,normal;4001-5000,missed objects
    char label[20];
    bool min_rect_modify;//false=no course angle calculated
    double x, y, z;
    float xmin,xmax,ymin,ymax,zmin,zmax;
    float length, width, height;

    double probability;
    float x1, x2, x3, x4, y1, y2, y3, y4;
    float speed_x;//km/s
    float speed_y;//km/s
    int lidar_num;//雷达编号，1-63
}Object;




struct Clustem_Obj
{
    std::vector<Object>* Obj;

};
Q_DECLARE_METATYPE(Clustem_Obj)


typedef struct
{
    uint id;    //starts with 0
    int label;  //0=normal, 1=non-motor, 2=small car, 3=big car, 4=pedestrian, 5=other,result by cluster
    float x, y, z;
    float r, g, b;
    int intensity;
    int area;
}Cloud_Point;




#endif // COMMOM_STRUCT_H
