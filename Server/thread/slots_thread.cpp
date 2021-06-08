#include "threadclient.h"

//читаю данные от сокета
void ThreadClient::slot_read()
{
    QDataStream in;
    in.setDevice(newUser);
    in.setVersion(QDataStream::Qt_4_0);
    while(newUser->bytesAvailable())
    {
        in.startTransaction();
        in >> pack;

        if (!in.commitTransaction())
        {
            //если есть ошибки при чтении байт
            return;
        }
        //проверка комманд
        //checkNameAndSendSignal(pack);
        //логгирование
    }
    qDebug() << pack.getIdCommand() << pack.get_ByteData();

    //маршрутизатор команд
    controller_network_command();

}
//после получения имени клиента, отправить ему его идентификатор
void ThreadClient::slot_Got_Name_Client()
{

};
//разрыв соединения
void ThreadClient::slot_disconnectHost()
{
    qDebug() << "slot disconnect";
    emit connect_finished_signal(socketDescriptor);
    this->~ThreadClient();
}
