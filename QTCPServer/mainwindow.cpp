#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->insert("127.0.0.1");
    ui->lineEdit_2->insert("8080");

    m_server = new QTcpServer();
    rule_map = new Rule_Map();
    connect(this, &MainWindow::newMessage,
            this, &MainWindow::displayMessage);
    current_DateTime = QDateTime::currentDateTime().toString();
    qDebug() << "MainWindow [1]";
    //получать роли из файла и записать их в массив
    set_Roles_To_Map();
    //получаю дату и время начала выполнения инструкций
    set_Time_Complite_Instructions();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slot_Timer_Update()));
    timer->start(1000);
}
//[0]
void MainWindow::set_Roles_To_Map()
{
    qDebug() << "set_Roles_To_Map [2]";
    //TODO update file path !!!!!!!!!!!!!!!!!!!!!!!!
    QString filePath = QFileDialog::getOpenFileName(this, ("Выберите файл с ролями (rules.json)"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), ("File (*.json)"));
    //QString filePath = "/home/netkiller/Desktop/QTcpSocket-master/build-QTCPServer-Desktop_Qt_5_15_0_GCC_64bit-Debug/json_inst/rules.json";
    //QFile rules_json(QDir::currentPath() + "/json_inst/rules.json");
    emit newMessage("Файл (rules.json) с ролями читается...");
    QJsonDocument jsonDocument = get_JsonDocument(filePath);
    //хранилище ролей
    rule_map->set_Map(jsonDocument);
}

//[1]
void MainWindow::set_Time_Complite_Instructions()
{
    qDebug() << "set_Roles_To_Map [3]";
    /*
     * Читать файл со временем исполнения инструкций каждой роли
     * Сравнить даты с текущей, и так пока даты не будут равны
     * Когда даты равны, открыть файлы с инструкциями для каждой роли
     * передать команды и данные клиентам
    */

    //QFile f(QDir::currentPath() + "/json_inst/time_do.json");
    QString path_f = QFileDialog::getOpenFileName(0, "Выберите файл содержащий таймер выполнения инструкций и ссылку на файл с инструкциями (time_do.json)", "", "*.json");
    //QString path_f = "/home/netkiller/Desktop/QTcpSocket-master/build-QTCPServer-Desktop_Qt_5_15_0_GCC_64bit-Debug/json_inst/time_do.json";
    parser_TimeDo(path_f);
};

void MainWindow::appendToSocketList(QTcpSocket* socket)
{
    connection_set.insert(socket);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::slot_readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::slot_discardSocket);
    connect(socket, &QAbstractSocket::errorOccurred, this, &MainWindow::slot_displayError);

    emit newMessage(QString("Инфо :: Клиент с сокетом:%1 подключился").arg(socket->socketDescriptor()));
    //send_rule(rule);
    send_Command(socket, "SEND_RULE", "");
}

void MainWindow::displayMessage(const QString& str)
{
    ui->textBrowser_receivedMessages->append(str);
}


void MainWindow::disconnect(QTcpSocket *socket, const QString &str)
{
    emit newMessage(QString(str));
    //удаление клиента из роли
    rule_map->delete_Client_Id(socket->socketDescriptor());

    //разрыв соединения с клиентом
    QSet<QTcpSocket*>::iterator it = connection_set.find(socket);
    if (it != connection_set.end()){
        connection_set.remove(*it);
    }
    socket->deleteLater();

}


MainWindow::~MainWindow()
{
    foreach (QTcpSocket* socket, connection_set)
    {
        socket->close();
        socket->deleteLater();
    }

    m_server->close();
    m_server->deleteLater();

    delete ui;
}
