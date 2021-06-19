#include "clientObjectLogic.h"

void ClientObjectLogic::send_Command(const QString &command,const QString &text){
    //отправка команды клиенту
    QDataStream socketStream(clientSocket);
    socketStream.setVersion(QDataStream::Qt_5_15);

    QByteArray header;
    header.prepend(QString("fileType:command,command:%1,fileSize:%2;")
                               .arg(command)
                               .arg(text.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = text.toUtf8();
    byteArray.prepend(header);

    socketStream.setVersion(QDataStream::Qt_5_15);
    socketStream << byteArray;

    //if(command != "Error")
        //clientSocket->waitForReadyRead();
};

void ClientObjectLogic::send_Attachment(const QString &pathServer,const QString &pathClient){
    QFile m_file(pathServer);
    if(m_file.open(QIODevice::ReadOnly)){


         QDataStream socketStream(clientSocket);
         socketStream.setVersion(QDataStream::Qt_5_15);

         QByteArray header;

         header.prepend(QString("fileType:attachment,filePath:%1,fileSize:%2;").arg(pathClient).arg(m_file.size()).toUtf8());
         header.resize(128);

         QByteArray byteArray = m_file.readAll();
         byteArray.prepend(header);

         socketStream << byteArray;
         //clientSocket->waitForReadyRead();
    }else
         emit newMessage(QString("Не могу открыть файл <%1>, проверьте путь").arg(pathServer));
};
