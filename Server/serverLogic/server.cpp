/*
    * Логика сервера
    *
    * создание таблицы
    * реализация потоков для каждого подключения
    * ловим сигналы потоков
    *
    * функция connects() - реализует все сигнало слотовые соединения с потоком
    * функция incomingConnection() - вызывается при каждом подключении с передачей
    * дескриптора
    * getHostInfo() - слот получающиц инфу о хосте
    * getJson() -слот получающий строку json
    * SendDataToHost() - отправляю данные хосту
*/
#include "server.h"

#include <QTcpSocket>
#include <mutex>
#include "Pack.h"
#include <QHostInfo>


Server::Server(Ui::Dialog *ui, QObject* parent)
    : QTcpServer(parent),
      pack(new Packet()),
      table(new Table_Work(ui, commandHost)),
      cl_Map_Obj(new Clients_Map_Object())
{
    //сигнало слотовые соединения в качестве аргумента передают тип Пакета
    qRegisterMetaType<Packet>("Packet");
}


//подключения
void Server::incomingConnection(qintptr socketDescriptor)
{
    //объекта клиента перемещаю в отдельный поток и дескриптор
    ThreadClient* cl = new ThreadClient(socketDescriptor);

    QThread* thread = new QThread;
    cl->moveToThread(thread);

    //обработка сигнало слотовых соединений
    connects(cl, thread);

    thread->start();
}


//добавляю новый хост в карту
void Server::getHostInfo(QString name, int desc)
{
    this->hosts[name] = desc;
}


