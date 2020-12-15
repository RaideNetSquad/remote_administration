#include "dialog.h"


//посмотреть статус (форма показать)
void Dialog::on_pushButton_2_clicked()
{
    status->show();

}
//отправить файлы (форма показать)
void Dialog::on_pushButton_clicked()
{
    send->show();
}

void Dialog::slot_setRowTable(QString nameHost, QString textCommand)
{
    qDebug() << "set row";
    status->setRowTable(nameHost, textCommand);
}
