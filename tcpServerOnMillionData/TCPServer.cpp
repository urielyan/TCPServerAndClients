#include "TCPServer.h"

#include <QTcpSocket>

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
    m_clients.append(clientSocket);

    clientSocket->write("Hi, I'm server!");

    qDebug() << "peerAddr: " << clientSocket->peerAddress() << "\t"
             << "peerName: " << clientSocket->peerName() << "\t"
             << "peerPort: " << clientSocket->peerPort() << "\n"
             << "localAddress: " <<clientSocket->localAddress() << "\t"
             << "localPort: " <<clientSocket->localPort() << "\n"
                ;
}

