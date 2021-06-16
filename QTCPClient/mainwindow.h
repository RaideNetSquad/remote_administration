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
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void newMessage(QString);
private slots:
    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);

    void displayMessage(const QString& str);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QTcpSocket* socket;

    QHostAddress addr;
    quintptr port;
    QString rule;
private:
    void connection();
    //Senders
    void send_rule(const QString& str);
    void sendAttachment(QString from, QString to);
    void sendMessageStatusCommand(QString mess);
    //Job with path files
    QString split_Path_File(QString rule_File_Path);
};

#endif // MAINWINDOW_H
