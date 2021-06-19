#pragma once

#include <QtWidgets>
#include <QTcpServer>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>

#include "RolesMap/rolesMap.h"
#include "ClientObjectLogic/clientObjectLogic.h"

class ServerObjectLogic : public QTcpServer
{
     Q_OBJECT
public:
    explicit ServerObjectLogic(const QString &filePathRoles,
                               const QString &filePathTimeDo,
                               QObject *parent = 0);
    ~ServerObjectLogic();
private:
    QMutex mutex;
    QDateTime dateTimeSetupInstructions;
    QDateTime currentDateTime;
    QString pathInstructionsRoles;
    RoleMap *roleMap;
    QTimer *timer;
    int onceConnectYes;
    QSet<int> connectionSet;
    QString filePathRoles;
    QString filePathTimeDo;
private:
    void incomingConnection(qintptr socketDescriptor) override;
    //Getters
    void get_DateTimeSetupInstructions();
    //Setters
    void set_RolesToMap();
    //Json
    QJsonDocument get_JsonDocument(const QString &path);
    //Parser
    void parserFileTimeDo(const QString &path);
    void parserFileWithRolesInstructions();
    //FileInfo
    QString splitPathFile(const QString&);
signals:
    void newMessage(const QString &message);
    void newError(const QString &message);
    void deleteFromSet(int desc);
    void parserFileWithInstructionsRole(const int&,
                                        const QString&,
                                        const QString&,
                                        const QString&);
    void errorSend(const QString&);
    void disconnectWithClient(const qintptr&, const QString&);
    void addConnection(int);
private slots:
    void slot_addConnection(int);
    void slot_TimerUpdate();
    void slot_newMessageClient(const QString &message);
    void slot_newError(const QString &message);
    void slot_CheckRole(const QString &role, const int &desc);
    void slot_deleteFromSet(int sock);
    void slot_StartTimer();
};

