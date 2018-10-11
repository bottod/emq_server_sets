#ifndef MQTTSQL_H
#define MQTTSQL_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

class MqttSql : public QObject
{
    Q_OBJECT
public:
    explicit MqttSql(QObject *parent = nullptr);

private:
    QSqlDatabase db;
    QSqlQuery query;

public:
    int64_t mq_insert(std::string table_name,std::string col_name,std::string value);

signals:

public slots:
};

#endif // MQTTSQL_H
