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

    ui->setupUi(this);
    serv = new Server(ui,this);

    checkErrorGettingHost();

    ui->portValue->setText(QString::number(port));
    ui->hostValue->setText(host.toString());
    qDebug() << "dialog start";
    connect(serv, SIGNAL(setRowTable(QString, QString)),
            this, SLOT(slot_setRowTable(QString, QString)));
    //отправка файлов
    connect(send, SIGNAL(sendFileFromForm(QString)),
            serv, SLOT(slot_send_file(QString)));

    //занесение имени клиента в список
    connect(serv, SIGNAL(new_client_to_sendForm(QString, int)),
            send, SLOT(new_client_set(QString, int)));

    connect(this, &Dialog::closeUi,
            this, &Dialog::closeApp);
    qDebug() << "dialog end";
}

void Dialog::closeApp()
{
    this->~Dialog();
}
Dialog::~Dialog()
{
    delete ui;
}

