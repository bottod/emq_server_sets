#include <QCoreApplication>
#include "fakemqttserver.h"

//this demo just for reference
/*
* email: jacksonex_h@163.com
*
* target: when it start, this fake server will subscribe some topic and then it will send this topic message to mysql
*/

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("./plugins");
    QCoreApplication a(argc, argv);

    FakeMqttServer fake_server;
    fake_server.mqtt_init();

    return a.exec();
}
