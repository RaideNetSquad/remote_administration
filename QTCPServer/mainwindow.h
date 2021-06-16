#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rule_map.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QMetaType>
#include <QSet>
#include <QStandardPaths>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void newMessage(QString);
private slots:
    void slot_newConnection();
    void appendToSocketList(QTcpSocket* socket);
    void displayMessage(const QString& str);
    void slot_readSocket();
    void slot_discardSocket();
    void slot_displayError(QAbstractSocket::SocketError socketError);


    void slot_Timer_Update();

    void on_pushButton_clicked();

private:

    QHostAddress addr;
    quintptr port;

    QTimer *timer;

    QString start_Commands;
    QString path_Instructions_Roles;
    QString current_DateTime;

    Ui::MainWindow *ui;

    Rule_Map *rule_map;

    QTcpServer* m_server;
    QSet<QTcpSocket*> connection_set;

    //Getters
    QString get_FileInstructions_By_Descr(int sock_Descr);
    QJsonDocument get_JsonDocument(QString f);
    //Setters
    void set_Roles_To_Map();
    void set_Time_Complite_Instructions();
    //Senders
    void sendAttachment(QTcpSocket* socket, const QString& path_S, const QString& path_C);
    void send_Command(QTcpSocket* socket, const QString& command, const QString& text);
    //Parsers
    void parser_TimeDo(QString path_f);
    void parser_File_With_Roles_Instructions();
    void parser_File_With_Instructions_Role(int rul_socketId_Client, QString rul_Value, QString path_File);

    //Job with commands
    void commands_Connector(const QString& key_Current_Comand,
                            const QJsonObject &current_Command_Object,
                            const int& rul_socketId_Client);
    void commands_Connector(const QString& key_Current_Comand,
                            const QString &current_Command_Str,
                            const int& rul_socketId_Client);

    //Job with path files
    QString split_Path_File(QString rule_File_Path);
    //Job with socket
    void disconnect(QTcpSocket *socket, const QString &str);
    void commands_Complite();
};

#endif // MAINWINDOW_H
