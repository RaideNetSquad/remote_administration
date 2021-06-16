#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "on_pushButton_clicked [1]";


    this->addr = ui->lineEdit->text();
    this->port = ui->lineEdit_2->text().toUInt();
    this->rule = ui->lineEdit_3->text();

    connection();
    //send_rule(rule);

}

void MainWindow::readSocket()
{
    qDebug() << "read socket [4]";
    QDataStream socketStream(socket);
    QByteArray buffer;

    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> buffer;
    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1 клиент :: Ожидание получения данных.. %2 %3")
                .arg(socket->socketDescriptor())
                .arg(socketStream.status())
                .arg(socket->errorString());
        emit newMessage(message);

        return;
    }

    QString header = buffer.mid(0,128);
    qDebug() << header << " Header";
    buffer = buffer.mid(128);

        QString fileType = header.split(",")[0].split(":")[1];
        qDebug() << header << " Header";
        if(fileType=="attachment"){
            QString filePath = header.split(",")[1].split(":")[1];
            filePath = split_Path_File(filePath);
            qDebug() << filePath << " filePath";

            QFile file(filePath);
            if(file.open(QIODevice::WriteOnly)){
                file.write(buffer);
                QString message = QString("Инфо :: Вложения от sd:%1 успешно сохраненны на диске от %2").arg(socket->socketDescriptor()).arg(QString(filePath));
                emit newMessage(message);
            }else
                QMessageBox::critical(this,"Отправитель", "Неизвестная ошибка записи вложений, поговорите с разработчиком.");
       }else if(fileType == "command"){
            //fileType:command,command:%1,fileSize:%2;
            qDebug() << header << " header";
            QString command = header.split(",")[1].split(":")[1];
            QString textCommand = buffer;

            if(command == "SEND_FILE"){
                //"FROM:%1,TO:%2"
                QString from  = textCommand.split(",")[0].split(":")[1];
                from = split_Path_File(from);

                QString to = textCommand.split(",")[1].split(":")[1];
                sendAttachment(from, to);
                //sendMessageStatusCommand("send:ok");
            }else if(command == "COPY_FILE"){
                //"FROM:%1,TO:%2"
                QString from  = textCommand.split(",")[1].split(":")[1];
                if(from.split("/")[0] == ".")
                {
                    from = QString("%1/%2").arg(QDir::currentPath()).arg(from.split("./")[1]);
                };
                QString to = textCommand.split(",")[0].split(":")[1];
                if(to.split("/")[0] == ".")
                {
                    to = QString("%1/%2").arg(QDir::currentPath()).arg(to.split("./")[1]);
                };
                qDebug() << from  << "From " << from << " To";
                QFile::copy(from, to);

                emit newMessage(QString("Скопировал файл из %1 по пути %2").arg(from, to));
                sendMessageStatusCommand("copy:ok");

            }else if(command == "REMOVE_FILE"){
                //"PATH:%1"
                QString path = textCommand.split(":")[1];
                if(path.split("/")[0] == ".")
                {
                    path = QString("%1/%2").arg(QDir::currentPath()).arg(path.split("./")[1]);
                };

                emit newMessage(QString("Удаляю файл %1").arg(path));

                QFile file(path);
                file.remove();

                sendMessageStatusCommand("remove:ok");

            }else if(command == "COMPLITE_SOFT"){
                //"PATH:%1"
                QString path = textCommand.split(":")[1];
                path = split_Path_File(path);
                const QString p = path;
                QProcess* newProcess = new QProcess();
                qDebug() << "PATH " << p;
                newProcess->start(p);
                if (!newProcess->waitForStarted())
                {
                    emit newMessage(QString("Не могу выполнить программу %1").arg(path));
                    qDebug() << "Errrorrr comand " << newProcess->errorString();
                    return;
                }


                emit newMessage(QString("Выполняю программу %1").arg(path));
                //sendMessageStatusCommand("complite:ok");
            }
            else if(command == "SEND_RULE"){
                send_rule(rule);
            }
        }

    qDebug() << header << " Header";

    socket->readAll();

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
