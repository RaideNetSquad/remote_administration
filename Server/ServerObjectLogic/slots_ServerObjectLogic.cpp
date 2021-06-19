#include "serverObjectLogic.h"

void ServerObjectLogic::slot_newMessageClient(const QString &message){
    emit newMessage(message);
}

void ServerObjectLogic::slot_newError(const QString &message){
    emit newError(message);
}

void ServerObjectLogic::slot_TimerUpdate(){
    currentDateTime = QDateTime::currentDateTime();
    qDebug() << "slot_TimerUpdate " << currentDateTime.secsTo(dateTimeSetupInstructions);
    if(currentDateTime.secsTo(dateTimeSetupInstructions) == 0){
        emit newMessage("Сервер - пришло время выполнять инструкции");
        if(connectionSet.size() == 0){
            emit newMessage("Никто из ролей не подключился, инструкции не могут быть выполненны!");
            return;
        }
        //will be instructions parse and complete
        timer->stop();
        //TODO выполнить инструкции
        parserFileWithRolesInstructions();
    }
    get_DateTimeSetupInstructions();

};
void ServerObjectLogic::slot_StartTimer(){
    qDebug() << "START timer";
    timer->start(1000);
}
void ServerObjectLogic::slot_CheckRole(const QString &role, const int &desc){
    int valid_Id_Rule = roleMap->get_RoleId(role, desc);
    QString errorMessage;
    qDebug() << "slot_CheckRole";
    if(valid_Id_Rule != -1){
        //если роль найдена и она свободна
        if(valid_Id_Rule != 1){
            emit newMessage(QString("Сокет %1 имеет роль <%2> ").arg(desc).arg(role));
        }else{
            qDebug() << role << desc << " get role";
            errorMessage = QString("Роль %1 занята для клиента %2").arg(role).arg(desc);
            //если роль не найденна или она занята
            emit disconnectWithClient(desc, errorMessage);
            emit newMessage(errorMessage);
            emit deleteFromSet(desc);
        }
    }else{
        errorMessage = QString("Роль <(%1)> не найдена (%2) - клиента").arg(role).arg(desc);
        emit disconnectWithClient(desc, errorMessage);
        emit newMessage(errorMessage);
        emit deleteFromSet(desc);
    }
}
void ServerObjectLogic::slot_deleteFromSet(int currentDesc){
    roleMap->delete_RoleId(currentDesc);
    foreach(int desc , connectionSet){
        if(desc == currentDesc)
            connectionSet.remove(desc);
    }
}

void ServerObjectLogic::slot_addConnection(int desc){
    connectionSet.insert(desc);
}
