#include "mainwindow.h"

//[2]
void MainWindow::parser_TimeDo(QString path_f)
{
    QJsonDocument dc_Js = get_JsonDocument(path_f);
    QJsonObject obj_Js = dc_Js.object();
    //qDebug() << obj_Js.begin().key() << " get start command from file";
    start_Commands = obj_Js.begin().key();
    //коннектор ролей и их инструкций
    path_Instructions_Roles = obj_Js.begin().value().toString();

    if(start_Commands.isEmpty() || path_Instructions_Roles.isEmpty())
    {
        emit newMessage(QString("Не удалось вытащить команды из файла по пути <%1>, проверьте правильность json файла").arg(path_f));
        QMessageBox::critical(this,"Ошибка", QString("Не удалось вытащить команды из файла по пути <%1>, проверьте правильность json файла").arg(path_f));
        exit(EXIT_FAILURE);
    };

}

void MainWindow::parser_File_With_Roles_Instructions()
{
    //path_Instructions_Roles - свойство
    QJsonDocument rFD = get_JsonDocument(path_Instructions_Roles);
    QJsonArray arr_Roles = rFD.array();

    QJsonObject current_Rule_Object;

    QString rul_Value;

    QString path_File_Instructions;

    int rul_socketId_Client;

    for(int i = 0; i < arr_Roles.size(); ++i)
    {
        current_Rule_Object = arr_Roles[i].toObject();

        rul_Value = current_Rule_Object.keys()[0];
        rul_socketId_Client = rule_map->get_Id_Rule(rul_Value);

        if(rul_socketId_Client != 0)
        {
            path_File_Instructions = current_Rule_Object.value(rul_Value).toString();
            //парсинг файла с инструкциями роли
            parser_File_With_Instructions_Role(rul_socketId_Client, rul_Value, path_File_Instructions);
        }
    }
}

void MainWindow::parser_File_With_Instructions_Role(int rul_socketId_Client,QString rul_Value, QString path_File_Instructions)
{
    qDebug() << "parser_File_With_Instructions_Role [5]";
    //парсинг файла с инструкциями роли
    path_File_Instructions = split_Path_File(path_File_Instructions);

    QJsonObject rFO = get_JsonDocument(path_File_Instructions).object();
    //состояние выполнения инструкций всех
    QString state = rFO.take("STATE").toString();
    QJsonArray arr_Commands_With_State;
    QJsonArray arr_Commands;

    QJsonObject current_Command;
    QJsonObject current_Status;

    QString key_Current_Comand;
    QJsonObject current_Command_Object;

    QString status_Command;
    QString status_Value;

    QJsonObject command_Obj;
    QString command_Str;
    if(state != "ok")
    {
         arr_Commands_With_State = rFO.take("COMMANDS").toArray();

         for(int j = 0; j < arr_Commands_With_State.size(); ++j)
         {
             arr_Commands = arr_Commands_With_State[j].toArray();

             current_Status = arr_Commands[0].toObject();
             current_Command = arr_Commands[1].toObject();

             key_Current_Comand = current_Command.keys()[0];

             if(current_Status.value("STATE") == ""){
                 command_Obj = current_Command.value(key_Current_Comand).toObject();
                 if(command_Obj.isEmpty()){
                     command_Str = current_Command.value(key_Current_Comand).toString();
                     commands_Connector(key_Current_Comand, command_Str, rul_socketId_Client);
                 }else{
                     current_Command_Object = current_Command.value(key_Current_Comand).toObject();
                     commands_Connector(key_Current_Comand, current_Command_Object, rul_socketId_Client);
                 }
             }else{
                 emit newMessage(QString("Команда <%1> уже выполненна ролью <%2>")
                                 .arg(key_Current_Comand)
                                 .arg(rul_Value));
             }
         }
    }else
    {
        emit newMessage(QString("Все инструкции выполненны, измените файл <%1> с инструкциями для роли <%2>")
                        .arg(path_File_Instructions)
                        .arg(rul_Value));
    }
}

void MainWindow::commands_Connector(const QString& key_Current_Comand,
                                    const QJsonObject &current_Command_Object,
                                    const int& socketId_Client)
{
    qDebug() << "commands_Connector [7]";
    QTcpSocket *socket = new QTcpSocket();
    socket->setSocketDescriptor(socketId_Client);

    qDebug() << key_Current_Comand << " Key command " << current_Command_Object;

    //ПОЛУЧИТЬ КЛИЕНТУ ФАЙЛ ОТ СЕРВЕРА
    if(key_Current_Comand == "GET_FILE"){
       QString PATH_SERV = split_Path_File(current_Command_Object.value("PATH_SERV").toString());
       QString PATH_CLIENT = current_Command_Object.value("PATH_CLIENT").toString();

       emit newMessage(QString("Передаю файл <%1> клиенту <%2>")
                       .arg(PATH_SERV).arg(socketId_Client));

       sendAttachment(socket, PATH_SERV, PATH_CLIENT);

    }
    //ОТПРАВИТЬ ФАЙЛ ОТ КЛИЕНТА НА СЕРВЕР
    else if(key_Current_Comand == "SEND_FILE"){

       QString PATH_SERV = split_Path_File(current_Command_Object.value("PATH_SERV").toString());
       QString PATH_CLIENT = current_Command_Object.value("PATH_CLIENT").toString();

       emit newMessage(QString("Отправляю команду клиенту <%1>, для получения от него файла <%2>")
                       .arg(socketId_Client).arg(PATH_CLIENT));
       send_Command(socket, key_Current_Comand, QString("FROM:%1,TO:%2")
                    .arg(PATH_CLIENT)
                    .arg(PATH_SERV));

    }
    //КОПИРОВАТЬ ФАЙЛ
    else if(key_Current_Comand == "COPY_FILE"){
       QString FROM = current_Command_Object.value("FROM").toString();
       QString TO = current_Command_Object.value("TO").toString();

       emit newMessage(QString("Отправляю команду клиенту <%1>, для копирования файлов на его компьютере")
                       .arg(socketId_Client));
       send_Command(socket, key_Current_Comand, QString("FROM:%1,TO:%2")
                    .arg(FROM)
                    .arg(TO));

    }
}

void MainWindow::commands_Connector(const QString& key_Current_Comand,
                                    const QString &current_Command_Str_Value,
                                    const int& socketId_Client)
{
    qDebug() << "commands_Connector [7]";
    QTcpSocket *socket = new QTcpSocket();
    socket->setSocketDescriptor(socketId_Client);

    qDebug() << key_Current_Comand << " Key command " << current_Command_Str_Value;

    //УДАЛИТЬ ФАЙЛ
    if(key_Current_Comand == "REMOVE_FILE"){
        QString REMOVE_FILE = current_Command_Str_Value;
        emit newMessage(QString("Отправляю команду клиенту <%1>, для удаления файла на его компьютере")
                        .arg(socketId_Client));
        send_Command(socket, key_Current_Comand, QString("PATH:%1")
                     .arg(REMOVE_FILE));
    }
    //ЗАПУСТИТЬ ПРОГРАММУ
    else if(key_Current_Comand == "COMPLITE_SOFT"){
        QString COMPLITE_SOFT = current_Command_Str_Value;
        emit newMessage(QString("Отправляю команду клиенту <%1>, для выполнения программы на его компьютере")
                        .arg(socketId_Client));
        send_Command(socket, key_Current_Comand, QString("PATH:%1")
                     .arg(COMPLITE_SOFT));
    }
}
