/*
    * Реализация клиентского объекта
    * on_pushButton_clicked() - получаю данные для подключения с формы
    * slotNewConnected() - слот срабатывающий при каждом новом подключении
    * slotRead() - слот для чтения данных приходящих с сервера
    * parserCommands() - парсит команды
    * CompleteCommands() - выполняет команды
*/
#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <QMessageBox>
#include <QHostInfo>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QFileDialog>
#include "Pack.h"
void ClientWindow::MessageInfo(QString name, QString info)
{
    QMessageBox* message = new QMessageBox();
    message->setText(name);
    message->setInformativeText(info);
    message->setIcon(QMessageBox::Information);
    message->setDefaultButton(QMessageBox::Ok);
    message->open();
}

ClientWindow::ClientWindow(QWidget *parent) : QWidget(parent)
    , ui(new Ui::ClientWindow)
    , connectToServ(new QTcpSocket(this))
    , pack(new Packet(QHostInfo::localHostName()))
{
    Connections();
    ui->setupUi(this);
}
//получаю хост и порт для подключения
void ClientWindow::on_pushButton_clicked()
{
    host = ui->host->text();
    port = ui->port->text().toInt();
    connectToServ->connectToHost(host, port);

}

//выполнение команд
void ClientWindow::parser_Commands(QString& command, QString& path,QVariant& value)
{
    qDebug() << "complete";
    if(command == "createFile")
    {
        create_file(path);
    }
    if(command == "writeToFile")
    {

        write_to_file(value, path);
    }
    /*
    if(command == "openFile")
    {
        qDebug() << "OPEN FILE" << value;
        QString val = value.toString();
        open_file(val);
    }
    if(command == "deleteFile")
    {
        QString val = value.toString();
        delete_file(val);
    }
    if(command == "copyFile")
    {
        QJsonObject obj = value.toJsonObject();
        QString val1 = obj.take("from").toString();
        QString val2 = obj.take("to").toString();
        copy_file(val1, val2);
    }

    if(command == "completeSoft")
    {
        QJsonObject obj = value.toJsonObject();
        QString val = obj.take("what").toString();
        complite_file(val);
    }*/
}


void ClientWindow::dataSender()
{
    QByteArray arr;
    QDataStream out(&arr, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    QDateTime time = QDateTime::currentDateTime();
    pack->setDateAndTime(time);
    qDebug() << pack->getDateAndTime() << pack->getNameCommand();

    out << *pack;

    connectToServ->write(arr);
    connectToServ->waitForBytesWritten();
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

