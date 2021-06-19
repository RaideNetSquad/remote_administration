#include "serverObjectLogic.h"

ServerObjectLogic::ServerObjectLogic(const QString &filePathRoles,
                                     const QString &filePathTimeDo,
                                     QObject *parent)
    : QTcpServer(parent)
    , roleMap(new RoleMap){
    this->filePathRoles = splitPathFile(filePathRoles);
    this->filePathTimeDo = splitPathFile(filePathTimeDo);
    connect(roleMap, &RoleMap::newError,
            this, &ServerObjectLogic::slot_newError);
    connect(this, &ServerObjectLogic::addConnection,
            this, &ServerObjectLogic::slot_addConnection);
    set_RolesToMap();
    get_DateTimeSetupInstructions();

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slot_TimerUpdate()));
    timer->start(1000);
};
void ServerObjectLogic::set_RolesToMap(){
    //Установить дефолтные значения словаря (роль - сокет)
    //TODO update file path !!!!!!!!!!!!!!!!!!!!!!!!

    //QString filePath = "/home/[username]/Desktop/transmit/resource/Server/rules.json";
    const QJsonDocument jsonDocument = get_JsonDocument(filePathRoles);
    if(jsonDocument.isEmpty()){
        emit newError((QString("Сервер - Не могу открыть файл %1").arg(filePathRoles)));
    }

    //хранилище ролей
    roleMap->set_Map(jsonDocument);
};

void ServerObjectLogic::get_DateTimeSetupInstructions(){
    //получить время выполнения файла с инструкциями клиентов и сам файл

    //QFile f(QDir::currentPath() + "/json_inst/time_do.json");
    //QString path_f = QFileDialog::getOpenFileName(0, "Выберите основной json файл (time_do.json)", "", "*.json");
    //QString filePath = "/home/[userName]/Desktop/transmit/resource/Server/time_do.json";
    parserFileTimeDo(filePathTimeDo);
};

void ServerObjectLogic::incomingConnection(qintptr socketDescriptor){
    emit addConnection((int)socketDescriptor);
    //все подключения обрабатываю здесь
    //для каждого подключения отдельный поток
    QThread *threadClient = new QThread(this);

    ClientObjectLogic *client = new ClientObjectLogic(socketDescriptor);
    connect(client, &ClientObjectLogic::finished, client, &ClientObjectLogic::deleteLater, Qt::QueuedConnection);
    connect(this, &ServerObjectLogic::parserFileWithInstructionsRole,
            client, &ClientObjectLogic::slot_parserFileWithInstructionsRole, Qt::DirectConnection);
    connect(threadClient, &QThread::finished,
                threadClient, &QThread::deleteLater);

    connect(client, &ClientObjectLogic::newMessage,
            this, &ServerObjectLogic::slot_newMessageClient, Qt::QueuedConnection);

    connect(client, &ClientObjectLogic::checkRole,
            this, &ServerObjectLogic::slot_CheckRole,  Qt::QueuedConnection);
    connect(client, &ClientObjectLogic::delClientObj,
            this, &ServerObjectLogic::slot_deleteFromSet, Qt::QueuedConnection);
    connect(this, &ServerObjectLogic::disconnectWithClient,
            client, &ClientObjectLogic::slot_disconnectWithClient, Qt::DirectConnection);
    connect(client, &ClientObjectLogic::lastCommandRole,
            this, &ServerObjectLogic::slot_StartTimer, Qt::QueuedConnection);
    client->moveToThread(threadClient);
    threadClient->start();
};

QString ServerObjectLogic::splitPathFile(const QString& path){
    if(path.split("/")[0] == ".")
    {
        return QString("%1/%2").arg(QDir::currentPath()).arg(path.split("./")[1]);
    }
    return path;
};

ServerObjectLogic::~ServerObjectLogic(){
    delete this;
}
