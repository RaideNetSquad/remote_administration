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
//парсинг команд
void ClientWindow::parser_Commands(QString &command)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(command.toUtf8());
    if(jsonDoc.isArray())
    {
        QJsonArray jsonArr = jsonDoc.array();
        QJsonObject jsonObj = jsonArr[0].toObject();
        QJsonArray arrCommands = jsonObj.take("commands").toArray();
        for(int i = 0; i < arrCommands.size(); ++i)
        {
            QJsonObject commandObj = arrCommands[i].toObject();
            QString strCommand;
            QVariant nameCommand;
            if(commandObj.contains("createfile")){
                strCommand = "createFile";
                nameCommand = commandObj.take("createfile").toString();
            };
            if(commandObj.contains("write")){
                strCommand = "writeToFile";
                nameCommand = commandObj.take("write").toObject();
            };
            if(commandObj.contains("open")){
                strCommand = "openFile";
                nameCommand = commandObj.take("open").toString();
            };
            if(commandObj.contains("delete")){
                strCommand = "deleteFile";
                nameCommand = commandObj.take("delete").toString();
            };
            if(commandObj.contains("copyfile")){
                strCommand = "copyFile";
                nameCommand = commandObj.take("copyfile").toObject();
            };
            complete_Commands(strCommand, nameCommand);
        }
    }
}
//выполнение команд
void ClientWindow::complete_Commands(QString &command, QVariant value)
{
    qDebug() << "complete";
    if(command == "createFile")
    {
        QString val = value.toString();
        create_file(val);
    }
    if(command == "writeToFile")
    {
        QJsonObject obj = value.toJsonObject();

        QString text = obj.take("text").toString();
        QString path = obj.take("where").toString();

        write_to_file(text, path);
    }
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
}


void ClientWindow::dataSender()
{
    QByteArray arr;
    QDataStream out(&arr, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    QDateTime time = QDateTime::currentDateTime();
    pack->setDateAndTime(time);
    qDebug() << pack->getDateAndTime() << pack->getHostName();

    out << *pack;

    connectToServ->write(arr);
    connectToServ->waitForBytesWritten();
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

