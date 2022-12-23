#ifndef DIARY_H
#define DIARY_H

#include <QWidget>
#include <QList>

#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlQueryModel>

#include <mutex>
#include "myparams.h"

const int log_size = 100;

namespace Ui {
class Diary;
}



class Diary : public QWidget
{
    Q_OBJECT

public:
    explicit Diary(QWidget *parent = nullptr);
    ~Diary();

    void pushLogData(const Log &msg);

private:
    Ui::Diary *ui;
    QList<Log> logs;
    QTableWidget* TableWidget;
    std::mutex my_lock;

    QTableWidgetItem* table_widget_item_date;
    QTableWidgetItem* table_widget_item_level;
    QTableWidgetItem* table_widget_item_data;


};

#endif // DIARY_H
