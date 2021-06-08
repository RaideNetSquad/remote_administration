#include "threadclient.h"

void ThreadClient::connects()
{
    connect(newUser, SIGNAL(readyRead()),
            this, SLOT(slot_read()));
    connect(newUser, &QTcpSocket::disconnected,
            this, &ThreadClient::slot_disconnectHost);
    //после передачи клиенту его имени
    connect(this, SIGNAL(got_Name_Client()),
             this, SLOT(slot_Got_Name_Client()));
}
