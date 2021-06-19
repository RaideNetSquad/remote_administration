#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include <QHostAddress>
#include <QMutex>
#include <QMutexLocker>

#include "ServerObjectLogic/serverObjectLogic.h"
#include "ui_serverwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ServerWindow; }
QT_END_NAMESPACE

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    ServerWindow(QWidget *parent = nullptr);
    ~ServerWindow();

private:
    Ui::ServerWindow *ui;

    QHostAddress addr;
    quintptr port;

    ServerObjectLogic *serverLogic;
    QMutex mutex;
    QFile log;
signals:
    void newMessage(const QString&);
private slots:
    void on_pushButton_clicked();
    void slot_DisplayMessage(const QString &message);
    void slot_ErrorServer(const QString &textError);
    void logger(const QString &message);
    void newConnection();
};
#endif // SERVERWINDOW_H


