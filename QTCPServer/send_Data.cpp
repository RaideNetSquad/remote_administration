#include "mainwindow.h"

void MainWindow::sendAttachment(QTcpSocket* socket,
                                const QString& path_S,
                                const QString& path_C)
{

            QFile m_file(path_S);
            qDebug() << "path Server file " << path_S;
            if(m_file.open(QIODevice::ReadOnly)){


                QDataStream socketStream(socket);
                socketStream.setVersion(QDataStream::Qt_5_15);

                QByteArray header;

                header.prepend(QString("fileType:attachment,filePath:%1,fileSize:%2;").arg(path_C).arg(m_file.size()).toUtf8());
                header.resize(128);

                QByteArray byteArray = m_file.readAll();
                byteArray.prepend(header);

                socketStream << byteArray;
            }else
                emit newMessage(QString("Не могу открыть файл <%1>, проверьте путь").arg(path_S));

};

void MainWindow::send_Command(QTcpSocket* socket,
                              const QString& command,
                              const QString& text)
{
    qDebug() << "send_Command [8] " << command << text;


                QDataStream socketStream(socket);
                socketStream.setVersion(QDataStream::Qt_5_15);
                qDebug() << QString("fileType:command,command:%1,fileSize:%2;")
                            .arg(command)
                            .arg(text.size()).toUtf8() << " STR COMMAND SEND" << socket->socketDescriptor();
                QByteArray header;
                header.prepend(QString("fileType:command,command:%1,fileSize:%2;")
                               .arg(command)
                               .arg(text.size()).toUtf8());
                header.resize(128);

                QByteArray byteArray = text.toUtf8();
                byteArray.prepend(header);

                socketStream << byteArray;

}
