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
#include "thread/threadclient.h"
#include <QTcpSocket>
#include <mutex>
#include "Pack.h"
#include <QHostInfo>


Server::Server(Ui::Dialog *ui, QObject* parent)
    : QTcpServer(parent), pack(new Packet(QHostInfo::localHostName()))
{
    //сигнало слотовые соединения в качестве аргумента передают тип Пакета
    qRegisterMetaType<Packet>("Packet");
    qDebug() << "Server start";
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
//парсер скрипта принимает текст файла и дескриптор
void Server::parseJsonCommand(QString text, int sock)
{
    qDebug() << "parse";
    QJsonDocument doc = QJsonDocument::fromJson(text.toUtf8());
    qDebug() << doc;
    //массив объектов json
    QJsonArray arr = doc.array();

    QJsonObject obj;
    QString key;
    QString value;
    for(int i = 0; i<arr.size(); ++i)
    {

        obj = arr[i].toObject();
        key = obj.keys()[0];
        qDebug() << key;
        pack->setNameCommand(key);
        if(key == "write_to_file")
        {
                QString from;
                QString to;
                QJsonObject o_c = obj.value(key).toObject();
                from = o_c.value("from").toString();
                to = o_c.value("to").toString();
                pack->setPath(to);
                pack->setTextCommand(from);
        }else{
            value = obj.value(key).toString();
            pack->setTextCommand(value);
        }


        SendDataPack(*pack, sock);
    }
}
//добавляю новый хост в карту
void Server::getHostInfo(QString name, int desc)
{
    this->hosts[name] = desc;
}


