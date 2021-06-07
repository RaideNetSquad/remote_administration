/*
    * реализация объекта для подключения и взаимодействия с сервером
    * sendData() - функция отправки данных
    * slotNewConnected() - слот срабатывающий при каждом новом подключении
    * read() - слот для чтения данных с сервера
    * connecting() - функция для подключения к серверу
    * on_send_clicked() - функция вызывается при отправки данных с формы
    * slotCloseUi() - слот для закрытия формы
*/
#include "network.h"
#include "ui_jsonsender.h"
#include "form_json_send.h"

#include <QObject>
#include <QDateTime>
#include <QHostInfo>
#include <QMessageBox>

void infoBox(QString, QString);

Network::Network(QWidget *parent) : QWidget(parent),
      connectToServ(new QTcpSocket(this)),
      pack(new Packet(QHostInfo::localHostName())),
      ui(new Ui::network)
{
    ui->setupUi(this);
};

bool Network::connecting()
{
    QString host = this->host;
    quint16 port = this->port;

    connectToServ->connectToHost(host, port);
    signal_slot_Connections();
    if(!connectToServ->waitForConnected(3000))
    {

        return false;
    }
    return true;
}

/*void Network::slot_NewConnected()
{
    infoBox("Подключение", "Есть подключение к серверу!");
    pack.dateAndTime = QDateTime::currentDateTime();
    pack.nameCommand = "Подключился";
    pack.textCommand = "Запрос на подключение от хоста успешно выполнился";
    sendData();
}*/
void Network::on_send_clicked()
{
    port = ui->port->text().toInt();
    host = ui->host->text();

    if(connecting()){

        FormJsonSend *jsonForm = new FormJsonSend();
        jsonForm->show();
        connect(jsonForm, SIGNAL(sendData_from_packJson(Packet*)),
                this, SLOT(sendData(Packet*)));
        connect(jsonForm, SIGNAL(errorOpen(QString, QString)),
                this, SLOT(slot_errorOpen(QString, QString)));
        this->close();
    }else{
        infoBox("Error", "Немогу подключиться к серверу, обратитесь в службу поддержки!\nИли измените адрес хоста и/или порт");
    };

}

