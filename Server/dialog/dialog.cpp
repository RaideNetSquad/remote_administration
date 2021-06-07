/*
    * Виджеты сервера
    * Созднание объекта серверной логики
*/
#include "dialog.h"
#include "serverLogic/server.h"
#include "ui_dialog.h"
#include <QMessageBox>

//обработчик ошибок при получении хоста или порта
void Dialog::checkErrorGettingHost()
{
    if(!getHost()){
        QMessageBox::critical(0, tr("Err Server"),
                                      tr("Unable to start the server: %1.")
                                      .arg(serv->errorString()));
        emit closeUi();
        return;
    }
}

Dialog::Dialog(QWidget* parent)
                : QMainWindow(parent),
                  ui(new Ui::Dialog)
{

    ui->setupUi(this);
    //серверная логика в этом объекте
    serv = new Server(ui,this);

    checkErrorGettingHost();

    ui->portValue->setText(QString::number(port));
    ui->hostValue->setText(host.toString());
    connect(this, &Dialog::closeUi,
            this, &Dialog::closeApp);
}

void Dialog::closeApp()
{
    this->~Dialog();
}

Dialog::~Dialog()
{
    delete ui;
}
