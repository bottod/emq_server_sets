#include "fakemqttserver.h"

FakeMqttServer::FakeMqttServer(QObject *parent) : QObject(parent)
{
}

void FakeMqttServer::mqtt_init()
{
    std::cout<<"fake_server init...."<<std::endl;
    MqttSql s;
    s.mysql_init_from_file();       //can add or not add,cause below statement has dealed it, but you'd better add it
    s.mysql_create_table();

    mqtt_init_from_file();      /*  init from conf/mqtt_info.conf    */

    m_fake_server.connectToHost();   /*  real connect    */
    if(m_fake_server.state() == 1)
        std::cout<<"fake_server connecting...."<<std::endl;

    /* c++11 lambda; just for study; */
//    connect(&m_client, &QMqttClient::connected, [&](){m_client.subscribe(QString("topic_name"));});
//    connect(&m_client, &QMqttClient::messageReceived, this, [&](const QByteArray &message, const QMqttTopicName &topic)
//    {std::cout<<topic.name().toStdString()<<" Message: "<<message.toStdString()<<std::endl;});
    connect(&m_fake_server,&QMqttClient::connected,this,&FakeMqttServer::mqtt_sub);
    connect(&m_fake_server,&QMqttClient::messageReceived,this,&FakeMqttServer::mqtt_msg_recv);
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
            if(line_info.size() && line_info.at(0) != '#' )
                m_fake_server.subscribe(QString::fromStdString(line_info));
        }
        std::cout<<"Info: Subscribe success!!"<<std::endl;
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
    MqttSql sql;

    time_t now_time;
    now_time = time(nullptr);
    tm *now_time_p;
    now_time_p = localtime(&now_time);

    sql.mysql_init_from_file();
    sql.mq_insert(topic.name().toStdString(), message.toStdString());
    std::cout<<1900+now_time_p->tm_year<<"/"<<1+now_time_p->tm_mon<<"/"<<now_time_p->tm_mday<<" ";
    std::cout<<now_time_p->tm_hour<<":"<<now_time_p->tm_min<<":"<<now_time_p->tm_sec<<" ";
    std::cout<<topic.name().toStdString()<<" Message: "<<message.toStdString()<<std::endl;
}

void FakeMqttServer::mqtt_init_from_file()
{
    std::ifstream mqtt_info_file;
    int64_t count = 0;//string array count
    std::string mqtt_info[5];//only 5 line; not start with '#' and not empty line
    mqtt_info_file.open("conf/mqtt_info.conf");
    if(mqtt_info_file.is_open())
    {
        std::string line_info;
        while (getline(mqtt_info_file,line_info))
        {
            if(count < 5)
            {
                if(line_info.size() && line_info.at(0) != '#' )
                {
                    mqtt_info[count] = line_info;
                    ++count;
                }
            }
            else if(count >= 5 )
            {
                break;
            }
        }
        mqtt_info_file.close();
        if(count >= 5)//must be 5
        {
            m_fake_server.setHostname(mqtt_info[0].c_str());
            m_fake_server.setUsername(mqtt_info[1].c_str());
            m_fake_server.setPassword(mqtt_info[2].c_str());
            m_fake_server.setPort(static_cast<quint16>(atoi(mqtt_info[3].c_str())));
            m_fake_server.setClientId(mqtt_info[4].c_str());

            std::cout<<"Info: mqtt init OK! you must be sure that your info is correct!"<<std::endl;
        }
        else
        {
            std::cout<<"Error: your mqtt_info conf not correct!!"<<std::endl;
            exit(0);
        }
    }
    else
    {
        std::cout<<"Error: Can't Open mqtt_info conf! Please checkout this conf!!"<<std::endl;
        exit(0);
    }
}

