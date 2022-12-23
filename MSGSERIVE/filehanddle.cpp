#include "filehanddle.h"
#include "qdebug.h"
#include <stdio.h>
#include <unistd.h>

FileHanddle::FileHanddle()
{
    char buf[128] = {0};
    getcwd(buf, sizeof(buf));
    read_file_path = std::string(buf) + "/my_paramss.json";
}

void FileHanddle::init(TotalParams &total_params)
{
    // read_file_path = "/home/ljy/my_paramss.json";
    readDataLocal(total_params);
}

int FileHanddle::writeDataLocal(TotalParams &total_params)
{

    // 根节点
    Json::Value root;
    // 子节点
    Json::Value ComunicationData;
    // 子节点属性
    //  ComunicationData["lidar_x"] = Json::Value(total_params.protocol_data.read_data.angle);
    //  ComunicationData["lidar_y"] = Json::Value(total_params.protocol_data.read_data.amplitude_position);
    //  ComunicationData["lidar_z"] = Json::Value(total_params.protocol_data.read_data.height);
    //  ComunicationData["safe_distance"] = Json::Value(total_params.protocol_data.read_data.safe_distance);
    //  ComunicationData["resolution"] = Json::Value(total_params.protocol_data.read_data.resolution);
    //  ComunicationData["build_map_signal"] = Json::Value(total_params.protocol_data.read_data.build_map_signal);
    //  ComunicationData["comnunication_flag"] = Json::Value(total_params.protocol_data.read_data.comnunication_flag);
    //  ComunicationData["device_status"] = Json::Value(total_params.protocol_data.read_data.device_status);
    //  ComunicationData["material_area_x"] = Json::Value(total_params.protocol_data.read_data.material_area_x);
    //  ComunicationData["material_area_y"] = Json::Value(total_params.protocol_data.read_data.material_area_y);
    //  ComunicationData["meterial_area_length"] = Json::Value(total_params.protocol_data.read_data.meterial_area_length);
    //  ComunicationData["meterial_area_width"] = Json::Value(total_params.protocol_data.read_data.meterial_area_width);
    //  ComunicationData["technology"] = Json::Value(total_params.protocol_data.read_data.technology);
    // 子节点挂到根节点上
    root["ComunicationData"] = Json::Value(ComunicationData);

    // 子节点
    Json::Value LidarPreset;
    // 子节点属性
    LidarPreset["paintarea_Radius"] = Json::Value(total_params.baseParams.lidarPreset.paintarea_Radius);
    LidarPreset["XAngle"] = Json::Value(total_params.baseParams.lidarPreset.XAngle);
    LidarPreset["YAngle"] = Json::Value(total_params.baseParams.lidarPreset.YAngle);
    LidarPreset["ZAngle"] = Json::Value(total_params.baseParams.lidarPreset.ZAngle);
    LidarPreset["Base_X"] = Json::Value(total_params.baseParams.lidarPreset.Base_X);
    LidarPreset["Base_Y"] = Json::Value(total_params.baseParams.lidarPreset.Base_Y);
    LidarPreset["Base_Z"] = Json::Value(total_params.baseParams.lidarPreset.Base_Z);
    // 子节点挂到根节点上
    root["LidarPreset"] = Json::Value(LidarPreset);

    // 子节点
    Json::Value LidarCluster;
    // 子节点属性
    LidarCluster["ClusterTolerance"] = Json::Value(total_params.baseParams.lidarCluster.ClusterTolerance);
    LidarCluster["MinClusterSize"] = Json::Value(total_params.baseParams.lidarCluster.MinClusterSize);
    LidarCluster["MaxClusterSize"] = Json::Value(total_params.baseParams.lidarCluster.MaxClusterSize);
    LidarCluster["Resolution"] = Json::Value(total_params.baseParams.lidarCluster.Resolution);
    LidarCluster["Difference_threshold"] = Json::Value(total_params.baseParams.lidarCluster.Difference_threshold);
    LidarCluster["Kvalue"] = Json::Value(total_params.baseParams.lidarCluster.Kvalue);
    LidarCluster["EuclideanDistance"] = Json::Value(total_params.baseParams.lidarCluster.EuclideanDistance);
    // 子节点挂到根节点上
    root["LidarCluster"] = Json::Value(LidarCluster);

    // 子节点
    Json::Value LidarBase;
    // 子节点属性
    LidarBase["lidarPort"] = Json::Value(total_params.baseParams.lidarBase.lidarPort);
    LidarBase["LidarAddress"] = Json::Value(total_params.baseParams.lidarBase.LidarAddress);
    LidarBase["ServerPort"] = Json::Value(total_params.baseParams.lidarBase.ServerPort);
    LidarBase["ServerAddress"] = Json::Value(total_params.baseParams.lidarBase.ServerAddress);
    LidarBase["DataAddress"] = Json::Value(total_params.baseParams.lidarBase.DataAddress);
    LidarBase["DeviceId"] = Json::Value(total_params.baseParams.lidarBase.DeviceId);
    LidarBase["LidarModel"] = Json::Value(total_params.baseParams.lidarBase.LidarModel);
    // 子节点挂到根节点上
    root["LidarBase"] = Json::Value(LidarBase);

    // 子节点
    Json::Value LidarCameraBase;
    // 子节点属性
    LidarCameraBase["Pos_X"] = Json::Value(total_params.baseParams.lidarCameraBase.Pos_X);
    LidarCameraBase["Pos_Y"] = Json::Value(total_params.baseParams.lidarCameraBase.Pos_Y);
    LidarCameraBase["Pos_Z"] = Json::Value(total_params.baseParams.lidarCameraBase.Pos_Z);
    LidarCameraBase["View_X"] = Json::Value(total_params.baseParams.lidarCameraBase.View_X);
    LidarCameraBase["View_Y"] = Json::Value(total_params.baseParams.lidarCameraBase.View_Y);
    LidarCameraBase["View_Z"] = Json::Value(total_params.baseParams.lidarCameraBase.View_Z);
    LidarCameraBase["Up_X"] = Json::Value(total_params.baseParams.lidarCameraBase.Up_X);
    LidarCameraBase["Up_Y"] = Json::Value(total_params.baseParams.lidarCameraBase.Up_Y);
    LidarCameraBase["Up_Z"] = Json::Value(total_params.baseParams.lidarCameraBase.Up_Z);
    // 子节点挂到根节点上
    root["LidarCameraBase"] = Json::Value(LidarCameraBase);

    // 子节点
    Json::Value CameraBase;
    // 子节点属性
    CameraBase["ip"] = Json::Value(total_params.baseParams.cameraBase.ip);
    CameraBase["code"] = Json::Value(total_params.baseParams.cameraBase.code);
    CameraBase["name"] = Json::Value(total_params.baseParams.cameraBase.name);
    // 子节点挂到根节点上
    root["CameraBase"] = Json::Value(CameraBase);

    // 子节点
    Json::Value LowerMachineBase;
    // 子节点属性
    LowerMachineBase["ip"] = Json::Value(total_params.baseParams.lowerMachineBase.ip);
    LowerMachineBase["port"] = Json::Value(total_params.baseParams.lowerMachineBase.port);
    // 子节点挂到根节点上
    root["LowerMachineBase"] = Json::Value(LowerMachineBase);

    // 子节点
    Json::Value GroundParamIn;
    // 子节点属性
    GroundParamIn["gridNumX"] = Json::Value(total_params.baseParams.groundParamIn.gridNumX);
    GroundParamIn["gridNumY"] = Json::Value(total_params.baseParams.groundParamIn.gridNumY);
    GroundParamIn["max_monitor_angle"] = Json::Value(total_params.baseParams.groundParamIn.max_monitor_angle);
    GroundParamIn["min_monitor_angle"] = Json::Value(total_params.baseParams.groundParamIn.min_monitor_angle);
    // 子节点挂到根节点上
    root["GroundParamIn"] = Json::Value(GroundParamIn);

    // 子节点
    Json::Value ShipParamIn;
    // 子节点属性
    ShipParamIn["gridNumX"] = Json::Value(total_params.baseParams.shipParamIn.gridNumX);
    ShipParamIn["gridNumY"] = Json::Value(total_params.baseParams.shipParamIn.gridNumY);
    ShipParamIn["max_monitor_angle"] = Json::Value(total_params.baseParams.shipParamIn.max_monitor_angle);
    ShipParamIn["min_monitor_angle"] = Json::Value(total_params.baseParams.shipParamIn.min_monitor_angle);
    ShipParamIn["boundRadius"] = Json::Value(total_params.baseParams.shipParamIn.boundRadius);
    ShipParamIn["normalRadius"] = Json::Value(total_params.baseParams.shipParamIn.normalRadius);
    // 子节点挂到根节点上
    root["ShipParamIn"] = Json::Value(ShipParamIn);

    std::vector<cv::Point2d> ground;
    std::vector<cv::Point2d> rectangle_ground;
    std::vector<cv::Point2d> ship;

    // 子节点
    Json::Value RoiArea;
    Json::Value RoiArea_ground;
    Json::Value RoiArea_rectangle_ground;
    Json::Value RoiArea_ship;
    Json::Value Coordination;

    for (std::vector<cv::Point2d>::iterator point = total_params.baseParams.roiArea.ground.begin();
         point < total_params.baseParams.roiArea.ground.end(); point++)
    {
        Coordination["x"] = point->x;
        Coordination["y"] = point->y;
        RoiArea_ground.append(Coordination);
    }

    for (std::vector<cv::Point2d>::iterator point = total_params.baseParams.roiArea.rectangle_ground.begin();
         point < total_params.baseParams.roiArea.rectangle_ground.end(); point++)
    {
        Coordination["x"] = point->x;
        Coordination["y"] = point->y;
        RoiArea_rectangle_ground.append(Coordination);
    }

    for (std::vector<cv::Point2d>::iterator point = total_params.baseParams.roiArea.ship.begin();
         point < total_params.baseParams.roiArea.ship.end(); point++)
    {
        Coordination["x"] = point->x;
        Coordination["y"] = point->y;
        RoiArea_ship.append(Coordination);
    }

    // 子节点挂到根节点上RoiArea
    RoiArea["RoiArea_ground"] = Json::Value(RoiArea_ground);
    RoiArea["RoiArea_rectangle_ground"] = Json::Value(RoiArea_rectangle_ground);
    RoiArea["RoiArea_ship"] = Json::Value(RoiArea_ship);
    root["RoiArea"] = Json::Value(RoiArea);

    std::ofstream ofs;
    ofs.open(read_file_path);
    if (!ofs.is_open())
    {
        qCritical() << "写入json文件失败";
        return false;
    }
    ofs << root.toStyledString();
    ofs.close();
    return true;
}

