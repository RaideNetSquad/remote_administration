#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_server = new QTcpServer();

    rule_map = new Rule_Map();

    //получать роли из файла
    rules_Worker();


    if(m_server->listen(QHostAddress::Any, 8080))
    {
       connect(this, &MainWindow::newMessage, this, &MainWindow::displayMessage);
       connect(m_server, &QTcpServer::newConnection, this, &MainWindow::newConnection);
       ui->statusBar->showMessage("Сервер работает...");
    }
    else
    {
        QMessageBox::critical(this,"QTCPServer",QString("Не удалось запустить сервер: %1.").arg(m_server->errorString()));
        exit(EXIT_FAILURE);
    }
}

MainWindow::~MainWindow()
{
    foreach (QTcpSocket* socket, connection_set)
    {
        socket->close();
        socket->deleteLater();
    }

    m_server->close();
    m_server->deleteLater();

    delete ui;
}

void MainWindow::newConnection()
{
    while (m_server->hasPendingConnections())
        appendToSocketList(m_server->nextPendingConnection());
}

void MainWindow::appendToSocketList(QTcpSocket* socket)
{
    connection_set.insert(socket);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &MainWindow::displayError);

    displayMessage(QString("Инфо :: Клиент с сокетом:%1 подключился").arg(socket->socketDescriptor()));
}

void MainWindow::readSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    qintptr sock_desc = socket->socketDescriptor();

    QByteArray buffer;

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> buffer;

    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1 клиент :: Ожидание получения дополнительных данных...").arg(socket->socketDescriptor());
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

        QString filePath = QFileDialog::getSaveFileName(this, tr("Сохранить фалй"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/"+fileName, QString("Файл (*.%1)").arg(ext));

        QFile file(filePath);
        if(file.open(QIODevice::WriteOnly)){
            file.write(buffer);
            QString message = QString("Инфо :: Данные от sd:%1 успешно сохраненны по пути %2").arg(socket->socketDescriptor()).arg(QString(filePath));
            emit newMessage(message);
        }else{
            QMessageBox::critical(this,"Отправитель", "Ошибка передачи данных.");
        }
    }else if(fileType == "rule")
    {
        QString rule = QString("%1").arg(QString::fromStdString(buffer.toStdString()));
        int valid_Id_Rule = rule_map->get_Rule_Id(rule, sock_desc);
        if(valid_Id_Rule != -1){
            //если роль найдена и она свободна
            if(valid_Id_Rule != 1){
                emit newMessage(QString("Сокет %1 имеет роль <%2> ").arg(sock_desc).arg(QString::fromStdString(buffer.toStdString())));
            }
        }else{
            //если роль не найденна или она занята
            disconnect(socket, QString("Роль <(%1)> не найденна или занята для клиента (%2)").arg(QString::fromStdString(buffer.toStdString())).arg(sock_desc));
        }
    }
}

void MainWindow::disconnect(QTcpSocket *socket, const QString &str)
{
    //удаление клиента из роли
    rule_map->delete_Client_Id(socket->socketDescriptor());

    //разрыв соединения с клиентом
    QSet<QTcpSocket*>::iterator it = connection_set.find(socket);
    if (it != connection_set.end()){
        displayMessage(QString(str).arg(socket->socketDescriptor()));
        connection_set.remove(*it);

    }
    socket->deleteLater();
}
void MainWindow::discardSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    disconnect(socket, "Инфо :: Клиент только что вышел из комнаты!");
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
        break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, "Отправитель", "Клиент не был найден. Пожалуйста проверьте адрес устроства или порт.");
        break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, "Отправитель", "Соединение было отклонено узлом. Убедитесь, что QTcpServer запущен, и проверьте правильность имени хоста и настроек порта.");
        break;
        default:
            QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
            QMessageBox::information(this, "Отправитель", QString("Произошла следующая ошибка: %1.").arg(socket->errorString()));
        break;
    }
}

void MainWindow::rules_Worker()
{
    QFile rules_json(QDir::currentPath() + "/rules.json");

    if(rules_json.open(QIODevice::ReadOnly)){
        // Считываем весь файл
        QByteArray readJSON = rules_json.readAll();
        // Создаём QJsonDocument
        QJsonDocument jsonDocument(QJsonDocument::fromJson(readJSON));
        //хранилище ролей
        rule_map->set_Map(jsonDocument);

    }else{
        qDebug() << "Err";
        QMessageBox::critical(this,"Ошибка", "Невозможно открыть файл");
        exit(EXIT_FAILURE);
    }
}

void MainWindow::displayMessage(const QString& str)
{
    ui->textBrowser_receivedMessages->append(str);
}

