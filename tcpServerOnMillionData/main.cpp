#include <QCoreApplication>

#include "TCPServer.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TCPServer serv;
    serv.init();
    return a.exec();
}

