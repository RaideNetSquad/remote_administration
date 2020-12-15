#ifndef MODELTABLE_H
#define MODELTABLE_H
#include <QAbstractTableModel>
#include <QDataStream>

struct HostsCommand
{
    QString nameHost;
    QString nameCommand;
};

inline QDataStream &operator<<(QDataStream &stream, const HostsCommand &hostsCommand)
{
    return stream << hostsCommand.nameHost << hostsCommand.nameCommand;
}
inline QDataStream &operator>>(QDataStream &stream, HostsCommand &hostsCommand)
{
    return stream >> hostsCommand.nameHost >> hostsCommand.nameCommand;
}

class ModelTable : public QAbstractTableModel
{
    Q_OBJECT
public:
    ModelTable(QObject *parent = nullptr);

    void setRow(const QVector<HostsCommand> &hostCommandVector);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    QVector<HostsCommand> hostCommandVector;
};

#endif // MODELTABLE_H
