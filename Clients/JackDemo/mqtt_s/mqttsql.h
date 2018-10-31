#ifndef MQTTSQL_H
#define MQTTSQL_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <fstream>
#include <iostream>

class MqttSql : public QObject
{
    Q_OBJECT
public:
    explicit MqttSql(QObject *parent = nullptr);

private:
    QSqlDatabase db;
    QSqlQuery query;

public:
    void mq_insert(std::string tablename, std::string value);
    std::string mysql_get_column();    //  get column info
    void mysql_init_from_file();       //  init mysql info
    void mysql_create_table();         //  create all table if not exists


signals:

private:
    void format_string(std::string& input); //clean '/' and only leave after the final '/'

};

#endif // MQTTSQL_H
