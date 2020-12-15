/*
    * Виджеты сервера
    * Созднание объекта серверной логики
*/
#include "dialog.h"


#include "serverObject/server.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget* parent)
                : QMainWindow(parent),
                  ui(new Ui::Dialog),
                  status(new StatusForm),
                  send(new SendForm)
{
    //загрузка интерфейса
    ui->setupUi(this);
    //объект серверной логики
    serv = new Server(ui,this);
    //проверка получения адреса хоста (ип порт)
    checkErrorGettingHost();
    //установка в виджетах ип и порт хоста
    ui->portValue->setText(QString::number(port));
    ui->hostValue->setText(host.toString());

    //сигнало-слотовые соединения объекта диалога
    connects_dialog();
}

void Dialog::closeApp()
{
    this->~Dialog();
}
Dialog::~Dialog()
{
    delete ui;
}

