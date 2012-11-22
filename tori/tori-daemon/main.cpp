#include <QCoreApplication>
#include "tori_dbus_adaptor.h"
#include "tori_dbus_daemon.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ToriDBusDaemon* daemon = new ToriDBusDaemon;
    new ToriDBusAdaptor(daemon);

    QDBusConnection connection = QDBusConnection::sessionBus();
    bool ret = connection.registerService("com.saruneko.tori");
    ret = connection.registerObject("/", daemon);

    return a.exec();
}
