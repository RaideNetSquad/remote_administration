#include "serverObjectLogic.h"

QJsonDocument ServerObjectLogic::get_JsonDocument(const QString &path)
{
    QMutexLocker locker(&mutex);
    QFile file(path);

    if(file.open(QIODevice::ReadOnly)){
        // Считывай весь файл
        QByteArray readJSON = file.readAll();

        QJsonDocument jsonDocument(QJsonDocument::fromJson(readJSON));
        file.close();
        return jsonDocument;

    }
    return QJsonDocument();
};
