#ifndef PACK_H
#define PACK_H
#include <QDataStream>
#include <QString>
#include <QDateTime>
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
    QString nameCommand;
    QString textCommand;
    QString jsonCommand;
    QString error;
public:
    QString getHostName()
    {
        return this->hostName;
    };
    QDateTime getDateAndTime()
    {
        return this->dateAndTime;
    };
    QString getNameCommand()
    {
        return this->nameCommand;
    };
    QString getTextCommand()
    {
        return this->textCommand;
    };
    QString getJsonCommand()
    {
        return this->jsonCommand;
    };
    QString getError()
    {
        return this->error;
    };

    QString setHostName(QString &name)
    {
        return this->hostName = name;
    };
    QDateTime setDateAndTime(QDateTime &dat)
    {
        return this->dateAndTime = dat;
    };
    QString setNameCommand(QString &name)
    {
        return this->nameCommand = name;
    };
    QString setTextCommand(QString &name)
    {
        return this->textCommand = name;
    };
    QString setJsonCommand(QString &name)
    {
        return this->jsonCommand = name;
    };
    QString setError(QString &name)
    {
        return this->error = name;
    };

public:
    friend QDataStream &operator <<(QDataStream &stream,const Packet &net);
    friend QDataStream &operator >>(QDataStream &stream, Packet &net);
};
inline QDataStream &operator>>(QDataStream &stream, Packet &pack)
{
    stream >> pack.hostName;
    stream >> pack.dateAndTime;
    stream >> pack.nameCommand;
    stream >> pack.textCommand;
    stream >> pack.jsonCommand;
    stream >> pack.error;
    return stream;
}
inline QDataStream &operator<<(QDataStream &stream, const Packet &pack)
{
    stream << pack.hostName;
    stream << pack.dateAndTime;
    stream << pack.nameCommand;
    stream << pack.textCommand;
    stream << pack.jsonCommand;
    stream << pack.error;
    return stream;
}

#endif // PACK_H
