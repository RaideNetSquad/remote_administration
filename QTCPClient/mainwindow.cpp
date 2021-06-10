#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    socket(new QTcpSocket(this))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    if(socket->isOpen())
        socket->close();
    delete ui;
}

void MainWindow::readSocket()
{
    QByteArray buffer;

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> buffer;

    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1 клиент :: Ожидание получения данных..").arg(socket->socketDescriptor());
        emit newMessage(message);
        return;
    }

    QString header = buffer.mid(0,128);
    QString fileType = header.split(",")[0].split(":")[1];

    buffer = buffer.mid(128);

    if(fileType=="attachment"){
        QString fileName = header.split(",")[1].split(":")[1];
        QString ext = fileName.split(".")[1];
        QString size = header.split(",")[2].split(":")[1].split(";")[0];

        QString filePath = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/"+fileName, QString("File (*.%1)").arg(ext));

        QFile file(filePath);
        if(file.open(QIODevice::WriteOnly)){
            file.write(buffer);
            QString message = QString("Инфо :: Вложения от sd:%1 успешно сохраненны на диске от %2").arg(socket->socketDescriptor()).arg(QString(filePath));
            emit newMessage(message);
        }else
            QMessageBox::critical(this,"Отправитель", "Неизвестная ошибка записи вложений, поговорите с разработчиком.");
   }
}

void MainWindow::discardSocket()
{

    socket->deleteLater();
    socket=nullptr;

    ui->pushButton->setDisabled(false);
    ui->statusBar->showMessage("Разрыв соединения!");
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
        break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, "Отправитель", "Не найден хост. Проверьте правильность имени хоста или порта.");
        break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, "Отправитель", "Удаленное соединение разорванно. Проверьте правильность имени хоста или порта. ");
        break;
        default:
            QMessageBox::information(this, "Отправитель", QString("Произошла следующая ошибка: %1.").arg(socket->errorString()));
        break;
    }
}

/*void MainWindow::on_pushButton_sendAttachment_clicked()
{
    if(socket)
    {
        if(socket->isOpen())
        {
            QString filePath = QFileDialog::getOpenFileName(this, ("Выберите файл"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), ("Файл (*.*)"));

            if(filePath.isEmpty()){
                QMessageBox::critical(this,"Отправитель","Вы не выбрали файл!");
                return;
            }

            QFile m_file(filePath);
            if(m_file.open(QIODevice::ReadOnly)){

                QFileInfo fileInfo(m_file.fileName());
                QString fileName(fileInfo.fileName());

                QDataStream socketStream(socket);
                socketStream.setVersion(QDataStream::Qt_5_15);

                QByteArray header;
                header.prepend(QString("fileType:attachment,fileName:%1,fileSize:%2;").arg(fileName).arg(m_file.size()).toUtf8());
                header.resize(128);

                QByteArray byteArray = m_file.readAll();
                byteArray.prepend(header);

                socketStream.setVersion(QDataStream::Qt_5_15);
                socketStream << byteArray;
            }else
                QMessageBox::critical(this,"Отправитель","Ошибка отправки файла, повторите попытку");
        }
        else
            QMessageBox::critical(this,"Отправитель","Сокет, похоже, не открыт");
    }
    else
        QMessageBox::critical(this,"Отправитель","Не подключенно");
}*/

void MainWindow::displayMessage(const QString& str)
{
    //ui->textBrowser_receivedMessages->append(str);
}

void MainWindow::on_pushButton_clicked()
{
    this->addr = ui->lineEdit->text();
    this->port = ui->lineEdit_2->text().toUInt();
    this->rule = ui->lineEdit_3->text();

    connection();
}

void MainWindow::connection()
{
    if(!socket)
        socket = new QTcpSocket(this);

    connect(this, &MainWindow::newMessage, this, &MainWindow::displayMessage);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &MainWindow::displayError);

    socket->connectToHost(this->addr,this->port);

    if(socket->waitForConnected()){
        ui->statusBar->showMessage("Подключился к серверу.");
        send_rule();
        ui->pushButton->setDisabled(true);
    }
    else{
        QMessageBox::critical(this,"Клиент", QString("Произошла следующая ошибка: %1.").arg(socket->errorString()));
        exit(EXIT_FAILURE);
    }
}

void MainWindow::send_rule()
{
    if(socket)
        {
            if(socket->isOpen())
            {

                QDataStream socketStream(socket);
                socketStream.setVersion(QDataStream::Qt_5_15);

                QByteArray header;
                header.prepend(QString("fileType:rule,fileName:null,fileSize:%1;").arg(rule.size()).toUtf8());
                header.resize(128);

                QByteArray byteArray = rule.toUtf8();
                byteArray.prepend(header);

                socketStream << byteArray;

            }
            else
                QMessageBox::critical(this,"Клиент","Сокет закрыт");
        }
        else
            QMessageBox::critical(this,"Клиент","Отсутствует подключение");
}
