#ifndef TCPCLIENTS_H
#define TCPCLIENTS_H

#include <QObject>
#include <QTcpSocket>
#include <QMap>

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
    QMap<int, QTcpSocket*> m_sockets;
};

#endif // TCPCLIENTS_H
