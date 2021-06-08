/*
 * Логика работы сервера
 */

#pragma once
#include <QtWidgets>
#include <QTcpServer>
#include <QNetworkInterface>
#include "Pack.h"
#include "ui_dialog.h"
#include "table_work/modelTable.h"
#include "thread/threadclient.h"
#include "table_work/table_work.h"
#include "qmap/clients_map_object.h"

class Server : public QTcpServer
{
    Q_OBJECT
private:
    Table_Work *table;
    Packet *pack;
    QMutex *mutex;
    //указатель на объект интерфеса
    Ui::Dialog *ui;

    //вектор сохраняет значения ячеек таблицы
    QVector<HostsCommand> *commandHost;

    Clients_Map_Object *cl_Map_Obj;

    quint64 countRow;
    QMap<QString, int> hosts;
    void getHostInfo(QString, int);
    void errorFoundHost(Packet pack, int socketDescriptor);

    void SendDataToHostError(int socketDescriptor, Packet *pack);
    void SendDataToHostJson(Packet pack, int socketDescriptor);
    void SendDataPack(Packet pack, int socketDescriptor);
public:
    explicit Server(Ui::Dialog *ui, QObject* parent = 0);
public:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    void connects(ThreadClient* cl, QThread* thread);
signals:
    void logger(const QDateTime&,
                const QString&,
                const QString&);
private slots:
    void slot_get_name_and_socket_to_qmap(const QString&, const int&);

    void slot_sendData_toTable(const QString&, const QString&);

    void finish_connect_slot(int);

    void slot_logger(const QDateTime&,
                           const QString&,
                           const QString&);

    //void notFoundHost(QString, QString);
    void getJson(int socketDescriptor, Packet pack);
};