void FileHanddle::readDataLocal(TotalParams &total_params)
{
    Json::Reader reader;
    Json::Value json_value;
    std::ifstream ifs(read_file_path, std::ios::binary);

    if (!ifs.is_open())
    {
        qCritical() << "读取参数文件失败，创建参数文件";
        writeDataLocal(total_params);
        ifs.open(read_file_path);
    }

    if (reader.parse(ifs, json_value))
    {
        // PLC协议设置内容
        //  total_params.protocol_data.read_data.angle= json_value["ComunicationData"]["angle"].asFloat();
        //  total_params.protocol_data.read_data.amplitude_position= json_value["ComunicationData"]["amplitude_position"].asFloat();
        //  total_params.protocol_data.read_data.height= json_value["ComunicationData"]["height"].asFloat();
        //  total_params.protocol_data.read_data.safe_distance= json_value["ComunicationData"]["safe_distance"].asFloat();
        //  total_params.protocol_data.read_data.resolution= json_value["ComunicationData"]["resolution"].asFloat();
        //  total_params.protocol_data.read_data.build_map_signal= json_value["ComunicationData"]["build_map_signal"].asFloat();
        //  total_params.protocol_data.read_data.comnunication_flag= json_value["ComunicationData"]["comnunication_flag"].asFloat();
        //  total_params.protocol_data.read_data.device_status= json_value["ComunicationData"]["device_status"].asFloat();
        //  total_params.protocol_data.read_data.material_area_x= json_value["ComunicationData"]["material_area_x"].asFloat();
        //  total_params.protocol_data.read_data.material_area_y= json_value["ComunicationData"]["material_area_y"].asFloat();
        //  total_params.protocol_data.read_data.meterial_area_length= json_value["ComunicationData"]["meterial_area_length"].asFloat();
        //  total_params.protocol_data.read_data.meterial_area_width= json_value["ComunicationData"]["meterial_area_width"].asFloat();
        //  total_params.protocol_data.read_data.technology= json_value["ComunicationData"]["technology"].asFloat();

        //
        total_params.baseParams.lidarPreset.paintarea_Radius = json_value["LidarPreset"]["paintarea_Radius"].asDouble();
        total_params.baseParams.lidarPreset.XAngle = json_value["LidarPreset"]["XAngle"].asDouble();
        total_params.baseParams.lidarPreset.YAngle = json_value["LidarPreset"]["YAngle"].asDouble();
        total_params.baseParams.lidarPreset.ZAngle = json_value["LidarPreset"]["ZAngle"].asDouble();
        total_params.baseParams.lidarPreset.Base_X = json_value["LidarPreset"]["Base_X"].asDouble();
        total_params.baseParams.lidarPreset.Base_Y = json_value["LidarPreset"]["Base_Y"].asDouble();
        total_params.baseParams.lidarPreset.Base_Z = json_value["LidarPreset"]["Base_Z"].asDouble();

        //
        total_params.baseParams.lidarCluster.ClusterTolerance = json_value["LidarCluster"]["ClusterTolerance"].asDouble();
        total_params.baseParams.lidarCluster.MinClusterSize = json_value["LidarCluster"]["MinClusterSize"].asDouble();
        total_params.baseParams.lidarCluster.MaxClusterSize = json_value["LidarCluster"]["MaxClusterSize"].asDouble();
        total_params.baseParams.lidarCluster.Resolution = json_value["LidarCluster"]["Resolution"].asDouble();
        total_params.baseParams.lidarCluster.Difference_threshold = json_value["LidarCluster"]["Difference_threshold"].asDouble();
        total_params.baseParams.lidarCluster.Kvalue = json_value["LidarCluster"]["Kvalue"].asDouble();
        total_params.baseParams.lidarCluster.EuclideanDistance = json_value["LidarCluster"]["EuclideanDistance"].asDouble();

        //
        total_params.baseParams.lidarBase.lidarPort = json_value["LidarBase"]["lidarPort"].asDouble();
        total_params.baseParams.lidarBase.LidarAddress = json_value["LidarBase"]["LidarAddress"].asString();
        total_params.baseParams.lidarBase.ServerPort = json_value["LidarBase"]["ServerPort"].asDouble();
        total_params.baseParams.lidarBase.ServerAddress = json_value["LidarBase"]["ServerAddress"].asString();
        total_params.baseParams.lidarBase.DataAddress = json_value["LidarBase"]["DataAddress"].asString();
        total_params.baseParams.lidarBase.DeviceId = json_value["LidarBase"]["DeviceId"].asInt();
        total_params.baseParams.lidarBase.LidarModel = json_value["LidarBase"]["LidarModel"].asInt();

        //
        total_params.baseParams.lidarCameraBase.Pos_X = json_value["LidarCameraBase"]["Pos_X"].asDouble();
        total_params.baseParams.lidarCameraBase.Pos_Y = json_value["LidarCameraBase"]["Pos_Y"].asDouble();
        total_params.baseParams.lidarCameraBase.Pos_Z = json_value["LidarCameraBase"]["Pos_Z"].asDouble();
        total_params.baseParams.lidarCameraBase.View_X = json_value["LidarCameraBase"]["View_X"].asDouble();
        total_params.baseParams.lidarCameraBase.View_Y = json_value["LidarCameraBase"]["View_Y"].asDouble();
        total_params.baseParams.lidarCameraBase.View_Z = json_value["LidarCameraBase"]["View_Z"].asDouble();
        total_params.baseParams.lidarCameraBase.Up_X = json_value["LidarCameraBase"]["Up_X"].asDouble();
        total_params.baseParams.lidarCameraBase.Up_Y = json_value["LidarCameraBase"]["Up_Y"].asDouble();
        total_params.baseParams.lidarCameraBase.Up_Z = json_value["LidarCameraBase"]["Up_Z"].asDouble();

        //
        total_params.baseParams.cameraBase.ip = json_value["CameraBase"]["ip"].asString();
        total_params.baseParams.cameraBase.code = json_value["CameraBase"]["code"].asString();
        total_params.baseParams.cameraBase.name = json_value["CameraBase"]["name"].asString();

        //
        total_params.baseParams.lowerMachineBase.ip = json_value["LowerMachineBase"]["ip"].asString();
        total_params.baseParams.lowerMachineBase.port = json_value["LowerMachineBase"]["port"].asInt();

        //
        total_params.baseParams.groundParamIn.gridNumX = json_value["GroundParamIn"]["gridNumX"].asDouble();
        total_params.baseParams.groundParamIn.gridNumY = json_value["GroundParamIn"]["gridNumY"].asDouble();
        total_params.baseParams.groundParamIn.max_monitor_angle = json_value["GroundParamIn"]["max_monitor_angle"].asDouble();
        total_params.baseParams.groundParamIn.min_monitor_angle = json_value["GroundParamIn"]["min_monitor_angle"].asDouble();

        //
        total_params.baseParams.shipParamIn.gridNumX = json_value["ShipParamIn"]["gridNumX"].asDouble();
        total_params.baseParams.shipParamIn.gridNumY = json_value["ShipParamIn"]["gridNumY"].asDouble();
        total_params.baseParams.shipParamIn.max_monitor_angle = json_value["ShipParamIn"]["max_monitor_angle"].asDouble();
        total_params.baseParams.shipParamIn.min_monitor_angle = json_value["ShipParamIn"]["min_monitor_angle"].asDouble();
        total_params.baseParams.shipParamIn.boundRadius = json_value["ShipParamIn"]["boundRadius"].asDouble();
        total_params.baseParams.shipParamIn.normalRadius = json_value["ShipParamIn"]["normalRadius"].asDouble();
        //

        int array_cnt = json_value["RoiArea"]["RoiArea_rectangle_ground"].size();
        for (int i = 0; array_cnt > i; i++)
        {
            cv::Point2d point2D(json_value["RoiArea"]["RoiArea_rectangle_ground"][i]["x"].asDouble(),
                                json_value["RoiArea"]["RoiArea_rectangle_ground"][i]["y"].asDouble());
            total_params.baseParams.roiArea.ground.push_back(point2D);
        }

        array_cnt = json_value["RoiArea"]["RoiArea_ground"].size();
        for (int i = 0; array_cnt > i; i++)
        {
            cv::Point2d point2D(json_value["RoiArea"]["RoiArea_ground"][i]["x"].asDouble(),
                                json_value["RoiArea"]["RoiArea_ground"][i]["y"].asDouble());
            total_params.baseParams.roiArea.rectangle_ground.push_back(point2D);
        }

        array_cnt = json_value["RoiArea"]["RoiArea_ship"].size();
        for (int i = 0; array_cnt > i; i++)
        {
            cv::Point2d point2D(json_value["RoiArea"]["RoiArea_ship"][i]["x"].asDouble(),
                                json_value["RoiArea"]["RoiArea_ship"][i]["y"].asDouble());
            total_params.baseParams.roiArea.ship.push_back(point2D);
        }

        // for (std::vector<cv::Point2d>::iterator point = total_params.roiArea.ship.begin();
        //      point < total_params.roiArea.ship.end(); point++)
        // {
        //     std::cout << point->x << std::endl;
        //     std::cout << point->y << std::endl;
        // }

    }
    else
    {
        qCritical() << "Can not parse Json file!";
    }

    ifs.close();
    // total_params.printData();
}
