#ifndef ALARM_H
#define ALARM_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include "myparams.h"

struct LEDSTATUS
{
    int communicion_led_color[2]= {5,5};
    int work_led_color[2]= {5,5};
    int system_led_color[2]= {5,5};
    int other_led_color[2]= {5,5};
};

namespace Ui {
class Alarm;
}

class Alarm : public QWidget
{
    Q_OBJECT

public:
    explicit Alarm(QWidget *parent = nullptr);
    ~Alarm();

    void setLED(QLabel* label, int color, int size ,int width);
    QTimer *my_timer;
    void setLEDStatus( const AlarmStatus& msg  );

private:
    Ui::Alarm *ui;
    LEDSTATUS led_status;
    AlarmStatus alarm_status;
    //    AlarmStatus alarm_status;
};

#endif // ALARM_H
