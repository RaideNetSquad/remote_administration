/*
    Логика взаимодействия с клиентом
*/
#pragma once
#include "ui_dialog.h"
#include "serverLogic/Pack.h"
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
    QDateTime dateTime;
    QString nameMessage;
    QString textMessage;
    //для заполнения сообщения логирования
    void full_Message(QDateTime, QString, QString);
private:
    Packet pack;
    int socketDescriptor;
    QTcpSocket* newUser;
    QDataStream in;
    QDataStream out;

    void dataSender();
    void checkNameAndSendSignal(Packet pack);
    void connects();

    //маршрутизатор команд
    void controller_network_command();

    //хочу получить имя клиента
    bool to_Ask_Name();
    //отправляю клиенту пакет
    bool send_Short_Data();

signals:
    void send_name_and_socket_to_qmap(QString &nameHostClient, int &socketDescriptor);
    void got_Name_Client();

    void connect_finished_signal(int);

    void logger(const QDateTime&,
                const QString&,
                const QString&);

    void notFoundHost(QString, QString);
    void SendDataToHost(QMap<QString, int>::iterator &it, QString &command);
    void checkHost(QString);
    void error(QTcpSocket::SocketError socketError);
    void finished();

    void sendJsonFromThread(int, Packet pack);
    void sendData_toTable(const QString&, const QString&);

    //int getSocketDeskriptor(QDateTime time, QString name, QVariant command, int des);
    void jsonSender();
private slots:
    void slot_Got_Name_Client();
    void slot_read();
    void slot_disconnectHost();
};


