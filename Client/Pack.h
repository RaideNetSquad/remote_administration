#ifndef PACK_H
#define PACK_H
#include <QDataStream>
#include <QString>
#include <QDateTime>

//Команды
#define SEND_NAME 0
#define TO_ASK_NAME 1
#define GET_ID 2
#define SEND_MESSAGE 3
#define SEND_COMMAND 4
#define NULL_ID 10

#define SEND_ERROR 500
#define SERVER_ID 100

class Packet
{
public:
    Packet(){};
    Packet(int id){
        this->hostId = id;
    };
private:
    int hostId;
    int idCommand;
    QByteArray data_byte_Arr;
    int jsonCommand;
    int error;
public:
    int getHostId()
    {
        return this->hostId;
    };
    int getIdCommand()
    {
        return this->idCommand;
    };
    QByteArray get_ByteData()
    {
        return this->data_byte_Arr;
    };
    int getJsonCommand()
    {
        return this->jsonCommand;
    };
    int getError()
    {
        return this->error;
    };

    void setHostId(const int &id)
    {
        this->hostId = id;
    };

    void setIdCommand(const int &id)
    {
        this->idCommand = id;
    };

    void setDataByArray(QString data)
    {
        //запись байт данных в свойство пакета
        QByteArray arr = data.toUtf8();
        this->data_byte_Arr = arr;
    }

    void setJsonCommand(const int &name)
    {
        this->jsonCommand = name;
    };
    void setError(const int &name)
    {
        this->error = name;
    };

public:
    friend QDataStream &operator <<(QDataStream &stream,const Packet &net);
    friend QDataStream &operator >>(QDataStream &stream, Packet &net);
};
//перегрузка оператора записи объекта в объект потока
inline QDataStream &operator>>(QDataStream &stream, Packet &pack)
{
    stream >> pack.hostId;
    stream >> pack.idCommand;
    stream >> pack.data_byte_Arr;
    stream >> pack.jsonCommand;
    stream >> pack.error;
    return stream;
}
inline QDataStream &operator<<(QDataStream &stream, const Packet &pack)
{
    stream << pack.hostId;
    stream << pack.idCommand;
    stream << pack.data_byte_Arr;
    stream << pack.jsonCommand;
    stream << pack.error;
    return stream;
}

#endif // PACK_H
