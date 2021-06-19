#include "mainwindow.h"

//[4]
void MainWindow::sendMessage(const QString&type,
                             const QString&value)
{
    //отправка команд - коротких сообщений
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:%1,fileSize:%2;")
                   .arg(type)
                   .arg(value.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = value.toUtf8();
    byteArray.prepend(header);

    socketStream.setVersion(QDataStream::Qt_5_15);
    socketStream << byteArray;

    emit newMessage(QString("Отправил данные серверу. Тип данных %1 значение %2")
                    .arg(type)
                    .arg(value));

};

void MainWindow::sendAttachment(QString path_C, QString path_S)
{
    qDebug() << "sendAttachment [5]";
    if(socket)
    {
        if(socket->isOpen())
        {

            QFile m_file(path_C);
            if(m_file.open(QIODevice::ReadOnly)){
                QDataStream socketStream(socket);
                socketStream.setVersion(QDataStream::Qt_5_15);

                QByteArray header;

                header.prepend(QString("fileType:attachment,fileName:%1,fileSize:%2;").arg(path_S).arg(m_file.size()).toUtf8());
                header.resize(128);

                QByteArray byteArray = m_file.readAll();


                byteArray.prepend(header);

                socketStream << byteArray;

            }else
                emit newError(QString("Не могу открыть файл <%1>, проверьте путь").arg(path_S));
        }
        else
            emit newError(QString("Нет возможности открыть сокет"));
    }
    else
        emit newError(QString("Нет подключения"));
}
