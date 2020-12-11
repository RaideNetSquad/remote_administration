#include <QDateTime>
#include <QString>
#include <QDataStream>
#ifndef PACK_H
#define PACK_H
struct Packet
{
    QString hostName;
    QDateTime dateAndTime;
    QString nameCommand;
    QString textCommand;
    QString jsonCommand;
    QString error;
};
inline QDataStream &operator>>(QDataStream &stream, Packet &pack)
{
    stream >>
            pack.hostName >>
            pack.dateAndTime >>
            pack.nameCommand >>
            pack.textCommand >>
            pack.jsonCommand >>
            pack.error;
}
inline QDataStream &operator<<(QDataStream &stream, const Packet &pack)
{
    stream << pack.hostName;
    stream << pack.dateAndTime;
    stream << pack.nameCommand;
    stream << pack.textCommand;
    stream << pack.jsonCommand;
    stream << pack.error;
}
#endif // PACK_H
