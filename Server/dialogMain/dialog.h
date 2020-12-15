#pragma once
#include <QMainWindow>
#include <QtNetwork>
#include "../serverObject/server.h"
#include "../nextForm/send/send.h"
#include "../nextForm/status/status.h"
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
    StatusForm* status;
    SendForm* send;
protected:
    Server* serv;
    QHostAddress host;
    int port;
    int threadsMy;
    bool getHost();
    void checkErrorGettingHost();
private slots:
    void slot_setRowTable(QString, QString);
    void closeApp();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

signals:
    void setRowTable_dialog(QString, QString);
    void closeUi();
};
