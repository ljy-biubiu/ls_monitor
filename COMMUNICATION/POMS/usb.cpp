#include "usb.h"

void POMS::init()
{
    INTIMUGPS();
    this->init_thread();
}

void POMS::init_thread()
{
    std::thread dowork_thread(std::bind(&POMS::run, this));
    dowork_thread.detach();
}

void POMS::globalParamsCallback(TotalParams msg, bool save_flag)
{
    // this->my_port = msg.baseParams.lowerMachineBase.port;
    // this->my_ip = msg.baseParams.lowerMachineBase.ip;

    // if (compare_write_data((char *)(&this->cur_write_data), (char *)(&msg.protocol_data.write_data)))
    // {
    //     this->cur_write_data = msg.protocol_data.write_data;
    //     send_write_data_flag = true;
    // }
}

bool POMS::send_data(WriteData &msg)
{
}

void POMS::run()
{
    while (1)
    {
        char IMUGPSData[1024 + 97] = {0};
        unsigned int readDataNum = 0;
        char GPSdata[1024] = {0};
        readDataNum = readDataTty(fdSerial, IMUGPSData, 2, 1024);
        // printf("readDataNum : %d\n", readDataNum);
        for (int i = 0; i < readDataNum; i++)
        {
            if (IMUGPSData[i] == '$' && IMUGPSData[i + 1] == 'G' && IMUGPSData[i + 2] == 'P' && IMUGPSData[i + 3] == 'F' && IMUGPSData[i + 4] == 'P' && IMUGPSData[i + 5] == 'D')
            {
                if (readDataNum - i > 97)
                {
                    // std::cout << i << std::endl;
                    for (int j = 0; j < 97; j++)
                    {
                        GPSdata[j] = IMUGPSData[i + j];
                    }
                    if (GPSdata[0] == '$' && GPSdata[1] == 'G' && GPSdata[2] == 'P' && GPSdata[3] == 'F' && GPSdata[4] == 'P' && GPSdata[5] == 'D')
                    {

                        std::string str;
                        str.assign((char *)GPSdata, sizeof(GPSdata));

                        //str = "$GPHPD,2232,206310.60,,,,22.7438507,113.8172101,23.96,0.002,-0.008,0.013,,7,7,0,1*46";

                        std::vector<std::string> list = MyUtil::split(str, ",");
                        if (list.size() < 15)
                            return;

                        //   GPSWeek=; // 自1980-1-6至当前的星期数
                        //  GPSTime[BUF_SIZE];  // 本周00：00：00至当前的秒数
                        gpfpd_info.Heading=atof(list[3].c_str());        // 偏航角
                        //  Pitch=          // 俯仰角
                        //  Roll=;           // 滚转角
                        //  Latitude=;      // 纬度 deg
                        //  Longitude=;     // 经度 deg  35
                        //  Altitude=;       // 高度 m     29
                        //  Ve=;             // 东 速度 m/s
                        //  Vn=;             // 北 速度 m/s
                        //  Vu=;             // 天 速度 m/s
                        //  Baseline=;       // 基线长度
                        //  NSV1=;             // 天线1卫星数
                        //  NSV2=;             // 天线2卫星数
                        //  Status[4];          // 系统状态

                        // Heading = atof(list[3].c_str());
                        // Picth = atof(list[4].c_str());
                        // roll = atof(list[5].c_str());
                        // latitude = atof(list[6].c_str());
                        // longitude = atof(list[7].c_str());
                        // height = atof(list[8].c_str());

                        char *temp;
                        temp = strtok(GPSdata, ",");
                        for (int m = 0; m < 14; m++)
                        {
                            temp = strtok(NULL, ",");
                            if (m == 0)
                            {
                                Gps_week = (int)atof(temp); // ����
                                printf("Gps_week : %d\n", Gps_week);
                            }
                            if (m == 1)
                            {
                                Gps_time = (double)atof(temp); // ����
                                printf("Gps_time : %.7f\n", Gps_time);
                            }
                        }
                    }
                }
            }
        }
    }
    return;
}

