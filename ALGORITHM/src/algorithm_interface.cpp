#include "algorithm_interface.h"

bool AlgorithmInterface::get_lidar_data(ProcessParamsOut &msg)
{
    std::lock_guard<std::mutex> LockGuard(this->m_lock);
    if (recv_lidar_queue_.size() > 0)
    {
        msg = std::move(this->recv_lidar_queue_.front());
        this->recv_lidar_queue_.pop();
        return true;
    }
    else
    {
        return false;
    }
}

void AlgorithmInterface::globalParamsCallback(TotalParams msg, bool save_flag)
{
    //   msg.protocol_data.read_data.lidar_x;
    process_params_in.protocolData=msg.protocol_data;
    process_params_in.shipParamIn.gridNumX = msg.baseParams.shipParamIn.gridNumX;
    process_params_in.shipParamIn.gridNumY = msg.baseParams.shipParamIn.gridNumY;
    process_params_in.shipParamIn.boundRadius = msg.baseParams.shipParamIn.boundRadius;
    process_params_in.shipParamIn.normalRadius = msg.baseParams.shipParamIn.normalRadius;
    process_params_in.shipParamIn.max_monitor_angle = msg.baseParams.shipParamIn.max_monitor_angle;
    process_params_in.shipParamIn.min_monitor_angle = msg.baseParams.shipParamIn.min_monitor_angle;

    process_params_in.groundParamIn.gridNumX = msg.baseParams.groundParamIn.gridNumX;
    process_params_in.groundParamIn.gridNumY = msg.baseParams.groundParamIn.gridNumY;
    process_params_in.groundParamIn.max_monitor_angle = msg.baseParams.groundParamIn.max_monitor_angle;
    process_params_in.groundParamIn.min_monitor_angle = msg.baseParams.groundParamIn.min_monitor_angle;

    // std::cout << "quaternion_w:" << msg.protocol_data.read_data.quaternion_w << " , ";
    // std::cout << "quaternion_x:" << msg.protocol_data.read_data.quaternion_x << " , ";
    // std::cout << "quaternion_y:" << msg.protocol_data.read_data.quaternion_y << " , ";
    // std::cout << "quaternion_z:" << msg.protocol_data.read_data.quaternion_z << " , ";

    // std::cout << "x_roll:" << msg.protocol_data.read_data.x_roll << " , ";
    // std::cout << "y_pitch:" << msg.protocol_data.read_data.y_pitch << " , ";
    // std::cout << "z_yaw:" << msg.protocol_data.read_data.z_yaw << std::endl;

    //    std::cout<<process_params_in.shipParamIn.gridNumX<<std::endl;
    //    std::cout<<process_params_in.shipParamIn.gridNumY<<std::endl;
    //    std::cout<<process_params_in.shipParamIn.boundRadius<<std::endl;
    //    std::cout<<process_params_in.shipParamIn.normalRadius<<std::endl;
    //    std::cout<<process_params_in.shipParamIn.max_monitor_angle<<std::endl;
    //    std::cout<<process_params_in.shipParamIn.min_monitor_angle<<std::endl;

    //    std::cout<<process_params_in.groundParamIn.gridNumX<<std::endl;
    //    std::cout<<process_params_in.groundParamIn.gridNumY<<std::endl;
    //    std::cout<<process_params_in.groundParamIn.max_monitor_angle<<std::endl;
    //    std::cout<<process_params_in.groundParamIn.min_monitor_angle<<std::endl;
}

void AlgorithmInterface::initLidarDrive(const std::shared_ptr<LidarDriveInterface> msg)
{
    this->lidarDriveInterface = msg;
}
