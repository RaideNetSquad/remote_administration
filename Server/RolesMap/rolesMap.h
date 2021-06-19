#pragma once

#include <QObject>
#include <QMap>
#include <QFile>
#include <QAbstractSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMutex>
#include <QMutexLocker>

class RoleMap : public QObject
{
    Q_OBJECT
public:
    explicit RoleMap(QObject* parent = nullptr);
private:
    QMap<QString, int> roles;
public:
    void set_Map(const QJsonDocument&);
    void set_RoleId(const QString &rule, const qintptr& id);
    QString get_RoleById(const qintptr &id);
    int get_RoleId(const QString& rule, const qintptr &id);
    int get_IdRole(const QString&);
    void delete_RoleId(const qintptr& id);
private:
    QMutex mutex;
signals:
    void newError(const QString &text);
};
