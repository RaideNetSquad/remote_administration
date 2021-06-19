#include "serverwindow.h"

void ServerWindow::on_pushButton_clicked(){

    addr.setAddress(ui->lineEdit->text());
    port = ui->lineEdit_2->text().toUInt();

    if(serverLogic->listen(addr, port)){

       ui->statusBar->showMessage("Сервер работает...");
       emit newMessage("Сервер ждет подключений");
    }
    else{
        emit newMessage(QString("Не удалось запустить сервер: %1.").arg(serverLogic->errorString()));
        ui->statusBar->showMessage("Сервер не работает...");
    }
    ui->pushButton->setDisabled(true);
};
void ServerWindow::newConnection(){
    emit newMessage("Новое подключение");
}
void ServerWindow::slot_DisplayMessage(const QString& message){
    //отобразить сообщение в браузере и записать в лог
    ui->textBrowser_receivedMessages->append(message);
    //запись в файл
    logger(message);
};

void ServerWindow::slot_ErrorServer(const QString &textError){
    QMessageBox::critical(this,"Ошибка", textError);
    logger(textError);
    ui->pushButton->setDisabled(false);
}
