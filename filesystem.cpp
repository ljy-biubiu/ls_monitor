#include "filesystem.h"
#include "mainwindow.h"
#include <QTextStream>
#include <QDebug>
FileSystem::FileSystem()
{
    openFile = QString("");
}


void FileSystem::LoadFile(void *win)//打开文件
{
    openFile = "Area.ini";

    if (!openFile.isEmpty())
    {
        qDebug()<<"open Area.ini success";
        QFile file(openFile);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return;
        }
        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull())
        {
            ProcessLine(win, line);
            line = in.readLine();
        }
    }
    else
    {
        qDebug()<<"open Area.ini failed";
    }
}


void FileSystem::ProcessLine(void *win, QString &line)
{
    static int curArea =0;
    QString s = line.trimmed();
    int len = s.size();
    MainWindow *mWindow = (MainWindow*)win;

    if (len == 0)
    {
        return;
    }

    QStringList sl = s.split(" ", QString::SkipEmptyParts);



    if(s.mid(0,10) == "[lidar_ID]")
    {
        mWindow->temlidar.lidar_Index = sl.at(1).toInt();
    }
    //    if(s.mid(0,10) == "[lidar_IP]")
    //    {
    //        mWindow->temlidar.lidar_Ip = sl.at(1).toInt();
    //    }
    if(s.mid(0,12) == "[lidar_PORT]")
    {
        mWindow->temlidar.lidar_port = sl.at(1).toInt();
    }
    if(s.mid(0,14) == "[lidar_RADIUS]")
    {
        mWindow->temlidar.lidar_Radius = sl.at(1).toFloat();
    }

    if(s.mid(0,12) == "[lidar_BASE]")
    {
        mWindow->temlidar.lidar_base.x = sl.at(1).toFloat();
        mWindow->temlidar.lidar_base.y = sl.at(2).toFloat();
        mWindow->temlidar.lidar_base.z = sl.at(3).toFloat();
    }
    if(s.mid(0,14) == "[lidar_ANGHOR]")
    {
        mWindow->temlidar.angle_hor = sl.at(1).toFloat();
    }
    if(s.mid(0,14) == "[lidar_ANGVER]")
    {
        mWindow->temlidar.angle_ver = sl.at(1).toFloat();
    }
    //摄像头配置参数
//    if(s.mid(0,11) == "[camera_ip]")
//    {
//        mWindow->m_ptz->camera_ip = sl.at(1);
//    }
//    if(s.mid(0,15) == "[camera_userid]")
//    {
//        mWindow->m_ptz->camera_userid = sl.at(1);
//    }
//    if(s.mid(0,13) =="[camera_pass]")
//    {
//        mWindow->m_ptz->camera_pass = sl.at(1);
//    }
    //
    if(s.mid(0,12) == "[area_INDEX]")
    {
        curArea = sl.at(1).toInt();
    }

    if(s.mid(0,18) == "[area_height_down]")
    {
        mWindow->setROI->area[curArea].Area_height_down = sl.at(1).toFloat();
        qDebug()<<"down :"<<mWindow->setROI->area[curArea].Area_height_down;
    }

    if(s.mid(0,17) == "[area_height_top]")
    {
        mWindow->setROI->area[curArea].Area_height_top = sl.at(1).toFloat();
    }
    if (s.mid(0, 15) == "[Polygon_point]")
    {
        mWindow->setROI->area[curArea].Area2D_point_T.clear();
        for(int i=1;i<sl.size();i+=2)
        {

            pcl::PointXYZRGB point;
            point.x =sl.at(i).toFloat();
            point.y =sl.at(i+1).toFloat();



            mWindow->setROI->area[curArea].Area2D_point_T.push_back(point);
        }
        //     qDebug()<<"mWindow->setROI->area[curArea].Area2D_point_T="<<mWindow->setROI->area[curArea].Area2D_point_T.size()<<" curarea=";

    }

}

int FileSystem::SaveDataToFile(void *win)
{
    MainWindow *mWindow = (MainWindow *)win;
    openFile = "Area.ini";

    QFile file(openFile);
    QTextStream out(&file);

    if (!file.exists())
    {
        file.open(QIODevice::WriteOnly);
        file.close();
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return -1;
    }
    out << QString("[lidar_ID] %1\n").arg(mWindow->temlidar.lidar_Index);
    out << QString("[lidar_IP] %1\n").arg(mWindow->temlidar.lidar_Ip);
    out << QString("[lidar_PORT] %1\n").arg(mWindow->temlidar.lidar_port);
    out << QString("[lidar_RADIUS] %1\n").arg(mWindow->temlidar.lidar_Radius);
    out << QString("[lidar_BASE] %1 %2 %3\n").arg(mWindow->temlidar.lidar_base.x).arg(mWindow->temlidar.lidar_base.y).arg(mWindow->temlidar.lidar_base.z);
    out << QString("[lidar_ANGHOR] %1\n").arg(mWindow->temlidar.angle_hor);
    out << QString("[lidar_ANGVER] %1\n").arg(mWindow->temlidar.angle_ver);
    for(int index =0;index<AREAS;index++)
    {
        out << QString("[area_INDEX] %1\n").arg(index);
        out << QString("[area_height_down] %1\n").arg(mWindow->setROI->area[index].Area_height_down);
        out << QString("[area_height_top] %1\n").arg(mWindow->setROI->area[index].Area_height_top);
        out << QString("[Polygon_point] ");
        for(int j=0;j<mWindow->setROI->area[index].Area2D_point_T.size();j++)
        {

            out << QString("%1 %2 ").arg(mWindow->setROI->area[index].Area2D_point_T[j].x).arg(mWindow->setROI->area[index].Area2D_point_T[j].y);

        }
        out << QString("\n");
    }

    file.close();

    return 0;
}
