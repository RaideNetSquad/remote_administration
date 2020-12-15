#include <QTableView>
#include "../status.h"
#include "modelTable.h"
#include "ui_status.h"


//установка таблицы
void StatusForm::setTable(Ui::Status *ui){
    qDebug() << "setTable f";
    clientStatus = ui->ClientStatus;
    clientStatus->horizontalHeader()->setVisible(true);
    clientStatus->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ModelTable *tableModel = new ModelTable(this);

    tableModel->setRow(commandHost);
    clientStatus->setModel(tableModel);
    model = new QStandardItemModel;
    qDebug() << "Set headers";
    QStringList horizontalHeader;
    horizontalHeader.append("Хост");
    horizontalHeader.append("Выполняемая команда");

    QStringList verticalHeader;
    verticalHeader.append("1");

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    clientStatus->setModel(model);
    clientStatus->resizeColumnsToContents();
    clientStatus->resizeRowsToContents();
    clientStatus->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    clientStatus->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

    qDebug() << "set table end";
}
//добавляю строку в таблицу
void StatusForm::setRowTable(QString name, QVariant command)
{
    mutex->lock();
    if(name.isNull() || name.isEmpty())
        return;

    ModelTable *tableModel = new ModelTable();

    HostsCommand strCOmmand;
    strCOmmand.nameHost = name;
    strCOmmand.nameCommand = command.toString();
    commandHost.append(strCOmmand);
    qDebug() << "command host " << commandHost[0].nameCommand;
    tableModel->setRow(commandHost);
    clientStatus->setModel(tableModel);
    mutex->unlock();
}


