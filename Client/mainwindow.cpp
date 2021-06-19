#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->insert("127.0.0.1");
    ui->lineEdit_2->insert("8080");
    ui->lineEdit_3->insert("Наблюдатель 1");

}

//[1]
void MainWindow::connection()
{
    //установка соединения с сервером
    socket = new QTcpSocket(this);

    socket->connectToHost(this->addr,this->port);
    connect(this, &MainWindow::newError, this, &MainWindow::slot_Error, Qt::QueuedConnection);
    connect(this, &MainWindow::newMessage, this, &MainWindow::displayMessage);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readSocket, Qt::QueuedConnection);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::discardSocket, Qt::QueuedConnection);
    connect(socket, &QAbstractSocket::errorOccurred, this, &MainWindow::displayError);

    if(socket->waitForConnected()){
        emit newMessage(QString("Подключился к серверу."));
        ui->statusBar->showMessage("Подключился к серверу.");
        ui->pushButton->setDisabled(true);
    }
    else{
        QMessageBox::critical(this,"Клиент", QString("Произошла следующая ошибка: %1.").arg(socket->errorString()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
