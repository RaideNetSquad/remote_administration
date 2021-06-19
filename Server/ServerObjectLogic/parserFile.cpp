#include "serverObjectLogic.h"

void ServerObjectLogic::parserFileTimeDo(const QString &path){
    //парсер файла со временем исполнения всех инструкций
    QJsonDocument dc_Js = get_JsonDocument(path);
    QJsonObject obj_Js = dc_Js.object();

    dateTimeSetupInstructions = QDateTime::fromString(obj_Js.begin().key(),"dd.MM.yyyy HH:mm:ss");
    //коннектор ролей и их инструкций
    pathInstructionsRoles = obj_Js.begin().value().toString();

    if(dateTimeSetupInstructions.isNull() || !dateTimeSetupInstructions.isValid())
    {
        emit newError(QString("Проверьте правильность даты и времени (dd.MM.yyyy HH:mm:ss) в файле %1")
                      .arg(path));

    }else if(pathInstructionsRoles.isEmpty()){
        emit newError(QString("Немогу прочитать ссылку на инструкции в файле %1")
                      .arg(path));
    };
};

void ServerObjectLogic::parserFileWithRolesInstructions(){
    qDebug() << "parserFileWithRolesInstructions";
    //path_Instructions_Roles - свойство
    QJsonDocument rFD = get_JsonDocument(pathInstructionsRoles);
    qDebug() << rFD;
    QJsonArray arrRoles = rFD.array();
    qDebug() << arrRoles;
    QJsonObject currentRoleObject;

    QString roleValue;

    QString pathFileInstructions;

    int roleSocketIdClient;

    for(int i = 0; i < arrRoles.size(); ++i)
    {
        currentRoleObject = arrRoles[i].toObject();
        qDebug() << currentRoleObject;
        roleValue = currentRoleObject.keys()[0];
        roleSocketIdClient = roleMap->get_IdRole(roleValue);
        qDebug() << roleSocketIdClient << roleValue;
        if(roleSocketIdClient != 0)
        {
            pathFileInstructions = currentRoleObject.value(roleValue).toString();
            pathFileInstructions = splitPathFile(pathFileInstructions);
            qDebug() << roleSocketIdClient << roleValue << pathFileInstructions;

            QString lastRole = arrRoles[arrRoles.size()-1].toObject().keys()[0];
            qDebug() << "LAST ROLE " << lastRole;
            //парсинг файла с инструкциями роли
            emit parserFileWithInstructionsRole(roleSocketIdClient, roleValue, pathFileInstructions, lastRole);
        }
    }
    emit newMessage("Все инструкции отправленны!");
}
