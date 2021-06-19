#include "clientObjectLogic.h"

void ClientObjectLogic::slot_parserFileWithInstructionsRole(const int &socketDescriptor,
                                                            const QString &role,
                                                            const QString &path,
                                                            const QString &lastRole){
    pathInstructionOfClient = path;
    this->lastRole = lastRole;
    this->role = role;
    qDebug() << "PARSER " << path << role;
    if(socketDescriptor == clientSocket->socketDescriptor()){
        QJsonObject rFO = get_JsonDocument(path).object();

        QJsonArray arrCommandsWithState;
        QJsonArray arrCommands;

        QJsonObject currentCommand;
        QJsonObject currentStatus;

        QString keyCurrentComand;
        QJsonObject currentCommandObject;


        QJsonObject commandObj;
        QString commandStr;
             arrCommandsWithState = rFO.take("COMMANDS").toArray();

             for(int j = 0; j < arrCommandsWithState.size(); ++j){
                 currentCommand = arrCommandsWithState[j].toObject();


                 keyCurrentComand = currentCommand.keys()[0];
                    if(j == (arrCommandsWithState.size()-1))
                        lastCommand = keyCurrentComand;

                     commandObj = currentCommand.value(keyCurrentComand).toObject();
                     if(commandObj.isEmpty()){
                         commandStr = currentCommand.value(keyCurrentComand).toString();
                         commandsConnector(keyCurrentComand, commandStr, role);
                     }else{
                         currentCommandObject = currentCommand.value(keyCurrentComand).toObject();
                         commandsConnector(keyCurrentComand, currentCommandObject, role);
                     }
             }
    }
}
void ClientObjectLogic::slot_ReadyRead(){
    qintptr sock_desc = clientSocket->socketDescriptor();

    QDataStream socketStream(clientSocket);
    QByteArray buffer;
    socketStream.setVersion(QDataStream::Qt_5_15);

    socketStream.startTransaction();
    socketStream >> buffer;

    if(!socketStream.commitTransaction())
    {
         return;
    }
    if(buffer.isEmpty()){
        return;
    }
    QString header = buffer.mid(0,128);
    QString fileType = header.split(",")[0].split(":")[1];
    buffer = buffer.mid(128);
    qDebug() << "file path header " << header;
    checkFileType(fileType, sock_desc, header, buffer);

};

void ClientObjectLogic::checkFileType(const QString &fileType,
                                      const qintptr &sockDesc,
                                      const QString &header,
                                      const QByteArray &buffer){
    if(fileType=="attachment"){
               QString filePath = header.split(",")[1].split(":")[1];
               qDebug() << "file path atech " << filePath;
               QFile file(filePath);
               if(file.open(QIODevice::WriteOnly)){
                   file.write(buffer);
                   QString message = QString("Инфо :: Данные от sd:%1 успешно сохраненны по пути %2").arg(role).arg(QString(filePath));
                   emit newMessage(message);
               }else{
                   //QMessageBox::critical(this,"Отправитель", "Ошибка передачи данных.");
                   return;
               }
               file.close();
    }else if(fileType == "role")
    {
              role = QString("%1").arg(QString::fromStdString(buffer.toStdString()));

              emit newMessage(QString("Подключился клиент с ролью %1").arg(role));
              emit checkRole(role, (int)sockDesc);

    }else if(fileType == "status")
    {
               QString textDataSender = QString("%1").arg(QString::fromStdString(buffer.toStdString()));
               QString command = textDataSender.split(':')[0];
               QString status = textDataSender.split(':')[1];

               emit newMessage(QString("<%1> :: <%2> <%3>").arg(sockDesc).arg(command).arg(status));

    }else if(fileType == "Error"){
          QString textDataSender = QString("%1").arg(QString::fromStdString(buffer.toStdString()));
          emit newMessage(QString("Клиент с ролью %1 не выполнил комманду, разрыв соединения. Причина - %2").arg(role).arg(textDataSender));
          emit delClientObj((int)sockDesc);
          emit disconnectClient();
    }
};

void ClientObjectLogic::slot_discardSocket(){
    emit finished();
}
void ClientObjectLogic::slot_disconnectWithClient(const qintptr &desc, const QString &text){

    if(clientSocket->socketDescriptor() == desc){
        send_Command("Error", text);
        emit finished();
    }
};
