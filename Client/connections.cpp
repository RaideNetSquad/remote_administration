#include "clientwindow.h"
#include "ui_clientwindow.h"

void ClientWindow::Connections()
{
    connect(connectToServ, SIGNAL(connected()),
            this, SLOT(slotNewConnected()));
    connect(connectToServ, SIGNAL(readyRead()),
            this, SLOT(slotRead()));

    connect(this, SIGNAL(create_file_signal(QString, QString)),
            this, SLOT(slot_send_command(QString, QString)),
            Qt::QueuedConnection);

    connect(this, SIGNAL(write_to_file_signal(QString, QString)),
            this, SLOT(slot_send_command(QString, QString)),
            Qt::QueuedConnection);

    connect(this, SIGNAL(open_file_signal(QString, QString)),
            this, SLOT(slot_send_command(QString, QString)),
            Qt::QueuedConnection);

    connect(this, SIGNAL(delete_file_signal(QString, QString)),
            this, SLOT(slot_send_command(QString, QString)),
            Qt::QueuedConnection);

    connect(this, SIGNAL(copy_file_signal(QString, QString)),
            this, SLOT(slot_send_command(QString, QString)),
            Qt::QueuedConnection);
}
