#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rule_map.h"

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
    void newConnection();
    void appendToSocketList(QTcpSocket* socket);

    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);

    void displayMessage(const QString& str);

private:
    Ui::MainWindow *ui;

    Rule_Map *rule_map;

    QTcpServer* m_server;
    QSet<QTcpSocket*> connection_set;

    void rules_Worker();
    void disconnect(QTcpSocket *socket, const QString &str);
};

#endif // MAINWINDOW_H
