#include "mainwindow.h"

QString MainWindow::split_Path_File(QString role_File_Path)
{
    if(role_File_Path.split("/")[0] == ".")
    {
        role_File_Path = QString("%1/%2").arg(QDir::currentPath()).arg(role_File_Path.split("./")[1]);
    }
    return role_File_Path;
}
