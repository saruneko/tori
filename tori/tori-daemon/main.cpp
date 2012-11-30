#include <QCoreApplication>
#include "keyring/service.h"
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

    // connect to the keyring
    ServiceInterface keyring("org.freedesktop.secrets", "/org/freedesktop/secrets", connection);
    return a.exec();
}
