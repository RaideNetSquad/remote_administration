#include "dialog.h"

//обработчик ошибок приполучении хоста или порта
void Dialog::checkErrorGettingHost()
{
    if(!getHost()){
        QMessageBox::critical(0, tr("Err Server"),
                                      tr("Unable to start the server: %1.")
                                      .arg(serv->errorString()));
        emit closeUi();
        return;
    }
}
