QT += sql
QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    fakemqttserver.cpp \
    mqttsql.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




# Add By Jack | Must be changed if you modify "Require" folder | top 2 line for windows(no use)
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Require/lib -lQt5Mqtt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Require/lib/ -lQt5Mqttd
else:unix: LIBS += -L$$PWD/Require/lib/ -lQt5Mqtt
INCLUDEPATH += $$PWD/Require/include/
DEPENDPATH += $$PWD/Require/include/

HEADERS += \
    fakemqttserver.h \
    mqttsql.h

