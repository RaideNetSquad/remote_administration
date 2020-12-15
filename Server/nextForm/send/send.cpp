#include "send.h"
#include "ui_sendFile.h"
#include <QFileDialog>
#include <QDebug>
#include <QListWidget>

SendForm::SendForm(QWidget* parent) :
    QMainWindow(parent),
    formSender_ui(new Ui::Send())
{
    qDebug() << "SendForm";
    formSender_ui->setupUi(this);
    lstWgt = formSender_ui->listWidget;
    connect(formSender_ui->send_file_btn, &QPushButton::clicked,
            this, &SendForm::on_send_file_btn_clicked);
    qDebug() << "end SendForm";
}
//отправить файлы
void SendForm::on_send_file_btn_clicked()
{
    qDebug() << "push";
    QStringList tt = QFileDialog::getOpenFileNames(0, "Open Dialog", "");
    for(int i = 0; i < tt.size(); ++i)
    {
        emit sendFileFromForm(tt[i]);
    }
}

void SendForm::setRowList(QString name, int sock)
{
    qDebug() << "setRowList";
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
    qDebug() << "new_client_set";
    setRowList(name, sock);
}
