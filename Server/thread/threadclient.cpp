/*
 *  Реализация функционала в отдельном потоке для
 * хостов которые подключаются к серверу
 *
 * функция logger() - ведет журналирование команд выполняемых хостами
 * функция dataSender() - отправляет уведомление хосту о возможности или не возможности
 * связи
 * функция checkNameAndSendSignal() - в зависимости от имени хоста отправит сигнал
 * функция read() - читает данные которые приходят с хостов
 * и вызывает checkNameAndSendSignal() и logger()
*/
#include "threadclient.h"
#include "ui_dialog.h"
#include <QTcpSocket>
#include <QStringListModel>
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>


ThreadClient::ThreadClient(int socketDescriptor,QObject* parent)
    : QObject(parent), socketDescriptor(socketDescriptor)
{
    qRegisterMetaType<Packet>("Packet");

    //создаю объект сокета клиента
    newUser = new QTcpSocket;

    pack.setHostId(SERVER_ID);

    //устанавливаю уникальный ключ для сокета клиента
    if (!newUser->setSocketDescriptor(socketDescriptor)) {
        emit error(newUser->error());
        qDebug() << "err";
        return;
    }

    connects();

    //TO DO uniq sock desc to serv
    //send_SockDesc(socketDescriptor, pack);
    to_Ask_Name();
}

bool ThreadClient::to_Ask_Name()
{
    pack.setIdCommand(TO_ASK_NAME);
    send_Short_Data();
};
bool ThreadClient::send_SockDesc(int desc)
{

}
bool ThreadClient::send_Short_Data()
{
    //отправляю короткую команду
    QByteArray arr;
    QDataStream out(&arr, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << pack;

    newUser->write(arr);
    newUser->waitForBytesWritten();


};
//отправляю строку уведомление сокету
/*void ThreadClient::dataSender()
{
    QByteArray arr;
    QDataStream out(&arr, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_4_0);
    out << pack;

    out.device()->seek(0);
    out << quint64(arr.size() - sizeof(quint64));
    newUser->write(arr);
}*/
//проверяю данные которые пришли от клиентов и записываю их в таблицу
void ThreadClient::checkNameAndSendSignal(Packet pack)
{
    /*if(pack.getNameCommand() == "json")
    {
        emit sendData(socketDescriptor,pack); //устанавливаю в таблицу новый лог
        emit sendJsonFromThread(socketDescriptor,pack); //отправляю пакет в котором json
        return;

    }
    emit sendData(socketDescriptor,pack);*/

}



ThreadClient::~ThreadClient()
{

}