/*******************************************************/
/**下面的函数暂时并没什么意思，完全可以忽略**/
int POMS::read_data_tty(int fd, char *rec_buf, int rec_wait)
{
    int retval;
    fd_set rfds;
    struct timeval tv;

    int ret, pos;
    tv.tv_sec = rec_wait;
    tv.tv_usec = 0;
    pos = 0;

    while (1)
    {
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);

        retval = select(fd + 1, &rfds, NULL, NULL, &tv);

        if (retval == -1)
        {
            perror("select()");
            break;
        }
        else if (retval)
        {
            ret = read(fd, rec_buf + pos, 2048);
            pos += ret;
            if (rec_buf[pos - 2] == '\r' && rec_buf[pos - 1] == '\n')
            {
                FD_ZERO(&rfds);
                FD_SET(fd, &rfds);
                retval = select(fd + 1, &rfds, NULL, NULL, &tv);

                if (!retval)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }

    return 1;
}

int POMS::device_485_receive(int fd)
{
    int ret;
    char rec_buf[1024];
    int i;
    char send_buf[] = {"02030202f925"};

    for (i = 0; i < 10; i++)
    {
        /*ret = write(fd, send_buf, strlen(send_buf));
        if (ret == -1) {
            printf("write device %s error\n", device);
            return -1;
        }*/

        // if (read_data_tty(fd, rec_buf, rec_buf_wait_2s)) {
        if (read_data_tty(fd, rec_buf, 2))
        {
            printf("%s\n", rec_buf);
        }
        else
        {
            printf("read_error\n");
        }

        // if ((read(fd, rec_buf, strlen(rec_buf))) == -1) {
        //       printf("error reading string\n");
        //       return -1;
        // } else {
        //       printf("%s\n", rec_buf);
    }
    return 0;
}
/*-----------------------------------------------------*/
/*******************************************************/

/*************Linux and Serial Port *********************/
/*************Linux and Serial Port *********************/
int POMS::openPort(int fd, int comport)
{

    if (comport == 1)
    {
        fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
        if (-1 == fd)
        {
            perror("Can't Open Serial Port");
            return (-1);
        }
        else
        {
            printf("open ttyS0 .....\n");
        }
    }
    else if (comport == 2)
    {
        fd = open("/dev/ttyS1", O_RDWR | O_NOCTTY | O_NDELAY);
        if (-1 == fd)
        {
            perror("Can't Open Serial Port");
            return (-1);
        }
        else
        {
            printf("open ttyS1 .....\n");
        }
    }
    else if (comport == 3)
    {
        fd = open("/dev/ttyS2", O_RDWR | O_NOCTTY | O_NDELAY);
        if (-1 == fd)
        {
            perror("Can't Open Serial Port");
            return (-1);
        }
        else
        {
            printf("open ttyS2 .....\n");
        }
    }
    /*************************************************/
    else if (comport == 4)
    {
        fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
        if (-1 == fd)
        {
            perror("Can't Open Serial Port");
            return (-1);
        }
        else
        {
            printf("open ttyUSB0 .....\n");
        }
    }

    if (fcntl(fd, F_SETFL, 0) < 0)
    {
        printf("fcntl failed!\n");
    }
    else
    {
        printf("fcntl=%d\n", fcntl(fd, F_SETFL, 0));
    }
    if (isatty(STDIN_FILENO) == 0)
    {
        printf("standard input is not a terminal device\n");
    }
    else
    {
        printf("is a tty success!\n");
    }
    printf("fd-open=%d\n", fd);
    return fd;
}

int POMS::setOpt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio, oldtio;
    if (tcgetattr(fd, &oldtio) != 0)
    {
        perror("SetupSerial 1");
        return -1;
    }
    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag |= CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;

    switch (nBits)
    {
    case 7:
        newtio.c_cflag |= CS7;
        break;
    case 8:
        newtio.c_cflag |= CS8;
        break;
    }

    switch (nEvent)
    {
    case 'O': // 奇校验
        newtio.c_cflag |= PARENB;
        newtio.c_cflag |= PARODD;
        newtio.c_iflag |= (INPCK | ISTRIP);
        break;
    case 'E': // 偶校验
        newtio.c_iflag |= (INPCK | ISTRIP);
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N': // 无校验
        newtio.c_cflag &= ~PARENB;
        break;
    }

    switch (nSpeed)
    {
    case 2400:
        cfsetispeed(&newtio, B2400);
        cfsetospeed(&newtio, B2400);
        break;
    case 4800:
        cfsetispeed(&newtio, B4800);
        cfsetospeed(&newtio, B4800);
        break;
    case 9600:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    case 115200:
        cfsetispeed(&newtio, B115200);
        cfsetospeed(&newtio, B115200);
        break;
    default:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    }
    if (nStop == 1)
    {
        newtio.c_cflag &= ~CSTOPB;
    }
    else if (nStop == 2)
    {
        newtio.c_cflag |= CSTOPB;
    }
    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN] = 0;
    tcflush(fd, TCIFLUSH);
    if ((tcsetattr(fd, TCSANOW, &newtio)) != 0)
    {
        perror("com set error");
        return -1;
    }
    printf("set done!\n");
    return 0;
}

int POMS::readDataTty(int fd, char *rcv_buf, int TimeOut, int Len)
{
    int retval;
    fd_set rfds;
    struct timeval tv;
    int ret, pos;
    tv.tv_sec = TimeOut / 1000;         // set the rcv wait time
    tv.tv_usec = TimeOut % 1000 * 1000; // 100000us = 0.1s

    pos = 0;
    while (1)
    {
        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);
        retval = select(fd + 1, &rfds, NULL, NULL, &tv);
        if (retval == -1)
        {
            perror("select()");
            break;
        }
        else if (retval)
        {
            ret = read(fd, rcv_buf + pos, 1);
            if (-1 == ret)
            {
                break;
            }

            pos++;
            if (Len <= pos)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    return pos;
}

int POMS::sendDataTty(int fd, char *send_buf, int Len)
{
    ssize_t ret;

    ret = write(fd, send_buf, Len);
    if (ret == -1)
    {
        printf("write device error\n");
        return -1;
    }

    return 1;
}

int POMS::INTIMUGPS()
{
    int iSetOpt = 0; // SetOpt 的增量i

    // openPort
    if ((fdSerial = openPort(fdSerial, 4)) < 0) // 1--"/dev/ttyS0",2--"/dev/ttyS1",3--"/dev/ttyS2",4--"/dev/ttyUSB0" 小电脑上是2--"/dev/ttyS1"
    {
        perror("open_port error");
        return -1;
    }

    if ((iSetOpt = setOpt(fdSerial, 115200, 8, 'N', 1)) < 0)
    {
        perror("set_opt error");
        return -1;
    }
    printf("Serial fdSerial=%d\n", fdSerial);

    tcflush(fdSerial, TCIOFLUSH); // 清掉串口缓存
    fcntl(fdSerial, F_SETFL, 0);
}
