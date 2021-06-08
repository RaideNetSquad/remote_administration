#include "server.h"
#include "../thread/threadclient.h"

//сигнало-слотовое соединение
void Server::connects(ThreadClient* cl, QThread* thread)
{
    //для передачи имени хоста и его ид в мар
    //connect(cl, SIGNAL(send_name_and_socket_to_qmap(QString&, int&)),
            //this, SLOT(slot_get_name_and_socket_to_qmap(QString&, int&)));

    connect(cl, SIGNAL(connect_finished_signal(int)),
            this, SLOT(finish_connect_slot(int)));
    connect(thread, &QThread::finished,
            thread, &QThread::deleteLater);

    connect(cl, SIGNAL(sendJsonFromThread(int,Packet)),
            this, SLOT(getJson(int, Packet)));

    /*connect(cl, SIGNAL(sendHostNameAndDescriptor(QString, int)),
            this, SLOT(getHostInfo(QString, int)),
            Qt::QueuedConnection);*/

    connect(cl, SIGNAL(sendData_toTable(const QString&, const QString&)),
            this, SLOT(slot_sendData_toTable(const QString&, const QString&))
            );

    connect(cl, SIGNAL(logger(const QDateTime&,
                              const QString&,
                              const QString&)),
            this, SLOT(slot_logger(const QDateTime&,
                                   const QString&,
                                   const QString&))
            );

    connect(this, SIGNAL(logger(const QDateTime&,
                                const QString&,
                                const QString&)),
            this, SLOT(slot_logger(const QDateTime&,
                                   const QString&,
                                   const QString&))
            );
}
