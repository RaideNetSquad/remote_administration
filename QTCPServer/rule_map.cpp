/*
 * JSON Формат
 * {
 *  "Роль 1":"",
 *  "Роль н":"Сокет н", - при подключении клиента с ролями
 * }
*/
#include "rule_map.h"

Rule_Map::Rule_Map(QObject* parent) : QObject(parent)
{

}
QString Rule_Map::return_Rule_By_Id(const qintptr &id)
{
    for(auto it = rules.begin(); it != rules.end();)
    {
        if(it.value() == id)
        {
            return it.key();
        }
    }
    return "";
}
int Rule_Map::get_Rule_Id(const QString& rule, const qintptr &id)
{
    for (auto it = this->rules.begin(); it != this->rules.end();){
        if(it.value() == id){
             return 1;
        }
        if(it.key() == rule){
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

void Rule_Map::set_Id_By_Rule(const QString &rule,const qintptr &id)
{
    //добавляю клиента к роли
    for (auto it = this->rules.begin(); it != this->rules.end();)
        if (it.key() == rule)
            it.value() = id;
        else
            ++it;
};

void Rule_Map::delete_Client_Id(const qintptr& id){
    //удаляю клиента из выполнения роли
    for (auto it = this->rules.begin(); it != this->rules.end();)
        if (it.value() == id)
            it.value() = 0;
        else
            ++it;
    qDebug() << rules;
};

void Rule_Map::set_Map(const QJsonDocument &jsonDoc)
{
    QJsonObject jsonObject = jsonDoc.object();

    QJsonObject::iterator iter = jsonObject.begin();

    for(; iter != jsonObject.end(); ++iter)
    {
        //добавляю новые роли в словарь
        rules.insert(iter.key(), iter.value().toInt());
    }
}

int Rule_Map::get_Id_Rule(const QString& rule)
{
    for (auto it = this->rules.begin(); it != this->rules.end(); ++it){
        if(rule == it.key())
        {
            return it.value();
        }
    }
    return 0;
}
