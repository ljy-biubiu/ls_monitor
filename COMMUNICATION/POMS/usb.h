#ifndef USB_H
#define USB_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h> //set baud rate
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>

#include "communication_interface.h"
#include  "poms.hpp"



class POMS : public ComunicateInterface
{
public:
    POMS();

public:
    virtual void run() override;
    virtual void init() override;
    virtual bool send_data(WriteData &msg) override;
    virtual void globalParamsCallback(TotalParams msg, bool save_flag) override;

private:
    int fdSerial{0};
    int frame{0};
    double Gps_time{0};
    int Gps_week{0};
    GPFPD_INFO gpfpd_info;

    int INTIMUGPS();
    int readDataTty(int fd, char *rcv_buf, int TimeOut, int Len);
    int sendDataTty(int fd, char *send_buf, int Len);
    int setOpt(int fd, int nSpeed, int nBits, char nEvent, int nStop);
    int openPort(int fd, int comport);
    int device_485_receive(int fd);
    int read_data_tty(int fd, char *rec_buf, int rec_wait);
    void init_thread();
};

#endif //