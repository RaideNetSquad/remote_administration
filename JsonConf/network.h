#pragma once
#include "form_json_send.h"

#include <QWidget>
#include <QTcpSocket>
#include <QString>
#include <QObject>
#include <QDateTime>
#include "Provider_Network_Data.h"
QT_BEGIN_NAMESPACE
namespace Ui { class network; }
QT_END_NAMESPACE


class Network : public QWidget
{
    Q_OBJECT
public:
    Network(QWidget *parent = 0);
protected:
    Ui::network *ui;
    QTcpSocket* connectToServ;
    QString host;
    quint16 port;

    Provider_Network_Data *provider_net;
    Datagram datagram;
protected:
    bool connecting();
    void MessageInfo(QString name, QString info);
    //void dataSender();
    //void connections();
    //bool connecting();
//signals:
    //void closeUi();
private slots:
    void slotNewConnected();
    void slotCloseUi();
    void slot_errorOpen(QString, QString);
    //void slot_NewConnected();
    void signal_slot_Connections();
    void on_send_clicked();
    void slot_read();
};
