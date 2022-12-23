#include "chat_plc.h"
#include <functional>
#include "qdebug.h"
// #include <afxsock.h>

void ChatPlc::init()
{

    this->init_thread();
}

void ChatPlc::init_thread()
{
    std::thread dowork_thread(std::bind(&ChatPlc::run, this));
    dowork_thread.detach();
}

bool ChatPlc::tcp_init()
{
    qDebug() << "尝试连接下位机";

    // 1、创建socket套接字
    this->my_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->my_sockfd < 0)
    {
        perror("socket error");
        qCritical() << "创建socket失败";
        return false;
    }

    // qDebug() << "创建连接下位机的socket成功";

    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(atoi(std::to_string(this->my_port).c_str()));
    myaddr.sin_addr.s_addr = inet_addr(this->my_ip.c_str());
    // 2、连接
    socklen_t len = sizeof(struct sockaddr_in);
    if (connect(this->my_sockfd, (struct sockaddr *)&myaddr, len) < 0)
    {
        //        perror("connect error");
        qCritical() << "连接下位机失败";
        std::lock_guard<std::mutex> LockGuard(params_event->getMylock());
        params_event->getTotalParams().alarm_status.communicate_status.bits.plc = 0;
        params_event->Notify(params_event->getTotalParams(), false);
        return false;
    }
    qDebug() << "连接下位机成功";
    return true;
}

void ChatPlc::UnInitialize()
{
    close(this->my_sockfd);
}

bool compare_write_data(char *buf1, char *buf2)
{
    for (int i = 0; i < sizeof(buf1); i++)
    {
        if (buf1[i] != buf2[i])
        {
            return true;
        }
    }
    return false;
}

void ChatPlc::globalParamsCallback(TotalParams msg, bool save_flag)
{
    this->my_port = msg.baseParams.lowerMachineBase.port;
    this->my_ip = msg.baseParams.lowerMachineBase.ip;

    if (compare_write_data((char *)(&this->cur_write_data), (char *)(&msg.protocol_data.write_data)))
    {
        this->cur_write_data = msg.protocol_data.write_data;
        send_write_data_flag = true;
    }
}

void reverseByte(char *buf, const int input_num_start,
                 const int &input_num_end, const int &cnt)
{
    int num = (input_num_end - input_num_start) / cnt;

    for (int i{0}; i < num; i++)
    {
        char cur_data_1 = buf[input_num_start + i * 4];
        char cur_data_2 = buf[input_num_start + 1 + i * 4];

        buf[input_num_start + i * 4] = buf[input_num_start + 3 + i * 4];
        buf[input_num_start + 1 + i * 4] = buf[input_num_start + 2 + i * 4];
        buf[input_num_start + 2 + i * 4] = cur_data_2;
        buf[input_num_start + 3 + i * 4] = cur_data_1;
    }
}

// 0.23
// 503

void ChatPlc::sendWriteDataEvent()
{
    if (send_write_data_flag == true)
    {
        send_data(cur_write_data);
        send_write_data_flag = false;
    }
}

// 用std::function+lamda 代替 抽象出协议层
void ChatPlc::run()
{

    if (!this->tcp_init())
    {
        return;
    };

    std::thread dowork_askreaddata_thread(std::bind(&ChatPlc::ask_read_data, this));
    dowork_askreaddata_thread.detach();

    // sendData(buff);
    while (1)
    {
        usleep(500);

        sendWriteDataEvent();

        memset(buff, 0x00, RECEIVE_BUFFER_SIZE);
        int ret = recv(this->my_sockfd, buff, sizeof(buff), 0);

        if (buff[7] == 3)
        {
            rece_read_data_flag = false;
            anlysisReceiveData();
        }
        else if (buff[7] == 16)
        {
            qDebug() << " receive   wirte data  ack";
        }

        if (ret < 0)
        {
            // perror("recv error");
            qCritical() << "recv   pcl error, ret = " << ret;
            break;
            ;
        }
    }
}

// bool send_data(ComunicationData &msg);

bool ChatPlc::ask_read_data()
{

    while (true)
    {
        if (rece_read_data_flag == false)
        {
            rece_read_data_flag = true;
            ask_plc_read.data2++;

            if (ask_plc_read.data2 == 0)
            {
                ask_plc_read.data1++;
            }

            int cnt{0};
            char *pc = nullptr;
            char send_buf[ASK_READ_DATA_BUFFER_SIZE] = {0};

            pc = (char *)(&ask_plc_read);

            for (int i{0}; i < (int)sizeof(AskPlcReadHead); i++, cnt++)
            {
                send_buf[cnt] = *(pc + i);
            }

            if (send(this->my_sockfd, send_buf, 12, 0) == -1)
            {
                qCritical() << "send to pcl data fail";
            }
        }
        usleep(1000);
    }
    return true;
}

