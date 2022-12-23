#include "communication_interface.h"

bool ComunicateInterface::get_receive_data(ReadData &msg)
{
    std::lock_guard<std::mutex> LockGuard(this->m_lock);
    if (recv_data_queue_.size() > 0)
    {
        msg = std::move(this->recv_data_queue_.front());
        this->recv_data_queue_.pop();
        return true;
    }
    else
    {
        return false;
    }
}


void ComunicateInterface::initParamsEvent(std::shared_ptr<ParamsEvent<ObserverFunc>> params_event_)
{
    params_event = params_event_;

    
    // std::lock_guard<std::mutex> LockGuard(params_event->getMylock());
    // params_event->getTotalParams().lidarBase.DataAddress = "dasdasd";
    // params_event->Notify(params_event->getTotalParams(), false);
}

// bool compare_write_data(char *buf1, char *buf2)
// {
//     for (int i = 0; i <sizeof(buf1); i++)
//     {
//         if (buf1[i] != buf2[i])
//         {
//             return true;
//         }
//     }
//     return false;
// }

// void ComunicateInterface::globalParamsCallback(TotalParams msg, bool save_flag)
// {
//     this->my_port = msg.lowerMachineBase.port;
//     this->my_ip = msg.lowerMachineBase.ip;

//     if (compare_write_data((char *)(&this->cur_write_data), (char *)(&msg.protocol_data.write_data)))
//     {
//         this->cur_write_data = msg.protocol_data.write_data;
//         send_write_data_flag = true;
//     }
// }