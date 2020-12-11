#include "server.h"
//обработчик ошибок

//при отсутствии хоста
void Server::errorFoundHost(Packet pack, int socketDescriptor)
{
    QDateTime time = QDateTime::currentDateTime();
    QString mesError = "Отсутствует хост, которому нужно отправить команды, обратитесь в службу поддержки!";
    QString name = "Error";

    pack.setDateAndTime(time);
    pack.setNameCommand(name);
    pack.setTextCommand(mesError);
    setRowTable(pack.getHostName(), mesError);
    //QMap<QString, int> map;
    //map[pack.getHostName()] = socketDescriptor;
    //QMap<QString, int>::Iterator currentIt = map.begin();
    SendDataPack(pack, socketDescriptor);


    emit logger(pack);
}
//разрыв соединения
void Server::finish_connect_slot(int socketDescriptor)
{
    Packet pack;
    QDateTime time = QDateTime::currentDateTime();
    QString name;
    QString nameCommand = "Статус";
    QString textCommand = "Разрыв соединения";
    pack.setDateAndTime(time);
    pack.setNameCommand(nameCommand);
    pack.setTextCommand(textCommand);
    QMap<QString, int>::iterator it = hosts.begin();
    for(; it != hosts.end(); ++it)
    {
        if(it.value() == socketDescriptor)
        {
            name = it.key();
            pack.setHostName(name);
            hosts.remove(it.key());
            emit logger(pack);
            return;
        }
    }
}
