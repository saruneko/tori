#include "tori_twitter_api.h"
#include <client/account_manager_client.h>
#include <QDebug>
#include <QHash>
#include <QString>

ToriTwitterAPI::ToriTwitterAPI(QObject *parent) :
    QObject(parent)
{
    AccountManagerClient client;
    QHash<QString, QDBusObjectPath> reply = client.getAccounts();

    QHashIterator<QString, QDBusObjectPath> iterator(reply);
    while (iterator.hasNext()) {
        iterator.next();
        // Now is just printing the values for testing
        // In the next branch i going to create the proper connection for each account
        qDebug() << iterator.key() << iterator.value().path();
    }
}
