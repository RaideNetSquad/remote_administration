#include "threadclient.h"

//читаю данные от сокета
void ThreadClient::slot_read()
{
    QDataStream in;
    in.setDevice(newUser);
    in.setVersion(QDataStream::Qt_4_0);

    while(newUser->bytesAvailable())
    {
        in.startTransaction();

        Packet pack;
        in >> pack;
        qDebug() << pack.getDateAndTime() << pack.getHostName();

        if (!in.commitTransaction())
              return;

        QDateTime time = pack.getDateAndTime();
        QString host = pack.getHostName();
        QString nameCommand = pack.getNameCommand();
        QString textCommand = pack.getTextCommand();
        QString jsonCommand = pack.getJsonCommand();
        qDebug() << "get data" << host << time << nameCommand << textCommand;
        //проверка комманд
        checkNameAndSendSignal(pack);
        //логгирование
        emit logger(pack);
    }


}
//разрыв соединения
void ThreadClient::slot_disconnectHost()
{
    qDebug() << "slot disconnect";
    emit connect_finished_signal(socketDescriptor);
    this->~ThreadClient();
}
