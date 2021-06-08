#include "form_json_send.h"
#include "ui_confjson.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
/*
    * Все слоты объекта FormJsonSend
    * для загрузки ДЖСОН файла  - on_upload_clicked
    * для отправки ДЖСОН файла на сервер  - on_send_clicked
*/


void infoBox(QString, QString);


void FormJsonSend::on_upload_clicked()
{
    fileJSON = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.json");
    ui->send->setEnabled(true);
    //ui->whoGet->textActivated();
}
//вызываю при клике на кнопку загрузки файла
void FormJsonSend::on_send_clicked()
{
    QFile json(fileJSON);

    if(json.open(QIODevice::ReadOnly)){
        //QDateTime dateAndTime = QDateTime::currentDateTime();
        QString nameCommand = "json";
        QString textCommand = "send JSON";
        QString readJSON = json.readAll();

        //pack->setDateAndTime(dateAndTime);
        //pack->setNameCommand(nameCommand);
        //pack->setTextCommand(textCommand);
        //pack->setJsonCommand(readJSON);

        //emit sendData_from_packJson(pack);
    }else{
        emit errorOpen("Error", "Не могу открыть файл");
    }
}


