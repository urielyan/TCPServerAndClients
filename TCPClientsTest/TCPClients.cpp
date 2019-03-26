#include "TCPClients.h"

#include <QHostAddress>
#include <QDebug>

struct TestData
{
    double a;
    double b;
};

TCPClients::TCPClients(QObject *parent) : QObject(parent)
{
    for (int i = 0; i< 100; ++i)
    {
        QTcpSocket *socket = new QTcpSocket(this);
        socket->connectToHost(QHostAddress::LocalHost, 11555);
        connect(socket, &QTcpSocket::readyRead, this,  &TCPClients::receiveServerData);
        connect(socket, &QTcpSocket::disconnected, this, &TCPClients::disconnectedFromServer);
        TestData structData;
        structData.a = 2.5232;
        structData.b = 5.266;

        if (socket->state() == QTcpSocket::ConnectedState)
        {
        }
        //使用多线程处理多个子程序
        startTimer(50);
        socket->write(QByteArray((const char*)(&structData), sizeof(structData)));//
        m_sockets.append(socket);
    }
    //connect()
}

void TCPClients::receiveServerData()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*> (sender());
    if (!socket)
    {
        qDebug() << "Invalid socket!";
        return;
    }
    qDebug() << socket->readAll();
}

void TCPClients::disconnectedFromServer()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*> (sender());
    if (!socket)
    {
        qDebug() << "Invalid socket!";
        return;
    }
    m_sockets.removeOne(socket);
}

void TCPClients::timerEvent(QTimerEvent *event)
{

}
