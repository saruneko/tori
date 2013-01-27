#include "account_client.h"

AccountClient::AccountClient(QString service, QObject *parent) :
    QObject(parent)
{
    this->proxy = new AccountProxy(service, "/", QDBusConnection::sessionBus());
}
