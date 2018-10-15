#include "fakemqttserver.h"

FakeMqttServer::FakeMqttServer(QObject *parent) : QObject(parent)
{
}

void FakeMqttServer::mqtt_init()
{
    std::cout<<"fake_server init...."<<std::endl;
    m_client.setHostname("101.132.70.232");
    m_client.setUsername("admin");
    m_client.setPassword("jack");
    m_client.setPort(1883);
    m_client.setClientId("fake_server");
    m_client.connectToHost();
    if(m_client.state() == 1)
        std::cout<<"fake_server connecting...."<<std::endl;

    /* c++11 lambda; just for study; */
//    connect(&m_client, &QMqttClient::connected, [&](){m_client.subscribe(QString("topic_name"));});
//    connect(&m_client, &QMqttClient::messageReceived, this, [&](const QByteArray &message, const QMqttTopicName &topic)
//    {
//        std::cout<<topic.name().toStdString()<<" Message: "<<message.toStdString()<<std::endl;
//    });
    connect(&m_client,&QMqttClient::connected,this,&FakeMqttServer::mqtt_sub);
    connect(&m_client,&QMqttClient::messageReceived,this,&FakeMqttServer::mqtt_msg_recv);
}

void FakeMqttServer::mqtt_sub()
{
    std::cout<<"fake_server connected !!"<<std::endl;
    std::ifstream sub_conf_file;
    sub_conf_file.open("conf/subscribe.conf");
    if(sub_conf_file.is_open())
    {
        std::string line_info;
        while (getline(sub_conf_file,line_info))
        {
            m_client.subscribe(QString::fromStdString(line_info));
        }
        sub_conf_file.close();
    }
    else
    {
        std::cout<<"Error: Can't Open subscribe conf! Please checkout this conf!!"<<std::endl;
        exit(0);
    }
}

void FakeMqttServer::mqtt_msg_recv(const QByteArray &message, const QMqttTopicName &topic)
{
    sql.mq_insert(topic.name().toStdString(),topic.name().toStdString(),message.toStdString());
    std::cout<<topic.name().toStdString()<<" Message: "<<message.toStdString()<<std::endl;
}

