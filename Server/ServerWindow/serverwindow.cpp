#include "serverwindow.h"

ServerWindow::ServerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ServerWindow){
    //веду лог
    log.setFileName("logger.txt");

    ui->setupUi(this);
    //test
    ui->lineEdit->insert("127.0.0.1");
    ui->lineEdit_2->insert("8080");
    QString filePathRules = QFileDialog::getOpenFileName(this, ("Выберите файл с ролями (rules.json)"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), ("File (*.json)"));
    QString filePathTimeDo = QFileDialog::getOpenFileName(0, "Выберите json файл содержащий время исполнения инструкций и ссылку на них (time_do.json)", "", "*.json");
    //вся логика взаимодействия с клиентами
    serverLogic = new ServerObjectLogic(filePathRules, filePathTimeDo);
    connect(this, &ServerWindow::newMessage,
            this, &ServerWindow::slot_DisplayMessage);
    connect(serverLogic, &ServerObjectLogic::newError,
            this, &ServerWindow::slot_ErrorServer);
    connect(serverLogic, &QTcpServer::newConnection, this, &ServerWindow::newConnection);
    connect(serverLogic, &ServerObjectLogic::newMessage,
            this, &ServerWindow::slot_DisplayMessage);
}

void ServerWindow::logger(const QString &message){
    QMutexLocker locker(&mutex);
    //веду лог в текстовый файл
    if(log.open(QIODevice::Append)){

        QTextStream loggerStream(&log);
        loggerStream.setCodec(QTextCodec::codecForName("UTF-8"));
        loggerStream << QString("%1: %2\n")
                                        .arg(QDateTime::currentDateTime().toString())
                                        .arg(message);
        log.close();
    }else{
        QMessageBox::critical(this,"Лог",QString("Не могу вести лог: %1.").arg(log.errorString()));
        exit(EXIT_FAILURE);
    }
}

ServerWindow::~ServerWindow(){
    delete serverLogic;
    delete ui;
}
