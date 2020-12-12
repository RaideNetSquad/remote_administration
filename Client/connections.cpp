#include "clientwindow.h"
#include "ui_clientwindow.h"

void ClientWindow::Connections()
{
    connect(connectToServ, SIGNAL(connected()),
            this, SLOT(slotNewConnected()));
    connect(connectToServ, SIGNAL(readyRead()),
            this, SLOT(slotRead()));

    connect(this, SIGNAL(complete_signal(QString, QString)),
            this, SLOT(slot_send_command(QString, QString)),
            Qt::QueuedConnection);
}
