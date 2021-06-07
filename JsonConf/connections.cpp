#include "network.h"
#include "form_json_send.h"


void Network::signal_slot_Connections()
{
    connect(connectToServ, SIGNAL(readyRead()),
            this, SLOT(slot_read()));
};

void FormJsonSend::signal_slot_Connections()
{

}
