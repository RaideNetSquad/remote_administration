#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    socket(new QTcpSocket(this))
{
    ui->setupUi(this);
    ui->lineEdit->insert("127.0.0.1");
    ui->lineEdit_2->insert("8080");
    ui->lineEdit_3->insert("Наблюдатель 1");
}

MainWindow::~MainWindow()
{
    if(socket->isOpen())
        socket->close();
    delete ui;
}

QString MainWindow::split_Path_File(QString rule_File_Path)
{
    if(rule_File_Path.split("/")[0] == ".")
    {
        rule_File_Path = QString("%1/%2").arg(QDir::currentPath()).arg(rule_File_Path.split("./")[1]);
    }
    return rule_File_Path;
}

void MainWindow::connection()
{
    qDebug() << "connection [2]";
    //if(!socket)
    socket = new QTcpSocket(this);

    connect(this, &MainWindow::newMessage, this, &MainWindow::displayMessage);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &MainWindow::displayError);

    socket->connectToHost(this->addr,this->port);

    if(socket->waitForConnected()){
        ui->statusBar->showMessage("Подключился к серверу.");
        emit newMessage("Подключился к серверу.");
        ui->pushButton->setDisabled(true);
    }
    else{
        QMessageBox::critical(this,"Клиент", QString("Произошла следующая ошибка: %1.").arg(socket->errorString()));
        exit(EXIT_FAILURE);
    }
}


void MainWindow::discardSocket()
{

    socket->deleteLater();
    socket=nullptr;

    ui->pushButton->setDisabled(false);
    ui->statusBar->showMessage("Разрыв соединения!");
}

void MainWindow::displayMessage(const QString& str)
{
    ui->textBrowser_receivedMessages->append(str);
}
