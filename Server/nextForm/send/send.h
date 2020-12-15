#pragma once

#include <QMainWindow>
#include <QListWidget>
namespace Ui {
    class Send;
}
//логика формы отправки файлов
class SendForm : public QMainWindow
{
    Q_OBJECT
public:
    SendForm(QWidget* parent = 0);

public slots:
    void on_send_file_btn_clicked();
    void new_client_set(QString, int);
private:
    QListWidget* lstWgt;
    Ui::Send* formSender_ui;
    void setRowList(QString name, int sock);
signals:
    void sendFileFromForm(QString);
};
