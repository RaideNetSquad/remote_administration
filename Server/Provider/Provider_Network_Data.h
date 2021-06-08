#ifndef PACK_H
#define PACK_H
#include <QDataStream>
#include <QString>
#include <QDateTime>
#include <QTcpSocket>
#include <QHostInfo>
#include <QDebug>

//Команды
#define GET_NAME 0
#define TO_ASK_NAME 1
#define GET_ID 2
#define SEND_MESSAGE 3
#define SEND_COMMAND 4
#define NULL_ID 10

#define SEND_ERROR 500
#define SERVER_ID 100

struct Datagram {
    int hostId;
    int idCommand;
    QByteArray data_byte_Arr;
    int error;
};

int getHostId(Datagram d);
int getIdCommand(Datagram d);
QByteArray get_ByteData(Datagram d);
int getError(Datagram d);
void setHostId(Datagram d, const int &id);
void setIdCommand(Datagram d, const int &id);
void setDataByArray(Datagram d, QString data);
void setError(Datagram d, const int &name);

//перегрузка оператора записи объекта в объект потока
inline QDataStream &operator>>(QDataStream &stream, Datagram &pack)
{
    stream >> pack.hostId;
    stream >> pack.idCommand;
    stream >> pack.data_byte_Arr;
    stream >> pack.error;
    return stream;
}
inline QDataStream &operator<<(QDataStream &stream, const Datagram &pack)
{
    stream << pack.hostId;
    stream << pack.idCommand;
    stream << pack.data_byte_Arr;
    stream << pack.error;
    return stream;
}

class Provider_Network_Data
{
public:

public:
    Provider_Network_Data(){};
public:
    void check_NetCommand_From_Server(QTcpSocket *sck, Datagram *datagram){
        //маршрутизатор команд

        const int command_id = getIdCommand(*datagram);

        if(command_id == TO_ASK_NAME)
        {
            this->send_Name(sck, datagram);
        };
    };

    void send_Name(QTcpSocket *sck, Datagram *datagram)
    {
        //отправить имя хоста серверу
        setIdCommand(*datagram, GET_NAME);

        QString localName = QHostInfo::localHostName();
        setDataByArray(*datagram, localName);
        qDebug() << getIdCommand(*datagram) << " id c";
        qDebug() << get_ByteData(*datagram) << " byte arr";
        this->dataSender(sck, *datagram);
    }

    void dataSender(QTcpSocket *connectToServ, Datagram datagram)
    {
        QByteArray arr;
        QDataStream out(&arr, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_0);

        qDebug() << getIdCommand(datagram);

        out << datagram;

        connectToServ->write(arr);
        connectToServ->waitForBytesWritten();
    }

};
#endif // PACK_H
