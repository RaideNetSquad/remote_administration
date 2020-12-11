#include "ui_jsonsender.h"

#include "jsonsender.h"
#include "network.h"

#include <QWidget>
#include <QMessageBox>

void infoBox (QString, QString);

JsonSender::JsonSender(QWidget *parent) : Network(parent){};
