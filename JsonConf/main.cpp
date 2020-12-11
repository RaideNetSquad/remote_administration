#include "network.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Network net;
    net.show();
    return a.exec();
}
