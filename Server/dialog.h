#pragma once
#include <QMainWindow>
#include <QtNetwork>
#include "serverObject/server.h"
namespace Ui {
    class Dialog;
}

class Dialog : public QMainWindow
{
    Q_OBJECT
public:
        explicit Dialog(QWidget *parent = 0);
        ~Dialog();
private:
    Ui::Dialog *ui;
protected:
    Server* serv;
    QHostAddress host;
    int port;
    int threadsMy;
    bool getHost();
    void checkErrorGettingHost();
private slots:
    void closeApp();
signals:
    void closeUi();
};
