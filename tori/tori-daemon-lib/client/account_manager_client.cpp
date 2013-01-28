#include "account_manager_client.h"

#include <QDBusConnection>

AccountManagerClient::AccountManagerClient(QObject *parent) :
    QObject(parent)
{
    this->_client = new AccountManagerProxy("org.saruneko.tori.AccountManager",
                                                        "/", QDBusConnection::sessionBus());
}

QHash<QString, QDBusObjectPath> AccountManagerClient::getAccounts()
{
    return this->_client->getAccounts().value();
}
