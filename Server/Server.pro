QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog.cpp \
    main.cpp \
    serverObject/ModelTable.cpp \
    serverObject/connections.cpp \
    serverObject/errorHandler.cpp \
    serverObject/sendData.cpp \
    serverObject/server.cpp \
    getHost.cpp \
    serverObject/slots_server.cpp \
    serverObject/tableWork.cpp \
    thread/slots_thread.cpp \
    thread/threadclient.cpp

HEADERS += \
    Pack.h \
    modelTable.h \
    ui_dialog.h\
    dialog.h \
    server.h \
    serverObject/server.h \
    thread/threadclient.h \
    threadclient.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    dialog.ui

RESOURCES += \
    logger.qrc

