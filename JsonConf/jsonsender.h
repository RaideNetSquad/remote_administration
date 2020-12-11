/*
    * Этот метод расширяет родительский добавляя
    * способность взаимодействия с пользователем
*/
#pragma once
#include "network.h"

#include <QObject>


class JsonSender : public Network
{
    Q_OBJECT
public:
    JsonSender(QWidget *parent = 0);

private:
    void connections();
    void signal_slot_Connections();
    void on_send_clicked();
signals:
    void sendData_from_packJson(Packet pack);
    void errorOpen(QString, QString);

protected slots:
    void slot_read();
    void slot_NewConnected();
    //void sendData();
    //void slotCloseUi();
    //void slot_errorOpen(QString, QString);
    //void on_upload_clicked();

};

