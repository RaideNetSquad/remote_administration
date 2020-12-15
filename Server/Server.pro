QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialogMain/getHost.cpp \
    dialogMain/dialog.cpp \
    dialogMain/handlerErrorDialog.cpp \
    dialogMain/slots_dialog.cpp \
    main.cpp \
    serverObject/connections.cpp \
    serverObject/errorHandler.cpp \
    serverObject/sendData.cpp \
    serverObject/server.cpp \
    serverObject/slots_server.cpp \
    thread/slots_thread.cpp \
    thread/threadclient.cpp \
    nextForm/send/send.cpp \
    nextForm/status/status.cpp \
    nextForm/status/table/tableWork.cpp\
    nextForm/status/table/ModelTable.cpp

HEADERS += \
    Pack.h \
    ui_dialog.h\
    dialogMain/dialog.h \
    server.h \
    serverObject/server.h \
    thread/threadclient.h \
    threadclient.h \
    nextForm/send/send.h \
    nextForm/status/status.h \
    nextForm/status/table/modelTable.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    ui/dialog.ui \
    ui/sendFile.ui \
    ui/status.ui



