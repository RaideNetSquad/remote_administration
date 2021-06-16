#include "mainwindow.h"

QString MainWindow::split_Path_File(QString rule_File_Path)
{
    if(rule_File_Path.split("/")[0] == ".")
    {
        rule_File_Path = QString("%1/%2").arg(QDir::currentPath()).arg(rule_File_Path.split("./")[1]);
    }
    return rule_File_Path;
}

QString MainWindow::get_FileInstructions_By_Descr(int sock_Descr)
{
    QString rule = rule_map->return_Rule_By_Id(sock_Descr);
    if(rule == "")
    {
        emit newMessage(QString("Неизвесный дескриптор сокета"));
        return "";
    }

    QJsonDocument json_Doc_Rule_File = get_JsonDocument(path_Instructions_Roles);

    if(!json_Doc_Rule_File.isEmpty()){
        QJsonArray arr_Roles = json_Doc_Rule_File.array();

        QJsonObject ob_Role;

        for(int i = 0; i < arr_Roles.size(); ++i)
        {
            ob_Role = arr_Roles[i].toObject();
            if(ob_Role.keys()[0] == rule)
            {
                QString rule_File_Path = ob_Role.value(rule).toString();
                rule_File_Path = split_Path_File(rule_File_Path);
                qDebug() << rule_File_Path << " Путь к инструкциям файла";
                return rule_File_Path;
            }
        }
    }

}


QJsonDocument MainWindow::get_JsonDocument(QString f)
{
    qDebug() << "get_JsonDocument [6]";
    QFile file(f);

    if(file.open(QIODevice::ReadOnly))
    {
        // Считываем весь файл
        QByteArray readJSON = file.readAll();
        // Создаём QJsonDocument
        QJsonDocument jsonDocument(QJsonDocument::fromJson(readJSON));
        file.close();
        return jsonDocument;

    }else{
        emit newMessage((QString("Не могу открыть файл %1").arg(path_Instructions_Roles)));
        return QJsonDocument();
    }
}
