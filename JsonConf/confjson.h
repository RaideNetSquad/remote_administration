/*#ifndef CONFJSON_H
#define CONFJSON_H

#include <QWidget>
#include "network.h"
#include <QJsonDocument>
namespace Ui {
class ConfJson;
}

class ConfJson : public QWidget
{
    Q_OBJECT

public:
    explicit ConfJson(Packet pack,QWidget *parent = nullptr);
    ~ConfJson();

private slots:
    void on_upload_clicked();

    void on_send_clicked();

private:
    Packet pack;
    Ui::ConfJson *ui;
    void connections();
    void infoBox(QString textInfo, QString head);
signals:
    void sendData_from_packJson(Packet pack);
    void errorOpen(QString, QString);
};

#endif // CONFJSON_H
*/
