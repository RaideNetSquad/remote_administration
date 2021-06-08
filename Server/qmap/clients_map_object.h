/*
    * Clients_Map_Object класс для работы и хранения
    * словаря клиентов, где ключ имя клиента, а значение его идентификатор
    * --------------------------------------------------------------------
    * clear_map - очищение словаря
    * add_client - добавление нового клиента
    * delete_client_with_id - удаление клиент по идентификатору
    * delete_client_with_name - удаление клиента по имени
    * get_client_id - получить идентификатор клиента по имени
    * get_client_name - получить имя клиента по идентификатору
*/
#pragma once

#include <QObject>
#include <QMap>
#include <QString>
#include <QDebug>

class Clients_Map_Object : public QObject
{
    Q_OBJECT
public:
    Clients_Map_Object(QObject* parent = nullptr);
private:
    QMap<QString, int> clients_map;

public:
    void clear_map();
    void add_client(const QString&, const int&);

    void delete_client_with_id(int&);
    void delete_client_with_name(QString&);

    int get_client_id(QString&);
    QString get_client_name(int&);

    int get_id();

};

