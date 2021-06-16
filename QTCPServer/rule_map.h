#ifndef RULE_MAP_H
#define RULE_MAP_H

#include <QObject>
#include <QMap>
#include <QFile>
#include <QAbstractSocket>
#include <QJsonDocument>
#include <QJsonObject>

class Rule_Map : public QObject
{
    Q_OBJECT
public:
    explicit Rule_Map(QObject* parent = nullptr);
private:
    QMap<QString, int> rules;

public:
    void set_Map(const QJsonDocument&);
    void set_Id_By_Rule(const QString &rule, const qintptr& id);
    int get_Rule_Id(const QString& rule, const qintptr &id);
    int get_Id_Rule(const QString&);
    void delete_Client_Id(const qintptr& id);
    QString return_Rule_By_Id(const qintptr &id);

};

#endif // RULE_MAP_H
