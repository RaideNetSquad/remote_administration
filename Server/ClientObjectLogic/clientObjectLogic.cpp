#include "clientObjectLogic.h"

ClientObjectLogic::ClientObjectLogic(const qintptr& socketDesc,QObject* parent): QObject(parent)
        , clientSocket(new QTcpSocket){
    clientSocket->setSocketDescriptor(socketDesc);

    connect(clientSocket, &QTcpSocket::readyRead,
            this, &ClientObjectLogic::slot_ReadyRead, Qt::QueuedConnection);
    connect(clientSocket, &QTcpSocket::disconnected,
            this, &ClientObjectLogic::slot_discardSocket);
    connect(this, &ClientObjectLogic::disconnectClient,
            this, &ClientObjectLogic::slot_discardSocket);
    send_Command("SEND_ROLE", "");
}

QJsonDocument ClientObjectLogic::get_JsonDocument(const QString &path){
    QFile file(path);

    if(file.open(QIODevice::ReadOnly))
    {
        // Считываем весь файл
        QByteArray readJSON = file.readAll();
        // Создаём QJsonDocument
        QJsonDocument jsonDocument(QJsonDocument::fromJson(readJSON));
        file.close();
        return jsonDocument;

    }else{
        emit newMessage(QString("Не могу открыть файл %1").arg(path));
        return QJsonDocument();
    }
};


QString ClientObjectLogic::splitPathFile(const QString& path){
    if(path.split("/")[0] == ".")
    {
        return QString("%1/%2").arg(QDir::currentPath()).arg(path.split("./")[1]);
    }
    return path;
};


ClientObjectLogic::~ClientObjectLogic(){
};
