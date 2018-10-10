#include <QCoreApplication>
#include "fakemqttserver.h"

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

//this demo just for reference
/*
* email: jacksonex_h@163.com
*
* target: when it start, this fake server will subscribe some topic and then it will send this topic message to mysql
*/

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FakeMqttServer fake;
    fake.mqtt_test();


//    QString publish_topic = QString("/World");
//    QString Payload = QString("hello world");
//    m_client->publish(publish_topic, Payload.toUtf8());


      //sql_test

//    //sql Singleton Pattern
//    QSqlDatabase dbconn;
//    if(QSqlDatabase::contains("qt_mqtt_connection"))
//        dbconn = QSqlDatabase::database("qt_mqtt_connection");
//    else
//    {
//        dbconn = QSqlDatabase::addDatabase("QMYSQL","qt_mqtt_connection");//uniqe connection name -> "qt_mqtt_connection"
//        dbconn.setHostName("172.16.163.134");//IP
//        dbconn.setDatabaseName("mq_playground");//database name
//        if(dbconn.open("mq_admin", "mq_password")/*username,password | success return 1*/)
//        {
//            std::cout<<"yes"<<std::endl;
//            if(dbconn.isOpen())
//            {
//                //we don't use default connection name, so we must use constructor
//                QSqlQuery query = QSqlQuery(dbconn);
//                query.exec("select * from mq_farm");
//                query.first();
//                int moisture_col_num = query.record().indexOf("moisture");
//                int temperature_col_num = query.record().indexOf("temperature");
//                for(int i=0;i<1;i++)
//                {
//                    qDebug()<<query.value(moisture_col_num);
//                    qDebug()<<query.value(temperature_col_num);
//                }
//                query.exec("insert into mq_farm values(20,22)");
//            }
//        }

//    }


    return a.exec();
}
