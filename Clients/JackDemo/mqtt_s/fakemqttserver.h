#ifndef FAKEMQTTSERVER_H
#define FAKEMQTTSERVER_H

#include <QObject>
#include "qmqttclient.h"
#include <QDebug>

class FakeMqttServer : public QObject
{
    Q_OBJECT
public:
    explicit FakeMqttServer(QObject *parent = nullptr);
    void mqtt_test();
    void mqtt_sub();

private:
    QMqttClient m_client;

signals:

public slots:
};

#endif // FAKEMQTTSERVER_H
