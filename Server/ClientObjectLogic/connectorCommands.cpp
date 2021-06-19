#include "clientObjectLogic.h"

void ClientObjectLogic::commandsConnector(const QString &keyCurrentComand,
                                const QJsonObject &currentCommandObject,
                                const QString &role)
{
    qDebug() << keyCurrentComand << currentCommandObject;
    //ПОЛУЧИТЬ КЛИЕНТУ ФАЙЛ ОТ СЕРВЕРА
    if(keyCurrentComand == "GET_FILE"){
       QString PATH_SERV = splitPathFile(currentCommandObject.value("PATH_SERV").toString());
       QString PATH_CLIENT = currentCommandObject.value("PATH_CLIENT").toString();

       emit newMessage(QString("Передаю файл <%1> клиенту <%2>")
                       .arg(PATH_SERV).arg(role));

       send_Attachment(PATH_SERV, PATH_CLIENT);
       if(clientSocket->isReadable())
           clientSocket->waitForReadyRead();

    }
    //ОТПРАВИТЬ ФАЙЛ ОТ КЛИЕНТА НА СЕРВЕР
    else if(keyCurrentComand == "SEND_FILE"){

       QString PATH_SERV = splitPathFile(currentCommandObject.value("PATH_SERV").toString());
       QString PATH_CLIENT = currentCommandObject.value("PATH_CLIENT").toString();

       emit newMessage(QString("Отправляю команду клиенту <%1>, для получения от него файла <%2>")
                       .arg(role).arg(PATH_CLIENT));
       send_Command(keyCurrentComand, QString("FROM:%1,TO:%2")
                    .arg(PATH_CLIENT)
                    .arg(PATH_SERV));
       if(clientSocket->isReadable())
           clientSocket->waitForReadyRead();

    }
    //КОПИРОВАТЬ ФАЙЛ
    else if(keyCurrentComand == "COPY_FILE"){
       QString FROM = currentCommandObject.value("FROM").toString();
       QString TO = currentCommandObject.value("TO").toString();

       emit newMessage(QString("Отправляю команду клиенту <%1>, для копирования файлов на его компьютере")
                       .arg(role));
       send_Command(keyCurrentComand, QString("FROM:%1,TO:%2")
                    .arg(FROM)
                    .arg(TO));
       if(clientSocket->isReadable())
           clientSocket->waitForReadyRead();
    }

    if((keyCurrentComand == lastCommand) && (role == lastRole)){
        qDebug() << lastCommand << role << "LASRT";
        emit lastCommandRole();
    }
}

void ClientObjectLogic::commandsConnector(const QString &keyCurrentComand,
                                const QString &current_Command_Str,
                                const QString &role)
{
    qDebug() << keyCurrentComand << current_Command_Str;
    //УДАЛИТЬ ФАЙЛ
    if(keyCurrentComand == "REMOVE_FILE"){
        QString REMOVE_FILE = current_Command_Str;
        qDebug() << "REMOVE " << current_Command_Str;
        emit newMessage(QString("Отправляю команду клиенту <%1>, для удаления файла на его компьютере")
                        .arg(role));
        emit send_Command(keyCurrentComand, QString("PATH:%1")
                     .arg(REMOVE_FILE));
        if(clientSocket->isReadable())
            clientSocket->waitForReadyRead();
    }
    //ЗАПУСТИТЬ ПРОГРАММУ
    else if(keyCurrentComand == "COMPLITE_SOFT"){
        QString COMPLITE_SOFT = current_Command_Str;
        qDebug() << "COMPLITE_SOFT " << current_Command_Str;
        emit newMessage(QString("Отправляю команду клиенту <%1>, для выполнения программы на его компьютере")
                        .arg(role));
        send_Command(keyCurrentComand, QString("PATH:%1")
                     .arg(COMPLITE_SOFT));
        if(clientSocket->isReadable())
            clientSocket->waitForReadyRead();
    }
    if((keyCurrentComand == lastCommand) && (role == lastRole)){
        qDebug() << lastCommand << role << "LASRT";
        emit lastCommandRole();
    }
}
