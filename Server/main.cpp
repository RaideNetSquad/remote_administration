/*
    * Приложение сервера
*/

#include "dialog/dialog.h"
#include <QtCore>

#include <stdlib.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog window;
    window.show();
    return a.exec();
}
