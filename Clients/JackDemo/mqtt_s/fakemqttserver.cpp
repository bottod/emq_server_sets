#include "fakemqttserver.h"

FakeMqttServer::FakeMqttServer(QObject *parent) : QObject(parent)
{
}

void FakeMqttServer::mqtt_test()
{
    qDebug()<<"start";
    m_client.setHostname("172.16.163.134");
    m_client.setUsername("admin");
    m_client.setPassword("jack");
    m_client.setPort(1883);
    m_client.setClientId("hwx");
    m_client.connectToHost();
    qDebug()<<m_client.state();

    /* c++11 lambda; just for study; */
    // connect(&m_client, &QMqttClient::connected, [&](){m_client.subscribe(QString("/aa"));});
    /* to make code more readable,I decide not use it */
    connect(&m_client, &QMqttClient::connected,this,&FakeMqttServer::mqtt_sub);
}

void FakeMqttServer::mqtt_sub()
{
    m_client.subscribe(QString("/ab"));
}
