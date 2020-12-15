#pragma once
#include "ui_dialog.h"
#include "../Pack.h"
#include <QThread>
#include <QTcpSocket>
#include <QtWidgets>
#include <QMutex>

class ThreadClient : public QObject
{
    Q_OBJECT

public:
    explicit ThreadClient(int socketDescriptor,
                 QObject* parent = 0);
    ~ThreadClient();
public:
    quint64 nextBlock;
private:
    Packet pack;
    int socketDescriptor;
    QTcpSocket* newUser;
    QDataStream in;
    QDataStream out;
    void dataSender();
    void checkNameAndSendSignal(Packet pack);
signals:
    void new_client_set_item_from_thread(QString, int);
    void connect_finished_signal(int);
    void logger(Packet pack);
    void notFoundHost(QString, QString);
    void SendDataToHost(QMap<QString, int>::iterator &it, QString &command);
    void checkHost(QString);
    void error(QTcpSocket::SocketError socketError);
    void finished();
    void sendJsonFromThread(int, Packet pack);
    void sendData(int,Packet);
    //int getSocketDeskriptor(QDateTime time, QString name, QVariant command, int des);
    void jsonSender();
private slots:
    void slot_read();
    void slot_disconnectHost();
};


