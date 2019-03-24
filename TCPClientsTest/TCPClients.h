#ifndef TCPCLIENTS_H
#define TCPCLIENTS_H

#include <QObject>
#include <QTcpSocket>

class TCPClients : public QObject
{
    Q_OBJECT
public:
    explicit TCPClients(QObject *parent = nullptr);
    void connectToServer();

signals:

public slots:
    void receiveServerData();

private:
    QTcpSocket *m_socket;
};

#endif // TCPCLIENTS_H
