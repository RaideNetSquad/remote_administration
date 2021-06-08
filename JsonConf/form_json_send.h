#ifndef CONFJSON_H
#define CONFJSON_H

#include "network.h"
#include "Provider_Network_Data.h"

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
    Provider_Network_Data *provider_net;
    QString fileJSON;
    Ui::FormJsonSend *ui;
    void infoBox(QString textInfo, QString head);
    void signal_slot_Connections();

signals:
    void sendData_from_packJson(Provider_Network_Data *pack);
    void errorOpen(QString, QString);
};

#endif // CONFJSON_H
