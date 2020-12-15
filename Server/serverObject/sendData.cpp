#include "server.h"

//метод отправки данных
void Server::SendDataPack(Packet pack, int socketDescriptor)
{
    QTcpSocket* send = new QTcpSocket();
    send->setSocketDescriptor(socketDescriptor);

    QByteArray arr;
    QDataStream out(&arr, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << pack;
    send->write(arr);
    send->waitForBytesWritten();

    if(pack.getNameCommand() == "write_to_file")
    {
        arr.clear();
        qDebug() << "Write";
        //открыть файл и записать данные в сокет
        QString path = pack.getTextCommand();

        QFile file(path);
        if(!file.open(QIODevice::ReadOnly))
        {
            return;
        };
        int countByteStart = 0;
        QByteArray bytes;
        for(;!file.atEnd();) {
            arr.clear();
            countByteStart += 4;
            bytes = file.read(4);
            pack.setBytes(bytes);
            out << pack;
            send->write(arr);
            file.seek(countByteStart);
        }

    }


}

