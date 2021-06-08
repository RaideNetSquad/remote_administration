QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Provider_Network_Data.cpp \
    connections.cpp \
    form_json_send.cpp \
    infobox.cpp \
    main.cpp \
    network.cpp \
    slots_form_json.cpp \
    slots_network.cpp

HEADERS += \
    Provider_Network_Data.h \
    form_json_send.h \
    network.h

FORMS += \
    confjson.ui \
    jsonsender.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
