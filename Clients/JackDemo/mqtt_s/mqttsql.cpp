#include "mqttsql.h"
#include <iostream>

MqttSql::MqttSql(QObject *parent) : QObject(parent)
{
    //sql Singleton Pattern
    if(QSqlDatabase::contains("qt_mqtt_connection"))
        db = QSqlDatabase::database("qt_mqtt_connection");
    else
        db = QSqlDatabase::addDatabase("QMYSQL","qt_mqtt_connection");//uniqe connection name -> "qt_mqtt_connection"

    db.setHostName("172.16.163.134");
    db.setDatabaseName("mq_playground");
    db.setUserName("mq_admin");
    db.setPassword("mq_password");

    db.open();
    if(db.isOpen())
        query = QSqlQuery(db);
}

int64_t MqttSql::mq_insert(std::string table_name,std::string col_name,std::string value)
{
    std::string real_table_name;
    real_table_name = "mq_" + table_name.erase(0,1);
    std::string real_col_name;
    real_col_name = col_name.erase(0,1);

    std::string real_query;
    real_query = "INSERT INTO `" + real_table_name + "` ( `" + real_col_name +
            "` ) VALUES (" + value + ")";

    return query.exec(real_query.c_str());
}
