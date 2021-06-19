#include "mainwindow.h"
#include "ui_mainwindow.h"

//[0]
void MainWindow::on_pushButton_clicked()
{
    this->addr.setAddress(ui->lineEdit->text());
    this->port = ui->lineEdit_2->text().toUInt();
    this->role = ui->lineEdit_3->text();

    connection();
}
//[2]
void MainWindow::displayMessage(const QString& str)
{
    ui->textBrowser_receivedMessages->append(str);
}
//[3]
void MainWindow::readSocket()
{
    qDebug() << "read socket [3]";
    QDataStream socketStream(socket);
    QByteArray buffer;

    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> buffer;

    if(!socketStream.commitTransaction())
    {
        return;
    }

    QString header = buffer.mid(0,128);
    qDebug() << header << " Header";
    buffer = buffer.mid(128);

    QString fileType = header.split(",")[0].split(":")[1];
        if(fileType=="attachment"){
            QString filePath = header.split(",")[1].split(":")[1];
            filePath = split_Path_File(filePath);

            QFile file(filePath);
            if(file.open(QIODevice::WriteOnly)){
                file.write(buffer);
                QString message = QString("Инфо :: Вложения от sd:%1 успешно сохраненны на диске от %2").arg(socket->socketDescriptor()).arg(QString(filePath));
                emit newMessage(message);
            }else{
                emit newError(QString("Не записался файл роль %1 по пути %2").arg(role).arg(filePath));
            }
       }else if(fileType == "command"){
            //fileType:command,command:%1,fileSize:%2;
            qDebug() << header << " header";
            QString command = header.split(",")[1].split(":")[1];
            QString textCommand = QString("%1").arg(QString::fromStdString(buffer.toStdString()));
            if(command == "Error"){
                emit newError(QString("Ошибка %1").arg(textCommand));
                return;
            }
            if(command == "SEND_FILE"){
                qDebug() << textCommand << "SEND FILE BITCH";
                //"FROM:%1,TO:%2"
                QString from  = textCommand.split(",")[0].split(":")[1];
                from = split_Path_File(from);
                QFile f;
                if(!f.open(QIODevice::ReadOnly)){
                    emit newError(QString("Не найден путь к файлу %1 у роли %2").arg(from).arg(role));
                    return;
                }
                QString to = textCommand.split(",")[1].split(":")[1];
                sendAttachment(from, to);
                sendMessage("status","send Attachemnt:ok");

            }else if(command == "COPY_FILE"){
                //"FROM:%1,TO:%2"
                QString from  = split_Path_File(textCommand.split(",")[0].split(":")[1]);
                QString to = split_Path_File(textCommand.split(",")[1].split(":")[1]);

                if(!QFile::copy(from, to)){
                    emit newError(QString("У роли %1 неудалось скопировать файл %2 в %3").arg(role).arg(from).arg(to));
                    return;
                };

                emit newMessage(QString("Скопировал файл из %1 по пути %2").arg(from, to));
                sendMessage("status","copy file:ok");

            }else if(command == "REMOVE_FILE"){
                //"PATH:%1"
                QString path = split_Path_File(textCommand.split(":")[1]);


                emit newMessage(QString("Удаляю файл %1").arg(path));

                QFile file(path);
                file.remove();

                sendMessage("status","remove file:ok");

            }else if(command == "COMPLITE_SOFT"){
                //"PATH:%1"
                QString path = textCommand.split(":")[1];
                path = split_Path_File(path);
                const QString p = path;
                QProcess* newProcess = new QProcess();
                qDebug() << "PATH " << p;
                newProcess->start(p, QStringList() << "");
                if (!newProcess->waitForStarted())
                {
                    QString message = QString("Не могу выполнить программу %1 - %2 (Error)").arg(path).arg(newProcess->errorString());
                    emit newError(message);
                    return;
                }


                emit newMessage(QString("Выполняю программу %1").arg(path));
                sendMessage("status","complite file:ok");
            }
            else if(command == "SEND_ROLE"){
                sendMessage("role", role);
            }

        }
}

void MainWindow::discardSocket()
{
    ui->pushButton->setDisabled(false);
    socket->close();
    socket->deleteLater();
}
void MainWindow::slot_Error(const QString &text){
    sendMessage("Error", text);
    QMessageBox::information(this, "Сервер", text);
    qDebug() << text << "TextError";
    emit newMessage(text);
    socket->disconnectFromHost();
    socket->close();
    socket->deleteLater();
    ui->pushButton->setDisabled(false);
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
