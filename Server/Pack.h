#ifndef PACK_H
#define PACK_H
#include <QDataStream>
#include <QString>
#include <QDateTime>
#include <QVariant>
class Packet
{
public:
    Packet(){};
    Packet(QString name /*QDateTime, QString, QString, QString,QString*/){
        this->hostName = name;
    };
private:
    QString hostName;
    QDateTime dateAndTime;
    QString path;
    QString nameCommand;
    QString textCommand;
    QVariant command;
    QString error;
    QByteArray bytes;
public:
    QString getHostName()
    {
        return this->hostName;
    };
    QDateTime getDateAndTime()
    {
        return this->dateAndTime;
    };
    QString getPath()
    {
        return this->path;
    }
    QString getNameCommand()
    {
        return this->nameCommand;
    };
    QString getTextCommand()
    {
        return this->textCommand;
    };
    QVariant getCommand()
    {
        return this->command;
    };
    QString getError()
    {
        return this->error;
    };
    QByteArray getBytes()
    {
        return this->bytes;
    }

    void setHostName(QString &name)
    {
        this->hostName = name;
    };
    void setDateAndTime(QDateTime &dat)
    {
        this->dateAndTime = dat;
    };
    void setPath(QString &path)
    {
        this->path = path;
    }
    void setNameCommand(QString &name)
    {
        this->nameCommand = name;
    };
    void setTextCommand(QString &name)
    {
        this->textCommand = name;
    };
    void setCommand(QVariant &name)
    {
        this->command = name;
    };
    void setError(QString &name)
    {
        this->error = name;
    };
    void setBytes(QByteArray &arr)
    {
        this->bytes = arr;
    }
public:
    friend QDataStream &operator <<(QDataStream &stream,const Packet &net);
    friend QDataStream &operator >>(QDataStream &stream, Packet &net);
};
inline QDataStream &operator>>(QDataStream &stream, Packet &pack)
{
    stream >> pack.hostName;
    stream >> pack.dateAndTime;
    stream >> pack.path;
    stream >> pack.nameCommand;
    stream >> pack.textCommand;
    stream >> pack.command;
    stream >> pack.error;
    stream >> pack.bytes;
    return stream;
}
inline QDataStream &operator<<(QDataStream &stream, const Packet &pack)
{
    stream << pack.hostName;
    stream << pack.dateAndTime;
    stream << pack.path;
    stream << pack.nameCommand;
    stream << pack.textCommand;
    stream << pack.command;
    stream << pack.error;
    stream << pack.bytes;
    return stream;
}

#endif // PACK_H
