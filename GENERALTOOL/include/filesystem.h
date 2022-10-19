#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <QFileDialog>
#include <pcl/point_cloud.h>
#include <pcl/visualization/common/common.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <common.h>
class FileSystem
{
public:
    FileSystem();
    void LoadFile(void *win);
    int SaveDataToFile(void *win);


private:
    void ProcessLine(void *win,QString &line);

    QString openFile;
};

#endif // FILESYSTEM_H
