#include <QCoreApplication>
#include "ctcpserver.h"

int main(int argc, char *argv[])
{



    QCoreApplication a(argc, argv);
    cTCPServer server;
    return a.exec();
}
