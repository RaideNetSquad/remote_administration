QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    job_WithFilesJson.cpp \
        main.cpp \
    mainwindow.cpp \
    parser_Instructions.cpp \
    rule_map.cpp \
    send_Data.cpp \
    slots_window.cpp

HEADERS += \
    mainwindow.h \
    rule_map.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../build-QTCPServer-Desktop_Qt_5_15_0_GCC_64bit-Debug/time_do.json \
    rules
