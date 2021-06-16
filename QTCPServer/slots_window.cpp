#include "mainwindow.h"
#include <QThread>
void MainWindow::slot_newConnection()
{
    while (m_server->hasPendingConnections())
        appendToSocketList(m_server->nextPendingConnection());

}

void MainWindow::slot_Timer_Update()
{

    current_DateTime = QDateTime::currentDateTime().toString();
    //совпадение есть (start_Commands == current_DateTime);
    //qDebug() << path_Instructions_Rules;
    if(start_Commands == current_DateTime)
    {
        emit newMessage(QString("Пришло время выполнять команды <%1>")
                        .arg(path_Instructions_Roles));
        //will be instructions parse and complete
    }
    //Выполняться будет каждую секунду перенеси в тело условного оператора сверху
    //int res_Role_Id_Getting;
    //QString path_File_Instructions_Rule;
    if(connection_set.size() > 0)
    {
            timer->stop();
            emit newMessage(QString("Читаю команды из файла <%1>").arg(path_Instructions_Roles));
            //роли
            parser_File_With_Roles_Instructions();
            //qDebug() << rFO;
            /*
            for(auto it = rFO.begin(); it != rFO.end(); ++it)
            {
                rul = it.key();
                res_Rule_Id_Getting = rule_map->get_Id_Rule(rul);

                if(res_Rule_Id_Getting != 0)
                {

                    //если роль (клиент) в сети
                    //проверить статус выполнения инструкций
                    //если состояние 0 - он не выполнил команду (1 - выполнил) - см instructionsН.json "STATE"
                    path_File_Instructions_Rule = it.value().toString();

                    if(path_File_Instructions_Rule.split("/")[0] == ".")
                    {
                        path_File_Instructions_Rule = QString("%1/%2").arg(QDir::currentPath()).arg(path_File_Instructions_Rule.split("./")[1]);
                    }
                    QFile file_Ir(path_File_Instructions_Rule);
                    if(file_Ir.open(QIODevice::ReadOnly))
                    {
                        emit newMessage(QString("Читаю файл <%1> роли <%2> клиента <%3>")
                                        .arg(rul).arg(res_Rule_Id_Getting).arg(path_File_Instructions_Rule));
                        QJsonDocument inst = get_JsonDocument(file_Ir);
                        QJsonObject obj = inst.object();

                        if(obj.find("STATE").value().toString() != "ok")
                        {
                            qDebug() << "State no ok";
                            QJsonObject obj_val;

                            QString PATH_SERV;
                            QString PATH_CLIENT;

                            QString COPY_FROM;
                            QString COPY_TO;

                            QString REMOVE_FILE;
                            QString COMPLITE_SOFT;

                            QString commands;
                            for(auto iter = obj.begin(); iter != obj.end(); ++iter)
                            {
                                if(iter.key() == "GET_FILE"){

                                    obj_val = iter.value().toObject();

                                    PATH_SERV = obj_val.take("PATH_SERV").toString();
                                    PATH_CLIENT = obj_val.take("PATH_CLIENT").toString();

                                    connector_Command(res_Rule_Id_Getting, "GET_FILE", PATH_SERV, PATH_CLIENT);

                                }else if(iter.key() == "SEND_FILE"){

                                    obj_val = iter.value().toObject();

                                    PATH_CLIENT = obj_val.take("PATH_CLIENT").toString();
                                    PATH_SERV = obj_val.take("PATH_SERV").toString();

                                    connector_Command(res_Rule_Id_Getting, "SEND_FILE", PATH_SERV, PATH_CLIENT);

                                }else if(iter.key() == "COPY_FILE"){

                                    obj_val = iter.value().toObject();

                                    COPY_FROM = obj_val.take("COPY_FROM").toString();
                                    COPY_TO = obj_val.take("COPY_TO").toString();

                                    connector_Command(res_Rule_Id_Getting, "SEND_FILE", PATH_SERV, PATH_CLIENT);

                                }else if(iter.key() == "REMOVE_FILE"){
                                    REMOVE_FILE = iter.value().toString();

                                    connector_Command(res_Rule_Id_Getting, "REMOVE_FILE", "", REMOVE_FILE);

                                }else if(iter.key() == "COMPLITE_SOFT"){

                                    COMPLITE_SOFT = iter.value().toString();

                                    connector_Command(res_Rule_Id_Getting, "COMPLITE_SOFT", "", COMPLITE_SOFT);

                                }else if(iter.key() != "STATE"){
                                    qDebug() << QString("<%1> роль выполняет не изестную команду <%2>").arg(rul).arg(iter.key());
                                }
                            }
                        }else{
                            qDebug() << QString("Задача уже выполненна клиентом <%1>").arg(rul);
                        }

                    }else{
                        emit newMessage(QString("Невозможно открыть файл <%1> роли <%2> клиента <%3>")
                                        .arg(rul).arg(res_Rule_Id_Getting).arg(path_File_Instructions_Rule));
                    }
                }
            }*/
            //timer->start(1000);
    }
}

void MainWindow::slot_readSocket()
{
    QTcpSocket* socket_Read = reinterpret_cast<QTcpSocket*>(sender());
    qintptr sock_desc = socket_Read->socketDescriptor();

    QDataStream socketStream(socket_Read);
    QByteArray buffer;
    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> buffer;
    qDebug() << "Header client " << buffer.mid(0,8);
    qDebug() << "buffer" << buffer;

    if(!socketStream.commitTransaction())
    {

        QString message = QString("%1 клиент :: Ожидание получения данных.. %2 %3")
                .arg(socket_Read->socketDescriptor())
                .arg(socketStream.status())
                .arg(socket_Read->errorString());
        emit newMessage(message);
        return;
    }

    QString header = buffer.mid(0,128);
    QString fileType = header.split(",")[0].split(":")[1];

    buffer = buffer.mid(128);
    qDebug() << "file path header " << header;
    if(fileType=="attachment"){
        QString filePath = header.split(",")[1].split(":")[1];
        qDebug() << "file path atech " << filePath;
        QFile file(filePath);
        if(file.open(QIODevice::WriteOnly)){
            file.write(buffer);
            QString message = QString("Инфо :: Данные от sd:%1 успешно сохраненны по пути %2").arg(socket_Read->socketDescriptor()).arg(QString(filePath));
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
            disconnect(socket_Read, QString("Роль <(%1)> не найденна или занята для клиента (%2)").arg(QString::fromStdString(buffer.toStdString())).arg(sock_desc));
        }
    }else if(fileType == "status")
    {
        QString command = buffer.split(':')[0];
        QString status = buffer.split(':')[1];

        emit newMessage(QString("<%1> :: <%2> <%3>").arg(sock_desc).arg(command).arg(status));

        if(status == "ok")
        {

        }
    }

}


void MainWindow::on_pushButton_clicked()
{
    this->addr = ui->lineEdit->text();
    this->port = ui->lineEdit_2->text().toUInt();

    if(m_server->listen(addr, port))
    {
       connect(m_server, &QTcpServer::newConnection, this, &MainWindow::slot_newConnection);
       ui->statusBar->showMessage("Сервер работает...");
    }
    else
    {
        QMessageBox::critical(this,"QTCPServer",QString("Не удалось запустить сервер: %1.").arg(m_server->errorString()));
        exit(EXIT_FAILURE);
    }
}


void MainWindow::slot_discardSocket()
{
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    disconnect(socket, "Инфо :: Клиент только что вышел из комнаты!");
}

void MainWindow::slot_displayError(QAbstractSocket::SocketError socketError)
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

