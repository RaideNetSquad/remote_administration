#include "send.h"
#include "ui_sendFile.h"

#include <QFileDialog>

//при выборе хотяб одного клиента
void SendForm::on_listWidget_itemClicked(QListWidgetItem *item)
{

    formSender_ui->send_file_btn->setEnabled(true);
}

//отправить файлы при клике на кнопку
void SendForm::on_send_file_btn_clicked()
{
    //получаю список всех клиентов по которым нажали
    QList<QListWidgetItem*> it = formSender_ui->listWidget->selectedItems();
    //список строк из имен клиентов
    QList<QString> us;
    for(int user = 0; user < users.size(); ++user)
    {
        us.append(it[user]->text());
    }

    //открываю диалоговое окно с выбором файлов
    QStringList tt = QFileDialog::getOpenFileNames(0, "Open Dialog", "", "*.json");
    for(int i = 0; i < tt.size(); ++i)
    {
        for(int user = 0; user < users.size(); ++user)
        {
            //если пользователь найден в списке выборки
            if(us.indexOf(users[user].name))
            {
                //отправляю путь файла + дескриптор
                emit sendFileFromForm(tt[i], users[user].sock_Descriptor);
            }
        }
    }
}