bool ChatPlc::send_data(WriteData &msg)
{
    char *pc, *pc2 = nullptr;
    char send_buf[ASK_WRITE_DATA_BUFFER_SIZE] = {0};

    write_head.data2++;
    if (write_head.data2 == 0)
    {
        write_head.data1++;
    }

    pc = (char *)(&msg);
    pc2 = (char *)(&write_head);
    // write_head

    for (int i{0}, cnt{0}; i < (int)sizeof(write_head); i++, cnt++)
    {
        send_buf[cnt] = *(pc2 + i);
    }

    // 600字节需要分3次写入  分别写入3个地址
    int add_num[6] = {0x00, 0x52, 0x00, 0xb6, 0x01, 0x1a};

    for (size_t count = 0; count < 3; count++)
    {

        send_buf[8] = add_num[2 * count];
        send_buf[9] = add_num[2 * count + 1];

        for (int i{0}, cnt{0}; i < 200; i++, cnt++)
        {
            send_buf[(int)sizeof(write_head) + cnt] = *(pc + i + count * 200);
        }

        int in_ = 200 + (int)sizeof(write_head);
        reverseByte(send_buf, (int)sizeof(write_head), in_, 4);

        if (send(this->my_sockfd, send_buf, in_, 0) == -1)
        {
            return false;
        }
        std::cout << "count:" << count << std::endl;
        usleep(100);
    }
}

void ChatPlc::anlysisReceiveData()
{
    int cnt{0};
    char *pc = nullptr;
    ReadData msg;
    memset(&msg, 0, sizeof(msg));

    if (ret_head.data6 != 96 || ret_head.data7 != 1 ||
        ret_head.data8 != 3 || ret_head.data9 != 4 ||
        ask_plc_read.data1 != buff[0] || ask_plc_read.data2 != buff[1])
    {
        qCritical() << "接收Pcl数据校验错误！！！！";
        for (size_t i = 0; i < 105; i++)
        {
            std::cout << (int)buff[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "cur cnt :" << (int)ask_plc_read.data1 << " ," << (int)ask_plc_read.data2 << std::endl;
        memset(&buff, 0, sizeof(buff));

        // usleep(1000*1000*15);
        return;
    }

    pc = (char *)(&msg);
    for (int i{0}; i < (int)sizeof(ReadData); i++, cnt++)
    {
        *(pc + i) = buff[cnt + 9];
    }

    reverseByte(pc, 0, 105, 4);

    msg = *(ReadData *)pc;
    // std::lock_guard<std::mutex> LockGuard(m_lock);
    // recv_data_queue_.push(msg);

    std::lock_guard<std::mutex> LockGuard(params_event->getMylock());

    params_event->getTotalParams().protocol_data.read_data.angle = msg.angle;
    params_event->getTotalParams().protocol_data.read_data.build_map_signal = msg.build_map_signal;
    params_event->getTotalParams().protocol_data.read_data.comnunication_flag = msg.comnunication_flag;
    params_event->getTotalParams().protocol_data.read_data.device_status = msg.device_status;
    params_event->getTotalParams().protocol_data.read_data.lidar_x = msg.lidar_x;
    params_event->getTotalParams().protocol_data.read_data.lidar_y = msg.lidar_y;
    params_event->getTotalParams().protocol_data.read_data.lidar_z = msg.lidar_z;

    params_event->getTotalParams().protocol_data.read_data.material_area_x = msg.material_area_x;
    params_event->getTotalParams().protocol_data.read_data.material_area_y = msg.material_area_y;
    params_event->getTotalParams().protocol_data.read_data.meterial_area_length = msg.meterial_area_length;
    params_event->getTotalParams().protocol_data.read_data.meterial_area_width = msg.meterial_area_width;
    params_event->getTotalParams().protocol_data.read_data.resolution = msg.resolution;
    params_event->getTotalParams().protocol_data.read_data.shipyard_safe_distance = msg.shipyard_safe_distance;
    params_event->getTotalParams().protocol_data.read_data.technology = msg.technology;

    params_event->getTotalParams().protocol_data.read_data.unused_2 = msg.unused_2;
    params_event->getTotalParams().protocol_data.read_data.unused_2 = msg.unused_2;
    params_event->getTotalParams().protocol_data.read_data.unused_2 = msg.unused_2;

    params_event->Notify(params_event->getTotalParams(), false);

    // std::cout << "============" << std::endl;
    // std::cout << msg.lidar_x << std::endl;
    // std::cout << msg.lidar_y << std::endl;
    // std::cout << msg.lidar_z << std::endl;
    // std::cout << msg.shipyard_safe_distance << std::endl;

    // std::cout << msg.resolution << std::endl;
    // std::cout << msg.build_map_signal << std::endl;
    // std::cout << msg.comnunication_flag << std::endl;
    // std::cout << msg.device_status << std::endl;

    // std::cout << msg.material_area_x << std::endl;
    // std::cout << msg.material_area_y << std::endl;
    // std::cout << msg.material_area_x << std::endl;
    // std::cout << msg.meterial_area_length << std::endl;
    // std::cout << msg.meterial_area_width << std::endl;

    // std::cout << msg.technology << std::endl;
    // std::cout << msg.angle << std::endl;
    // std::cout << msg.x_roll << std::endl;
    // std::cout << msg.y_pitch << std::endl;
    // std::cout << msg.z_yaw << std::endl;

    // std::cout << msg.quaternion_w << std::endl;
    // std::cout << msg.quaternion_x << std::endl;
    // std::cout << msg.quaternion_y << std::endl;
    // std::cout << msg.quaternion_z << std::endl;
    // std::cout << msg.unused_1 << std::endl;
    // std::cout << msg.unused_2 << std::endl;
    // std::cout << msg.unused_3 << std::endl;

    // std::cout << "====-----------------------========" << std::endl;
}
