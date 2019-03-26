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
    void disconnectedFromServer();

protected:
    void timerEvent(QTimerEvent *event);

private:
    QList<QTcpSocket*> m_sockets;
};

#endif // TCPCLIENTS_H
