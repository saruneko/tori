#include <QCoreApplication>
#include "tori_daemon.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

/*
    ToriDBusDaemon* daemon = new ToriDBusDaemon;
    new ToriDBusAdaptor(daemon);

    QDBusConnection connection = QDBusConnection::sessionBus();
    bool ret = connection.registerService("com.saruneko.tori");
    ret = connection.registerObject("/", daemon);
*/
    tori::ToriDaemon* daemon = new tori::ToriDaemon();
    daemon->start();

    return a.exec();
}
