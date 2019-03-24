#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QList>

class TCPServer : public QObject
{
    Q_OBJECT
public:
    explicit TCPServer(QObject *parent = 0);

    bool init();


signals:

public slots:
    void handleNewConnection();

private:
    QTcpServer m_server;
    QList <QTcpSocket*> m_clients;
};

#endif // TCPSERVER_H
