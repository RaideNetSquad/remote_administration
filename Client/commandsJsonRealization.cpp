#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <QFile>
#include <QTextCodec>
#include <QFileDialog>
#include <QProcess>

/*
//Команды, которые может выполнить удаленно комп
void ClientWindow::create_file(QString &path)
{
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    file.close();

    emit complete_signal("Создаю файл", path);
    MessageInfo("Клиент", "Создал файл " + path);
}

void ClientWindow::write_to_file(QString &text, QString &path)
{
    qDebug() << path;
    QFile file(path);
    file.open(QIODevice::Append);
    QTextStream in(&file);
    in.setCodec(QTextCodec::codecForName("UTF-8"));
    in << text << "\n";
    file.close();

    emit complete_signal("Записал в файл", path + " текст " + text);
    MessageInfo("Клиент", "Записал в файл " + path);
}*/

/*void ClientWindow::open_file(QString &path)
{
exp .*/ /*
    QString f = QFileDialog::getOpenFileName(this, tr("Open File"),path, path.remove(QRegExp()));
    QFile file(f);
    emit complete_signal("Открываю файл", path);
    MessageInfo("Клиент", "Открыл файл " + path);
}

void ClientWindow::delete_file(QString &path)
{

    qDebug() << path;
    QFile file(path);
    file.remove();
    emit complete_signal("Удаляю файл", path);
    MessageInfo("Клиент", "Удалил файл " + path);
}

void ClientWindow::copy_file(QString &pathFrom, QString &pathTo)
{
    QString command = pathFrom + " в " + pathTo;
    emit complete_signal("Копирую файл ", command);
    qDebug() << command;
    QFile::copy(pathFrom, pathTo);
    MessageInfo("Копирую файл ", command);
}

void ClientWindow::complite_file(QString &path)
{
    qDebug() << "Complete";
    QProcess *newProcess = new QProcess();
    newProcess->start(path);
    newProcess->waitForStarted();
    MessageInfo("Выполнил программу", path);
    emit complete_signal("Выполнил программу", path);
}
*/
