#include "server.h"

//работаю с приходящим json файлом
void Server::getJson(int socketDescriptor, Packet pack)
{
    QString nameHost = pack.getHostName();
    QString nameCommand = pack.getNameCommand();
    QString textCommand = pack.getTextCommand();
    QString command = pack.getJsonCommand();
    QJsonDocument doc = QJsonDocument::fromJson(command.toUtf8());
    //массив команд и получателей
    QJsonArray arrInstructions = doc.array();
    //массив команд
    QJsonArray arrCommands;
    //массив получателей
    QJsonArray hostTo;

    QJsonObject obj;
    qDebug() << "check instructions";
    qDebug() << arrInstructions;
    //получаю массив инструкций и адресатов
    for(int i = 0; i < arrInstructions.size(); ++i)
    {
        obj = arrInstructions[i].toObject();
        if(obj.contains("commands")){
          arrCommands = obj.take("commands").toArray();
        };
        if(obj.contains("sendTo")){
          hostTo = obj.take("sendTo").toArray();
        };
    }
    QString all;
    //список хостов которым предназначаются инструкции
    QStringList listSendToHosts;
    //отправитель
    QMap<QString,int>::Iterator currentIt;
    currentIt = hosts.find(nameHost);
    qDebug() << currentIt.key() << currentIt.value() << "current sock";
    //получаю список отправителей
    //как определить кто именно отправляет джсон
    for(int i = 0; i < hostTo.size(); ++i)
    {
        if(hostTo[i].toString() == "all"){
            //отправляю всем
            all = "all";
            break;
        }
        //отправляю в список хостов
        listSendToHosts.append(hostTo[i].toString());
    }

    //отправляю всем
    qDebug() << hosts;
    if(hosts.isEmpty())
    {
        errorFoundHost("jsonsender" + nameHost, socketDescriptor);
        return;
    }
    if(!all.isNull())
    {
        QMap<QString,int>::Iterator it = hosts.begin();
        for(; it != hosts.end(); ++it)
        {
            SendDataPack(pack, it.value());
        }
        all = nullptr;
    //отправляю конкретным пользователям
    }else{

        for(int i = 0; i < listSendToHosts.size(); ++i)
        {
            qDebug() << listSendToHosts;
            qDebug() << hosts.contains(listSendToHosts[i]) << "check host at sendTO";
            if(hosts.contains(listSendToHosts[i]))
            {
                QMap<QString, int>::Iterator it = hosts.find(listSendToHosts[i]);
                qDebug() << it.key() << it.value() << " find host";
                SendDataPack(pack, it.value());
            }else{
                errorFoundHost("jsonsender " + nameHost, socketDescriptor);
            }

        }

    }

}

//проверяю есть ли хост в карте hosts
void Server::slot_sendData(int socket, Packet pack)
{
    QString nameHost = pack.getHostName();
    QString nameCommand = pack.getNameCommand();
    QString textCommand = pack.getTextCommand();

    if(!hosts.contains(nameHost) && nameCommand != "json" && nameCommand != "jsonSender")
    {
        getHostInfo(nameHost, socket);
    }
    if(nameCommand == "json" || nameCommand == "jsonsender"){
        setRowTable("jsonsender " + nameHost, textCommand);
    }else{
        setRowTable(nameHost, tr("%1 %2")
                                        .arg(nameCommand)
                                        .arg(textCommand));
    }

}


//журналирую данные в файл
void Server::slot_logger(Packet pack)
{
    mutex.lock();
    QFile log;
    log.setFileName("logger.txt");
    if(log.open(QIODevice::Append)){

        QTextStream loggerStream(&log);
        loggerStream.setCodec(QTextCodec::codecForName("UTF-8"));

        if(pack.getJsonCommand().isNull())
        {
            loggerStream << pack.getDateAndTime().toString() << " host: " << pack.getNameCommand() << " ----- " << pack.getNameCommand() << " - "
            << pack.getTextCommand() << "\n";
        }else{
            loggerStream << pack.getDateAndTime().toString() << " host: " << pack.getNameCommand() << " ----- " << pack.getNameCommand() << " - "
            << pack.getTextCommand() << " command: " << pack.getJsonCommand() << "\n";
        }

        log.close();
    }

    mutex.unlock();
}
