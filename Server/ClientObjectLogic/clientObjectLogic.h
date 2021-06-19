#pragma once

#include <QtWidgets>
#include <QTcpSocket>
#include <QMutex>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class ClientObjectLogic : public QObject
{
    Q_OBJECT
public:
    explicit ClientObjectLogic(const qintptr& socketDesc, QObject* parent = 0);
    ~ClientObjectLogic();
private:
    QTcpSocket *clientSocket;
    QString pathInstructionOfClient;
    QString role;
    QString lastRole;
    QString lastCommand;
private:
    void parserFileWithInstructionsRole(const int &socketId,
                                        const QString &roleValue,
                                        const QString &pathFileInstructions);
    //Json
    QJsonDocument get_JsonDocument(const QString &path);
    //Job with commands
    void commandsConnector(const QString& keyCurrentComand,
                            const QJsonObject &currentCommandObject,
                            const QString& role);

    void commandsConnector(const QString& keyCurrentComand,
                            const QString &currentCommandStr,
                            const QString& role);
    //FileInfo
    QString splitPathFile(const QString&);
    //Senders
    void send_Command(const QString&,const QString&);
    void send_Attachment(const QString&,const QString&);

    void checkFileType(const QString &fileType,
                                          const qintptr &sockDesc,
                                          const QString &header,
                                          const QByteArray &buffer);

signals:
    void finished();
    void newMessage(const QString&);
    void checkRole(const QString&, const int&);
    void delClientObj(int);
    void lastCommandRole();
    void disconnectClient();
public slots:
    void slot_parserFileWithInstructionsRole(const int &,
                                             const QString&,
                                             const QString&,
                                             const QString&);
    void slot_ReadyRead();
    void slot_disconnectWithClient(const qintptr&, const QString&);
    void slot_discardSocket();
};
