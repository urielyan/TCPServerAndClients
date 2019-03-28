#include "TCPClients.h"

#include <QHostAddress>
#include <QDebug>
#include <QTimerEvent>
#include <QtMath>

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


        //启动多个计时器
        int timeID = startTimer(20);
        m_sockets[timeID] = socket;
        //m_sockets.append(socket);
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
    m_sockets.remove(m_sockets.key(socket));
}

void TCPClients::timerEvent(QTimerEvent *event)
{
    int timeID = event->timerId();
    if (!m_sockets.contains(timeID))
    {
        return;
    }
    QTcpSocket *socket = m_sockets.value(timeID);
    if (!socket)
    {
        return;
    }

    TestData structData;
    structData.a = qrand() % 10;
    structData.b = qrand() % 10;


    socket->write(QByteArray((const char*)(&structData), sizeof(structData)));//

}
