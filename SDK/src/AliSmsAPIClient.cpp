#include "AliSmsAPIClient.h"

AliSmsAPIClient::AliSmsAPIClient()
{
    AlibabaCloud::InitializeSdk();
    AlibabaCloud::ClientConfiguration configuration( "cn-hangzhou" );
    AlibabaCloud::Credentials credential( "LTAI5tS4UwDKyinDRQFcpWJu", "Gxg7KCpLeDOEhN5gFPrv9QT8Xv1NsP");
    client = new DysmsapiClient( credential, configuration);
}

AliSmsAPIClient::~AliSmsAPIClient()
{
    AlibabaCloud::ShutdownSdk();
}

/**
 * @brief sendSMS
 * @param number:手机号
 * @param DeviceNumber:设备编号
 * @return -1:error 1:successful
 */
int AliSmsAPIClient::SendSMS(string Number,string DeviceNumber){


    Model::SendSmsRequest request;
    request.setSignName("LSLiDAR");
    request.setTemplateCode("SMS_249070139");
    request.setPhoneNumbers(Number);
    request.setTemplateParam(QString("{\"number\":\"%1\",\"time\":\"%2\"}").arg(DeviceNumber.c_str()).arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss ddd")).toStdString());

    auto outcome = client->sendSms( request );

    if ( !outcome.isSuccess() )
    {
        cout << outcome.error().errorCode() << std::endl
                  <<outcome.error().errorMessage() << std::endl;
        AlibabaCloud::ShutdownSdk();
        return(-1);
    }


    return 0;
}

/**
 * @brief SendSMSList
 * @param NumberList:群发手机号列表
 * @param DeviceNumber:设备编号
 * @return -1:error 1:successful
 */
int AliSmsAPIClient::SendSMSList(vector<string> NumberList,string DeviceNumber){
    for(auto number:NumberList)
    {
        int result=SendSMS(number,DeviceNumber);
        if(result==-1)
            return -1;
    }
    return 0;

}
