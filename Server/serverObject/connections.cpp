#include "server.h"
#include "../thread/threadclient.h"

//сигнало-слотовое соединение
void Server::connects(ThreadClient* cl, QThread* thread)
{
    connect(cl, SIGNAL(connect_finished_signal(int)),
            this, SLOT(finish_connect_slot(int)));
    connect(thread, &QThread::finished,
            thread, &QThread::deleteLater);

    connect(cl, SIGNAL(sendJsonFromThread(int,Packet)),
            this, SLOT(getJson(int, Packet)));

    /*connect(cl, SIGNAL(sendHostNameAndDescriptor(QString, int)),
            this, SLOT(getHostInfo(QString, int)),
            Qt::QueuedConnection);*/
    connect(cl, SIGNAL(sendData(int,Packet)),
            this, SLOT(slot_sendData(int,Packet ))
            );

    connect(cl, SIGNAL(logger(Packet)),
            this, SLOT(slot_logger(Packet))
            );
    connect(this, SIGNAL(logger(Packet)),
            this, SLOT(slot_logger(Packet))
            );
    connect(cl, SIGNAL(new_client_set_item_from_thread(QString,int)),
            this, SLOT(new_client_set_item_to_server(QString, int)));
}
