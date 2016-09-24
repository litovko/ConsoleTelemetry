#include "ctcpserver.h"
#include <QDebug>
//#include <QtNetwork/qhostaddress.h>

//cTCPServer::cTCPServer(QObject *parent) : QObject(parent)
//{

//}

cTCPServer::cTCPServer()
{
    //    connect(&m_tcpServer, SIGNAL(connected()),this, SLOT(clientConnected())); // Клиент приконнектилася к указанному адресу по указанному порту.
    //    connect(&m_tcpServer, SIGNAL(disconnected()),this, SLOT(clientDisconnected())); // Клиент отвалился
    m_tcpServer = new QTcpServer(this);
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(serverConnection()));
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    m_timer.start(5000);
    if (m_tcpServer->listen(QHostAddress::LocalHost, 9999))
        {
            qDebug()<<"LISTEN:"<<m_tcpServer->errorString();
        }
    else qDebug()<<"Some error:"<<m_tcpServer->errorString();

}

void cTCPServer::serverConnection()
{
    m_connected=true;
    qDebug()<<"Connected";
    m_tcpServer->pauseAccepting();
    m_clientConnection=m_tcpServer->nextPendingConnection();
    connect(m_clientConnection, SIGNAL(disconnected()),this, SLOT(clientDisconnected()));
}


void cTCPServer::timerSlot()
{
    QByteArray data;
    if(!m_connected) return;
    /*
    Передача цифровых датчиков
    №	Содержание	Описание	Примечание
    байта	НЕХ
    1	55	Стартовый
    2	31	Код
    3	хх	Байт 1	Содержание
    4	хх	Байт 2	байтов на листе
    5	хх	Байт 3	 "Протокол"
    6	хх	Байт 4	строки
    7	хх	Байт 5	 284 - 295
    8	хх	Байт 6
    9	хх	Байт 7
    10	хх	Байт 8
    11	хх	Байт 9
    12	00	Резерв
    13	00	Резерв
    14	00	Резерв
    15	CRC16	Контрольная
    16	CRC16	сумма
    */
    data.append(0x55);
    data.append(0x31);
    data.append(0x03);
    data.append(0x0E);
    data.append(char(0x00));
    data.append(0xFE);
    data.append(0xFF);
    data.append(0xF1);
    data.append(0xFF);
    data.append(0x08);
    data.append(0x09);
    data.append(0x0A);
    data.append(0x0B);
    data.append(0x0C);


    int crc = qChecksum(data.data(), data.length());
    qDebug()<<"Tick:crc:"<<crc<<"data:"<<data.toHex();
    m_clientConnection->write(data.append(crc).append(crc/256).append("qqq"));
    qDebug()<<data.toHex();
    /*


    Передача аналоговых датчиков
    №	Содержание	Описание	Примечание
    байта	НЕХ
    1	55	Стартовый
    2	32	Код
    3	хх	Байт 1	Содержание
    4	хх	Байт 2	байтов на листе
    5	хх	Байт 3	 "Протокол"
    6	хх	Байт 4	строки
    7	хх	Байт 5	 360 - 370
    8	хх	Байт 6
    9	хх	Байт 7
    10	хх	Байт 8
    11	хх	Байт 9
    12	хх	Байт 10
    13	хх	Байт 11
    14	хх	Байт 12
    15	хх	Байт 13
    16	хх	Байт 14
    17	хх	Байт 15
    18	00	Резерв
    19	CRC16	Контрольная
    20	CRC16	сумма
    */
    data.clear();
    data.append(0x55);
    data.append(0x32);
    data.append(0x01);
    data.append(0x02);
    data.append(0x03);
    data.append(0x04);
    data.append(0x05);
    data.append(0x06);
    data.append(0x07);
    data.append(0x08);
    data.append(0x09);
    data.append(0x0A);\
    data.append(0x0B);
    data.append(0x0C);
    data.append(0x0D);\
    data.append(0x0E);
    data.append(0x0F);
    data.append(0x10);

    crc = qChecksum(data.data(), data.length());
    qDebug()<<"Tick:crc:"<<crc<<"data:"<<data.toHex();
    m_clientConnection->write(data.append(crc).append(crc/256).append("xxx"));
    qDebug()<<data.toHex();
}

void cTCPServer::clientDisconnected()
{
    qDebug()<<"Disconnected";
    m_clientConnection->deleteLater();
    m_connected=false;
    m_tcpServer->resumeAccepting();
}
