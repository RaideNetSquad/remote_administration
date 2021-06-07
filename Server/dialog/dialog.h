#pragma once
#include <QMainWindow>
#include <QtNetwork>
#include "serverLogic/server.h"
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
    //объект интерфейса
    Ui::Dialog *ui;
protected:
    //логика сервера
    Server* serv;
    //имя хоста
    QHostAddress host;
    int port;
    //поток?
    int threadsMy;
    bool getHost();
    void checkErrorGettingHost();
private slots:
    void closeApp();
signals:
    void closeUi();
};
