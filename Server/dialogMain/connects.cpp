/*
    * Сигнально-слотовые соединения у диалога
*/
#include "dialog.h"

void Dialog::connects_dialog()
{
    //если сигнал от объекта сервера установить строку в таблице
    //устанавливаю строку
    connect(serv, SIGNAL(setRowTable(QString, QString)),
            this, SLOT(slot_setRowTable(QString, QString)));

    //если получаю из формы отправки файлов
    //файлы, передаю их объекту логике сервера
    connect(send, SIGNAL(sendFileFromForm(QString, int)),
            serv, SLOT(slot_send_file(QString, int)));

    //если подключился новый клиент
    //то отображаю его в форме отправки файлов
    connect(serv, SIGNAL(new_client_to_sendForm(QString, int)),
            send, SLOT(new_client_set(QString, int)));

    connect(this, &Dialog::closeUi,
            this, &Dialog::closeApp);
}
