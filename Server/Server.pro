QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Provider/Provider_Network_Data.cpp \
    dialog/dialog.cpp \
    dialog/getHost.cpp \
    table_work/ModelTable.cpp \
    table_work/table_work.cpp \
    serverLogic/connections.cpp \
    serverLogic/errorHandler.cpp \
    serverLogic/sendData.cpp \
    serverLogic/server.cpp \
    serverLogic/slots_server.cpp \
    thread/slots_thread.cpp \
    thread/threadclient.cpp \
    thread/connects.cpp \
    qmap/clients_map_object.cpp \
    main.cpp \

HEADERS += \
    Provider/Provider_Network_Data.h \
    serverLogic/server.h \
    table_work/modelTable.h \
    table_work/table_work.h \
    ui_dialog.h\
    dialog/dialog.h \
    thread/threadclient.h \
    qmap/clients_map_object.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    dialog/dialog.ui

RESOURCES += \
    logger.qrc

