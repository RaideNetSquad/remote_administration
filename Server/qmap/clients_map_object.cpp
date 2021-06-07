#include "clients_map_object.h"

Clients_Map_Object::Clients_Map_Object(QObject* parent) : QObject(parent)
{

}

void Clients_Map_Object::clear_map(){
    this->clients_map.clear();
};

void Clients_Map_Object::add_client(QString& nameHost, quint16& idHost){
    this->clients_map.insert(nameHost, idHost);
};

void Clients_Map_Object::delete_client_with_id(quint16& idClient){
    for (auto it = this->clients_map.begin(); it != this->clients_map.end();)
        if (it.value() == idClient)
            it = this->clients_map.erase(it);
        else
            ++it;
};
void Clients_Map_Object::delete_client_with_name(QString& nameClient){
    for (auto it = this->clients_map.begin(); it != this->clients_map.end();)
        if (it.key() == nameClient)
            it = this->clients_map.erase(it);
        else
            ++it;
};

quint16 Clients_Map_Object::get_client_id(QString& nameClient)
{
    for (auto it = this->clients_map.begin(); it != this->clients_map.end();)
        if (it.key() == nameClient)
            return it.value();
        else
            ++it;
};
QString Clients_Map_Object::get_client_name(quint16& idClient)
{
    for (auto it = this->clients_map.begin(); it != this->clients_map.end();)
        if (it.key() == idClient)
            return it.key();
        else
            ++it;
};

quint16 Clients_Map_Object::get_id()
{
    auto it = this->clients_map.begin();
    for (; it != this->clients_map.end();)
            ++it;
    qDebug() << it.value();
    return it.value() + 1;
}
