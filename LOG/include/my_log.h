#ifndef MYLOG_H
#define MYLOG_H

#include <QFile>
#include <QDir>
#include <QMutex>
#include <QDateTime>
#include <QTextStream>
#include "paramsevent.hpp"


void createLogFile();
void initParamEventLog(std::shared_ptr<ParamsEvent<ObserverFunc>> params_event_);
static void outputMessage( QtMsgType type, const QMessageLogContext& context, const QString& msg );

#endif // MYLOG_H
