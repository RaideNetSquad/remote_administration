/*
    Объект-коннектор для связи объекта Модели и Представления таблицы
    с объектом словаря
*/

#ifndef TABLE_WORK_H
#define TABLE_WORK_H

#include <QObject>

#include "thread/threadclient.h"
#include "modelTable.h"

class Table_Work : public QObject
{
    Q_OBJECT
public:
    Table_Work();
    explicit Table_Work(Ui::Dialog *ui,
                        QVector<HostsCommand> *commandHost,
                        QObject* parent = 0);
private:
    QMutex *mutex;
    QVector<HostsCommand> commandHost;
    Ui::Dialog *ui;

    ModelTable *tableModel;
    QTableView* clientStatus;
public:
    void setTable(Ui::Dialog *ui);
    void setRowTable(QString name, QVariant command);
};

#endif // TABLE_WORK_H
