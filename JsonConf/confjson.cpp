/*
    * Реализация функционала объекта для отправки файла  JSON
    * on_upload_clicked() - функция получает имя файла и путь к нему
    * on_send_clicked()  - функция отправляет файл на сервер
*/

/*#include "confjson.h"
#include "ui_confjson.h"
#include "network.h"
#include <QFile>
#include <QFileDialog>
#include <QHostInfo>
#include <QMessageBox>

void infoBox (QString, QString);

ConfJson::ConfJson(Packet *pack,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfJson)
{
    ui->setupUi(this);
}

ConfJson::~ConfJson()
{
    delete ui;
}

void ConfJson::on_upload_clicked()
{
    fileJSON = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.json");
    ui->send->setEnabled(true);
    //ui->whoGet->textActivated();
}
//вызываю при клике на кнопку загрузки файла
void ConfJson::on_send_clicked()
{
    QFile json(fileJSON);

    if(json.open(QIODevice::ReadOnly)){
        QString nameCommand = "json";
        QString textCommand = "отправляю JSON";
        QString readJSON = json.readAll();
        QDateTime dateAndTime = QDateTime::currentDateTime();
        pack.dateAndTime = dateAndTime;
        pack.nameCommand = nameCommand;
        pack.textCommand = textCommand;
        pack.jsonCommand = readJSON;
        emit sendData_from_packJson(pack);
    }else{
        emit errorOpen("Error", "Не могу открыть файл");
    }
}
*/
