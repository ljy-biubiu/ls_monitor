#include "chat_interface.h"

// template <typename W, typename R>
// bool ChatInterface<typename W, typename R>::get_receive_data(R &msg)
// {
//     if (recv_data_queue_.size() > 0)
//     {
//         std::lock_guard<std::mutex> LockGuard(this->m_lock);
//         msg = std::move(this->recv_data_queue_.front());
//         this->recv_data_queue_.pop();
//         return true;
//     }
//     else
//     {
//         return false;
//     }
// }


// template <typename W, typename R>
// void ChatInterface<typename W, typename R>::initParamsEvent(std::shared_ptr<ParamsEvent<ObserverFunc>> params_event_)
// {
//     params_event = params_event_;
//     // std::lock_guard<std::mutex> LockGuard(params_event->getMylock());
//     // params_event->getTotalParams().lidarBase.DataAddress = "dasdasd";
//     // params_event->Notify(params_event->getTotalParams(), false);
// }
