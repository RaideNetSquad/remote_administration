#include <QTableView>
#include "server.h"
#include "modelTable.h"
//установка таблицы
void Server::setTable(Ui::Dialog *ui){
    //реализация модели и ее представления
    //для таблицы
    clientStatus = ui->tableView;
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
void Server::setRowTable(QString name, QVariant command)
{
    mutex.lock();
    if(name.isNull() || name.isEmpty())
        return;

    ModelTable *tableModel = new ModelTable(this);
    HostsCommand strCOmmand;
    strCOmmand.nameHost = name;
    strCOmmand.nameCommand = command.toString();
    commandHost.append(strCOmmand);

    tableModel->setRow(commandHost);
    clientStatus->setModel(tableModel);
    mutex.unlock();
}


