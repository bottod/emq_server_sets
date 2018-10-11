#ifndef FAKEMQTTSERVER_H
#define FAKEMQTTSERVER_H

#include <QObject>
#include "qmqttclient.h"
#include "mqttsql.h"
#include <fstream>
#include <iostream>

class FakeMqttServer : public QObject
{
    Q_OBJECT
public:
    explicit FakeMqttServer(QObject *parent = nullptr);

private:
    QMqttClient m_client;
    MqttSql sql;

public:
    void mqtt_init();
    void mqtt_sub();
    void mqtt_msg_recv(const QByteArray &message, const QMqttTopicName &topic);

signals:

public slots:
};

#endif // FAKEMQTTSERVER_H
