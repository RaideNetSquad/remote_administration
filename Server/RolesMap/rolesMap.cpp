#include "rolesMap.h"

RoleMap::RoleMap(QObject* parent) : QObject(parent){};

void RoleMap::set_Map(const QJsonDocument &jsonDoc)
{
    QJsonObject jsonObject = jsonDoc.object();
    if(jsonObject.isEmpty())
        emit newError("Сервер - в файле, в котором находятся роли пустые данные или неверный формат записи ролей");
    QJsonObject::iterator iter = jsonObject.begin();

    for(; iter != jsonObject.end(); ++iter)
    {
        //добавляю новые роли в словарь
        roles.insert(iter.key(), iter.value().toInt());
    }
}

int RoleMap::get_RoleId(const QString& role, const qintptr &id)
{
    QMutexLocker ml(&mutex);
    for (auto it = this->roles.begin(); it != this->roles.end();){
        if(it.value() == id){
             return 1;
        }
        if(it.key() == role){
            if(it.value() == 0)
            {
                it.value() = id;
                return 0;
            }else if(it.value() == id){
                return 1;
            }else{
                return -1;
            }
        }
        else{
            ++it;
        }
    }
    return -1;
};

QString RoleMap::get_RoleById(const qintptr &id)
{
    QMutexLocker ml(&mutex);
    for(auto it = roles.begin(); it != roles.end();)
    {
        if(it.value() == id)
        {
            return it.key();
        }
    }
    return "";
}

int RoleMap::get_IdRole(const QString& role)
{
    QMutexLocker ml(&mutex);
    for (auto it = this->roles.begin(); it != this->roles.end(); ++it){
        if(role == it.key())
        {
            return it.value();
        }
    }
    return 0;
}

void RoleMap::delete_RoleId(const qintptr& id){
    QMutexLocker ml(&mutex);
    //удаляю клиента из роли
    for (auto it = this->roles.begin(); it != this->roles.end();)
        if (it.value() == id)
            it.value() = 0;
        else
            ++it;
};
