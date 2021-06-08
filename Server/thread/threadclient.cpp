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

    pack.setClientId(socketDescriptor);

    //устанавливаю уникальный ключ для сокета клиента
    if (!newUser->setSocketDescriptor(socketDescriptor)) {
        emit error(newUser->error());
        qDebug() << "err";
        return;
    }

    connects();

    to_Ask_Name();
}

bool ThreadClient::to_Ask_Name()
{

    pack.setIdCommand(TO_ASK_NAME);
    send_Short_Data();
};

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
/*void ThreadClient::checkNameAndSendSignal(Packet pack)
{
    /*if(pack.getNameCommand() == "json")
    {
        emit sendData(socketDescriptor,pack); //устанавливаю в таблицу новый лог
        emit sendJsonFromThread(socketDescriptor,pack); //отправляю пакет в котором json
        return;

    }
    emit sendData(socketDescriptor,pack);

}
*/
void ThreadClient::full_Message(QDateTime t, QString m, QString tM)
{
    this->dateTime = t;
    this->nameMessage = m;
    this->textMessage = tM;
};

void ThreadClient::controller_network_command()
{
    QString nameHostClient = pack.get_ByteData();

    QDateTime dateTime = QDateTime::currentDateTime();

    //обработчик команды получения имени
    if(pack.getIdCommand() == GET_NAME)
    {
        QString name = pack.get_ByteData();
        QString data = "Подключение клиента ";

        full_Message(dateTime, data, name);

        emit sendData_toTable(name, data);

        emit logger(this->dateTime,
                    this->nameMessage,
                    this->textMessage);
        //сигнал записи имени и уникального ид в словарь клиентов
        emit send_name_and_socket_to_qmap(nameHostClient, socketDescriptor);

        emit got_Name_Client();
    }
};

ThreadClient::~ThreadClient()
{

}
