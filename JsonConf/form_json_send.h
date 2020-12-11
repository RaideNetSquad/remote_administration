#ifndef CONFJSON_H
#define CONFJSON_H

#include "network.h"
#include "Pack.h"

#include <QWidget>
#include <QJsonDocument>

namespace Ui {
class FormJsonSend;
}


class FormJsonSend : public QWidget
{
    Q_OBJECT

public:
    FormJsonSend(QWidget *parent = 0);
    ~FormJsonSend();

public slots:
    void on_upload_clicked();

    void on_send_clicked();
private:
    Packet *pack;
    QString fileJSON;
    Ui::FormJsonSend *ui;
    void infoBox(QString textInfo, QString head);
    void signal_slot_Connections();

signals:
    void sendData_from_packJson(Packet *pack);
    void errorOpen(QString, QString);
};

#endif // CONFJSON_H
