#include "modelTable.h"
#include <QDebug>
#include <QBrush>
#include <QFont>
//реализация функционала таблицы
ModelTable::ModelTable(QObject *parent)
    : QAbstractTableModel(parent)
{

}

int ModelTable::rowCount(const QModelIndex &parent) const
{
   return parent.isValid() ? 0 : hostCommandVector.size();
}

int ModelTable::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 2;
}

QVariant ModelTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
          return QVariant();
      }
      if (index.column() == 0) {
          return hostCommandVector[index.row()].nameHost;
      } else if (index.column() == 1) {
          return hostCommandVector[index.row()].nameCommand;
      }
      return QVariant();
}

void ModelTable::setRow(const QVector<HostsCommand> &command)
{
    hostCommandVector = command;
    return;
}

QVariant ModelTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) {
            return QString("Хост");
        } else if (section == 1) {
            return QString("Команда");
        }
    }
    return QVariant();
}
