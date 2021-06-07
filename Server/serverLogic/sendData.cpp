#include "server.h"

//метод отправки данных
void Server::SendDataPack(Packet pack, int socketDescriptor)
{
    QDateTime time = QDateTime::currentDateTime();
    //pack.setDateAndTime(time);


    QTcpSocket* send = new QTcpSocket();
    send->setSocketDescriptor(socketDescriptor);
    QByteArray arr;
    QDataStream out(&arr, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << pack;

    send->write(arr);
    send->waitForBytesWritten();
}

