#include <QString>
#include <QMessageBox>

void infoBox(QString head, QString textInfo)
{
    QMessageBox* message = new QMessageBox();

    message->setWindowTitle(head);

    message->setInformativeText(textInfo);

    message->setIcon(QMessageBox::Information);
    message->setDefaultButton(QMessageBox::Ok);
    int n = message->exec();
    if (n == QMessageBox::Ok)
    {
      delete message;
    }
}
