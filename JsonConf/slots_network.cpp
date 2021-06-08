#include "network.h"
/*
    * Все слоты объекта Network
    * для чтения данных приходящиъ от сервера  - slot_read
    * для закрытия интерфейса в случае ошибки  - slotCloseUi
    * для информировании об ошибках            - slot_errorOpen
*/


void infoBox(QString, QString);


void Network::slotNewConnected()
{

    //dataSender();
    MessageInfo("Клиент", "Я подключился к серверу!");
};

//считываю данные приходящие к хосту
void Network::slot_read()
{
    QDataStream in;
    in.setDevice(connectToServ);
    in.setVersion(QDataStream::Qt_4_0);

    in.startTransaction();

    in >> datagram;

    if (!in.commitTransaction())
          return;

    provider_net->check_NetCommand_From_Server(connectToServ, &datagram);
}


void Network::slotCloseUi()
{
    delete ui;
}

void Network::slot_errorOpen(QString name, QString text)
{
    infoBox(name, text);
}
