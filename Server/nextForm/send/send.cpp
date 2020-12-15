#include "send.h"
#include "ui_sendFile.h"
#include <QFileDialog>
#include <QDebug>
#include <QListWidget>

SendForm::SendForm(QWidget* parent) :
    QMainWindow(parent),
    formSender_ui(new Ui::Send())
{
    formSender_ui->setupUi(this);
    lstWgt = formSender_ui->listWidget;
}


void SendForm::setRowList(QString name, int sock)
{
    qDebug() << "setRowList" << name;
    QLabel* wgt = new QLabel(name);
    qDebug() << "setRowList 1";
    QListWidgetItem* item = new QListWidgetItem( lstWgt );
    qDebug() << "setRowList 2";
    item->setSizeHint( wgt->sizeHint() );
    qDebug() << "setRowList 3";
    lstWgt->setItemWidget( item, wgt );
    qDebug() << "end setRowList";
}
void SendForm::new_client_set(QString name, int sock)
{
    UserName user = {name,sock};
    users.append(user);

    setRowList(name, sock);
}
