#include "table_work.h"

Table_Work::Table_Work(Ui::Dialog *ui,QVector<HostsCommand> *commandHost, QObject *parent): QObject(parent) ,
    tableModel(new ModelTable(this))
{
    //установка таблицы
    setTable(ui);
}

#include <QTableView>
#include "table_work.h"
#include "modelTable.h"
//установка таблицы
void Table_Work::setTable(Ui::Dialog *ui){
    //реализация модели и ее представления
    //для таблицы
    clientStatus = ui->table_clients;
    clientStatus->horizontalHeader()->setVisible(true);
    clientStatus->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ModelTable *tableModel = new ModelTable(this);

    tableModel->setRow(commandHost);
    clientStatus->setModel(tableModel);
    /*model = new QStandardItemModel;

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
*/
}
//добавляю строку в таблицу
void Table_Work::setRowTable(QString name, QVariant command)
{
    //отсутствие одновременного доступа к потоку
    if(name.isNull() || name.isEmpty())
        return;

    //модель таблицы
    ModelTable *tableModel = new ModelTable(this);

    HostsCommand strCOmmand;
    strCOmmand.nameHost = name;
    strCOmmand.nameCommand = command.toString();
    commandHost.append(strCOmmand);

    tableModel->setRow(commandHost);
    clientStatus->setModel(tableModel);
}
