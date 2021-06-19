QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ClientObjectLogic/sendData.cpp \
    ClientObjectLogic/slots_ClientObjectLogic.cpp \
    ServerObjectLogic/jobWithJson.cpp \
    ServerObjectLogic/parserFile.cpp \
    ServerObjectLogic/slots_ServerObjectLogic.cpp \
    ServerWindow/slots_ServerWindow.cpp \
    main.cpp \
    ServerWindow/serverwindow.cpp \
    ServerObjectLogic/serverObjectLogic.cpp \
    ClientObjectLogic/clientObjectLogic.cpp \
    ClientObjectLogic/connectorCommands.cpp \
    RolesMap/rolesMap.cpp

HEADERS += \
    ServerWindow/serverwindow.h \
    ServerObjectLogic/serverObjectLogic.h \
    ClientObjectLogic/clientObjectLogic.h \
    RolesMap/rolesMap.h

FORMS += \
    ServerWindow/serverwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
