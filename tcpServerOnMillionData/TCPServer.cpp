#include "TCPServer.h"

#include <QTcpSocket>
#include <QDebug>
#include <QDateTime>

TCPServer::TCPServer(QObject *parent) : QObject(parent)
{

}

bool TCPServer::init()
{
    bool isSuccess = m_server.listen(QHostAddress::Any, 11555);
    if (!isSuccess || !m_server.isListening())
    {
        qDebug() << m_server.errorString();
        return false;
    }
    qDebug() << "The Server is listenning on " << m_server.serverPort() << "!\n" ;

    connect(&m_server, &QTcpServer::newConnection, this, &TCPServer::handleNewConnection);
}

void TCPServer::handleNewConnection()
{
    if (!m_server.hasPendingConnections())
    {
        qDebug() << "No pending connections, but it emited  a handleNewConnection singal.";
        return;
    }

    QTcpSocket *clientSocket = m_server.nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &TCPServer::readClientsData);
    connect(clientSocket, &QTcpSocket::disconnected, this, &TCPServer::clientDisconnected);
    m_clients.append(clientSocket);

    clientSocket->write("Hi, I'm server!");

    printInfo("New Connection on: \n", clientSocket);
}

struct TestData
{
    double a;
    double b;
};
void TCPServer::readClientsData()
{
    static QDateTime initDateTime = QDateTime::currentDateTime();
    static int count = 0;

    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*> (sender());
    if (!clientSocket)
    {
        qDebug() << "Invalid socket!";
        return;
    }

    QByteArray allData = clientSocket->readAll();
    TestData structData = {};
    if (allData.size() != sizeof(TestData))
    {
        return;
    }
    memcpy((void *)&structData, (void *)allData.data(), allData.size());
    //qDebug() << "收到信息： " << structData.a << structData.b;
    add(structData.a, structData.b);
    count++;
//    qDebug() << QDateTime::currentDateTime().msecsTo(initDateTime);
    if (QDateTime::currentDateTime().msecsTo(initDateTime) < -1000)
    {
        qDebug() << "one second can solve data " << count;
        count = 0;
        initDateTime = QDateTime::currentDateTime();
    }
}

void TCPServer::clientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*> (sender());
    if (!clientSocket)
    {
        qDebug() << "Invalid socket!";
        return;
    }

    m_clients.removeOne(clientSocket);
    printInfo("Disconnected on ", clientSocket);
}

void TCPServer::printInfo(QString msg, QTcpSocket *clientSocket)
{
    qDebug() << msg
             << "peerAddr: " << clientSocket->peerAddress() << "\t"
             << "peerName: " << clientSocket->peerName() << "\t"
             << "peerPort: " << clientSocket->peerPort() << "\n"
//             << "localAddress: " <<clientSocket->localAddress() << "\t"
//             << "localPort: " <<clientSocket->localPort() << "\n"
             << "Clients size: " <<m_clients.size() << "\n"
                ;
}

double TCPServer::add(double a, double b)
{
    double sum = 0;
    double aa = a;
    double bb = b;
    sum = aa + bb;
    //qDebug() << a << b << aa << bb << sum;
    return sum;
}

