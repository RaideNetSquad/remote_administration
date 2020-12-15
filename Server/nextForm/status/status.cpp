#include "status.h"

#include "ui_status.h"

StatusForm::StatusForm(QWidget* parent) :
    QMainWindow(parent), formStatus_ui(new Ui::Status())
{
    mutex = new QMutex;
    formStatus_ui->setupUi(this);
    qDebug() << "Set table";
    //установка таблицы
    setTable(formStatus_ui);
}
