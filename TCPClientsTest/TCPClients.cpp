#include "TCPClients.h"

#include <QHostAddress>
#include <QDebug>
#include <QTimerEvent>
#include <QtMath>
#include <QDateTime>

struct TestData
{
    double a;
    double b;
};

TCPClients::TCPClients(QObject *parent) : QObject(parent)
{

    for (int i = 0; i< 50; ++i)
    {
        QTcpSocket *socket = new QTcpSocket(this);
        socket->connectToHost(QHostAddress::LocalHost, 11555);
        connect(socket, &QTcpSocket::readyRead, this,  &TCPClients::receiveServerData);
        connect(socket, &QTcpSocket::disconnected, this, &TCPClients::disconnectedFromServer);


        //启动多个计时器
        int timeID = startTimer(5);
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
    static QDateTime initDateTime = QDateTime::currentDateTime();
    static int count = 0;
    QDateTime inFunTime= QDateTime::currentDateTime();


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



    count++;
    if (QDateTime::currentDateTime().msecsTo(initDateTime) < -1000)
    {
        qDebug() << "one second can solve data " << count;
        count = 0;
        initDateTime = QDateTime::currentDateTime();
    }

    //发送数据的时间基本可以忽略不计
    //qDebug() << QDateTime::currentDateTime().msecsTo(inFunTime);
}
