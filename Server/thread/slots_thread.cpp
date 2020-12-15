#include "threadclient.h"

//читаю данные от сокета
void ThreadClient::slot_read()
{
    QDataStream in;
    in.setDevice(newUser);
    in.setVersion(QDataStream::Qt_4_0);
    int countMain = 1;
    while(newUser->bytesAvailable())
    {
        in.startTransaction();

        Packet pack;
        in >> pack;

        qDebug() << pack.getDateAndTime() << pack.getHostName();
        qDebug() << "slot_read 1";
        if (!in.commitTransaction())
              return;
        qDebug() << "slot_read 2";
        QDateTime time = pack.getDateAndTime();
        QString host = pack.getHostName();
        QString nameCommand = pack.getNameCommand();
        QString textCommand = pack.getTextCommand();
        QVariant command = pack.getCommand();
        qDebug() << "get data" << host << time << nameCommand << textCommand;
        //проверка комманд
        checkNameAndSendSignal(pack);
        //логгирование
        emit logger(pack);
        if(countMain == 1)
        {
            qDebug() << host << " threaf";
            emit new_client_set_item_from_thread(host,socketDescriptor);
            countMain = 0;
        }
    }

}
//разрыв соединения
void ThreadClient::slot_disconnectHost()
{
    qDebug() << "slot disconnect";
    emit connect_finished_signal(socketDescriptor);
    this->~ThreadClient();
}
