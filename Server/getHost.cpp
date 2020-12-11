/*
    * Получаю адрес сервера и порт
*/
#include "dialog.h"

bool Dialog::getHost()
{
    QString ipAddress;
    QList<QHostAddress> listAdd = QNetworkInterface::allAddresses();

    for(int i = 0; i < listAdd.size(); ++i)
    {
        if(listAdd.at(i) != QHostAddress::LocalHost && listAdd.at(i).toIPv4Address())
        {

            host = listAdd.at(i);
            ipAddress = "Not empty";
            break;
        }
    }
    if(ipAddress.isEmpty()){
        host = QHostAddress(QHostAddress::LocalHost).toString();
    }
    for(int i = 1; i < 65535; ++i)
    {
        if(serv->listen(host, i))
        {
            port = i;
            return true;
        }

    }
    return false;
}
