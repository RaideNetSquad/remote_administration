/*
 * Логика работы сервера
 */

#pragma once
#include <QtWidgets>
#include <QTcpServer>
#include <QNetworkInterface>
#include "Pack.h"
#include "ui_dialog.h"
#include "modelTable.h"
#include "thread/threadclient.h"

class Server : public QTcpServer
{
    Q_OBJECT
private:
    Packet *pack;
    QMutex mutex;
    Ui::Dialog *ui;
    QVector<HostsCommand> commandHost;
    ModelTable *tableModel;
    QTableView* clientStatus;
    //QStandardItemModel *model;
    //QStandardItem *item;
    quint64 countRow;
    QMap<QString, int> hosts;
    void getHostInfo(QString, int);
    void errorFoundHost(Packet pack, int socketDescriptor);
    void setRowTable(QString name, QVariant command);
    void SendDataToHostError(int socketDescriptor, Packet *pack);
    void SendDataToHostJson(Packet pack, int socketDescriptor);
    void SendDataPack(Packet pack, int socketDescriptor);
public:
    explicit Server(Ui::Dialog *ui, QObject* parent = 0);
public:
    void incomingConnection(qintptr socketDescriptor) override;
    void setTable(Ui::Dialog *ui);
private:
    void connects(ThreadClient* cl, QThread* thread);
signals:
    void logger(Packet pack);
private slots:
    void finish_connect_slot(int);
    void slot_logger(Packet pack);
    //void notFoundHost(QString, QString);
    void getJson(int socketDescriptor, Packet pack);
    void slot_sendData(int, Packet);
};


