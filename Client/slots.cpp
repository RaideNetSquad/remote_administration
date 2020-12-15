#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <QHostInfo>
#include <QDateTime>
//СЛОТЫ

void ClientWindow::slotNewConnected()
{
    QString nameCommand = "Подключение";
    QString textCommand = "Kлиента";
    QDateTime cur = QDateTime::currentDateTime();

    pack->setNameCommand(nameCommand);
    pack->setTextCommand(textCommand);

    dataSender();
    MessageInfo("Клиент", "Я подключился к серверу!");
}

void ClientWindow::slotRead()
{
    QDataStream in;
    in.setDevice(connectToServ);
    in.setVersion(QDataStream::Qt_4_0);
    Packet pack;
    in.startTransaction();

    in >> pack;

    if (!in.commitTransaction())
          return;
    QVariant command =pack.getCommand();
    QString name = pack.getNameCommand();
    QString text = pack.getTextCommand();
    qDebug() << pack.getBytes();
    //parser_Commands(name,text,command);



}

void ClientWindow::slot_send_command(QString nameCommand, QString textCommand){
    pack->setNameCommand(nameCommand);
    pack->setTextCommand(textCommand);
    this->dataSender();
}

