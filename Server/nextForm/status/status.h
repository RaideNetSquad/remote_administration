#pragma once

#include "table/modelTable.h"
#include <QDebug>
#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMutex>
namespace Ui {
    class Status;
}
//логика формы отправки файлов
class StatusForm : public QMainWindow
{
    Q_OBJECT
public:
    StatusForm(QWidget* parent = 0);
private:
    Ui::Status* formStatus_ui;

    QTableView* clientStatus;
    QStandardItemModel *model;
    QStandardItem *item;

    QVector<HostsCommand> commandHost;

    QMutex *mutex;

    void setTable(Ui::Status *);
public:
    void setRowTable(QString, QVariant);

};
