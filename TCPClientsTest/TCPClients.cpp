#include "TCPClients.h"

#include <QHostAddress>
#include <QDebug>

TCPClients::TCPClients(QObject *parent) : QObject(parent)
  , m_socket(new QTcpSocket(this))
{
    m_socket->connectToHost(QHostAddress::LocalHost, 11555);
    connect(m_socket, &QTcpSocket::readyRead, this,  &TCPClients::receiveServerData);
    //connect()
}

void TCPClients::receiveServerData()
{
    qDebug() << m_socket->readAll();
}
