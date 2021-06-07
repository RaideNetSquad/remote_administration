#include "threadclient.h"

void ThreadClient::connects()
{
    connect(newUser, SIGNAL(readyRead()),
            this, SLOT(slot_read()));
    connect(newUser, &QTcpSocket::disconnected,
            this, &ThreadClient::slot_disconnectHost);
}
