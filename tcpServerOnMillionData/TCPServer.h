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

    void readClientsData();
    void clientDisconnected();

private:
    QTcpServer m_server;
    QList <QTcpSocket*> m_clients;

private:
    void printInfo(QString msg, QTcpSocket* socket);

private:
    double add(double a, double b);
};

#endif // TCPSERVER_H
