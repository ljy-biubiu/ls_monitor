#ifndef CHAT_INTERFACE_H
#define CHAT_INTERFACE_H

#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <array>
#include "protocol.hpp"
#include "paramsevent.hpp"

template <typename W, typename R>
class ChatInterface
{

public:
    virtual void init() = 0;
    virtual void run() = 0;
    virtual bool send_data(W &msg) = 0;
    virtual void globalParamsCallback(TotalParams msg, bool save_flag) = 0;

    bool get_receive_data(R &msg);
    void initParamsEvent(std::shared_ptr<ParamsEvent<ObserverFunc>> params_event_);

protected:
    std::mutex m_lock;
    W cur_write_data;

    int my_port;
    std::string my_ip;
    bool send_write_data_flag{false};
    
    std::queue<R> recv_data_queue_;
    std::shared_ptr<ParamsEvent<ObserverFunc>> params_event;
};

#endif // COMMUNICATION_INTERFACE_H
