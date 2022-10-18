#ifndef ALISMSAPICLIENT_H
#define ALISMSAPICLIENT_H
#include <alibabacloud/core/AlibabaCloud.h>
#include <alibabacloud/dysmsapi/DysmsapiClient.h>
#include <QString>
#include <QDateTime>
#include <iostream>
using namespace std;
using namespace AlibabaCloud;
using namespace AlibabaCloud::Dysmsapi;

class AliSmsAPIClient
{
public:
    AliSmsAPIClient();
    ~AliSmsAPIClient();
    int SendSMS(string Number,string DeviceNumber);
    int SendSMSList(vector<string> NumberList,string DeviceNumber);
private:
    DysmsapiClient *client;
};

#endif // ALISMSAPICLIENT_H
