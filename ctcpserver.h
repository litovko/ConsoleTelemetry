#ifndef CTCPSERVER_H
#define CTCPSERVER_H

#include <QObject>
#include <QtNetwork/qtcpserver.h>
#include <QtNetwork/qtcpsocket.h>
#include <QTimer>
class cTCPServer : public QObject
{
    Q_OBJECT
public:
    //explicit cTCPServer(QObject *parent = 0);
    cTCPServer();

signals:

public slots:
    void serverConnection();
    void timerSlot();
    void clientDisconnected();
private:
    QTcpServer *m_tcpServer;
    QTcpSocket *m_clientConnection;
    QTimer m_timer;
    bool m_connected=false;
};

#endif // CTCPSERVER_H
