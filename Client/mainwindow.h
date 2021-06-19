#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QHostAddress>
#include <QMessageBox>
#include <QMetaType>
#include <QString>
#include <QStandardPaths>
#include <QTcpSocket>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define BUF_SIZE 1024*4

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    qint32 m_blockSize;
    //интерфейс
    Ui::MainWindow *ui;
    //сокет соединения с сервером
    QTcpSocket* socket;

    QHostAddress addr;
    quintptr port;
    QString role;
private:
    void connection();
    //Job with path files
    QString split_Path_File(QString);
    //Senders
    void sendMessage(const QString&type,
                     const QString&value);
    void sendAttachment(QString path_C, QString path_S);
signals:
    void newError(const QString&);
    void newMessage(QString);
private slots:
    void on_pushButton_clicked();
    void displayMessage(const QString& str);
    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);
    void slot_Error(const QString&);
};
#endif // MAINWINDOW_H
