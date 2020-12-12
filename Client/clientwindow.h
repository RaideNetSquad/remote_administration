#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QTcpSocket>
#include <QDateTime>
#include "Pack.h"
#include <QMutex>
QT_BEGIN_NAMESPACE
namespace Ui { class ClientWindow; }
QT_END_NAMESPACE

class ClientWindow : public QWidget
{
    Q_OBJECT
public:
    ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();
public:
    QMutex mutex;
    Packet *pack;

private:
    QTcpSocket* connectToServ;
    void dataSender();
    void Connections();
    void MessageInfo(QString name, QString info);
private:
    void parser_Commands(QString &command);
    void complete_Commands(QString &command, QVariant value);
    void create_file(QString &path);
    void open_file(QString &path);
    void delete_file(QString &path);
    void write_to_file(QString &text, QString &path);
    void copy_file(QString&, QString&);
    void complite_file(QString&);
private slots:
    void on_pushButton_clicked();

private:
    QString host;
    quint16 port;
    Ui::ClientWindow *ui;
private slots:
    void slotNewConnected();
    void slotRead();
signals:
    void complete_signal(QString, QString);
    /*void write_to_file_signal(QString, QString);
    void open_file_signal(QString, QString);
    void delete_file_signal(QString,QString);
    void copy_file_signal(QString, QString);*/
private slots:
    void slot_send_command(QString, QString);
};
#endif // CLIENTWINDOW_H
