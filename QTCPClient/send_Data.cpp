#include "mainwindow.h"
void MainWindow::send_rule(const QString& rule)
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

void MainWindow::sendAttachment(QString path_C, QString path_S)
{
    qDebug() << "sendAttachment [5]";
    if(socket)
    {
        if(socket->isOpen())
        {

            QFile m_file(path_C);
            qDebug() << "path Server file " << path_S;
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
                emit newMessage(QString("Не могу открыть файл <%1>, проверьте путь").arg(path_S));
        }
        else
            emit newMessage(QString("Нет возможности открыть сокет"));
    }
    else
        emit newMessage(QString("Нет подключения"));
}

void MainWindow::sendMessageStatusCommand(QString mess)
{
    qDebug() << "sendMessageStatusCommand [5]";
    if(socket)
    {
        if(socket->isOpen())
        {
                QDataStream socketStream(socket);
                socketStream.setVersion(QDataStream::Qt_5_15);

                QByteArray header;

                header.prepend(QString("fileType:status,fileSize:%1;").arg(mess.size()).toUtf8());
                header.resize(128);

                QByteArray byteArray = mess.toUtf8();
                byteArray.prepend(header);
                socketStream.setVersion(QDataStream::Qt_5_15);
                socketStream << byteArray;
        }
        else{
            emit newMessage(QString("Нет возможности открыть сокет"));
        }
    }
    else
    {
        emit newMessage(QString("Нет подключения"));
    }
};
