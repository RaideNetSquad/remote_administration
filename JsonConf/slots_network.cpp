#include "network.h"
/*
    * Все слоты объекта Network
    * для чтения данных приходящиъ от сервера  - slot_read
    * для закрытия интерфейса в случае ошибки  - slotCloseUi
    * для информировании об ошибках            - slot_errorOpen
*/


void infoBox(QString, QString);

void Network::sendData(Packet *pack)
{
    QByteArray arr;

    QDataStream in(&arr,QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_4_0);

    QDateTime time = QDateTime::currentDateTime();
    pack->setDateAndTime(time);

    in << *pack;

    connectToServ->write(arr);
    connectToServ->waitForBytesWritten();
}

//считываю данные приходящие к хосту
void Network::slot_read()
{
    QDataStream in;
    in.setDevice(connectToServ);
    in.setVersion(QDataStream::Qt_4_0);

    while(connectToServ->bytesAvailable())
    {
        in.startTransaction();

        Packet pack;
        in >> pack;

        if(pack.getNameCommand() == "Error")
        {
            infoBox(pack.getNameCommand(), pack.getTextCommand());
        }
        qDebug() << pack.getDateAndTime() << pack.getHostName();

        if (!in.commitTransaction())
              return;
    }
}

void Network::slotCloseUi()
{
    delete ui;
}

void Network::slot_errorOpen(QString name, QString text)
{
    infoBox(name, text);
}
