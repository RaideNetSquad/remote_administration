/*
    * Реализация функционала объекта для отправки файла  JSON
    * on_upload_clicked() - функция получает имя файла и путь к нему
    * on_send_clicked()  - функция отправляет файл на сервер
*/

#include "form_json_send.h"
#include "ui_confjson.h"
#include "network.h"
#include <QFile>
#include <QFileDialog>
#include <QHostInfo>
#include <QMessageBox>

void infoBox (QString, QString);

FormJsonSend::FormJsonSend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormJsonSend),
    provider_net(new Provider_Network_Data())
{
    ui->setupUi(this);
}

FormJsonSend::~FormJsonSend()
{
    delete ui;
}

