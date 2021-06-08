#include "Provider_Network_Data.h"

int getHostId(Datagram d)
{

    return d.hostId;
};
int getIdCommand(Datagram d)
{
    return d.idCommand;
};
QByteArray get_ByteData(Datagram d)
{
    return d.data_byte_Arr;
};

int getError(Datagram d)
{
    return d.error;
};

void setHostId(Datagram d, const int &id)
{
    d.hostId = id;
};

void setIdCommand(Datagram d, const int &id)
{
    d.idCommand = id;
};

void setDataByArray(Datagram d, QString data)
{
    //запись байт данных в свойство пакета
    QByteArray arr = data.toUtf8();
    d.data_byte_Arr = arr;
}


void setError(Datagram d, const int &name)
{
    d.error = name;
};
