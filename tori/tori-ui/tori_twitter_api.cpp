#include "tori_twitter_api.h"
#include <QDebug>

ToriTwitterAPI::ToriTwitterAPI(QObject *parent) :
    QObject(parent)
{
}

void ToriTwitterAPI::getAccounts()
{
    QHash<QString, QDBusObjectPath> reply = client.getAccounts();

    QHashIterator<QString, QDBusObjectPath> iterator(reply);
    while (iterator.hasNext()) {
        iterator.next();
//        this->accountClients[iterator.key()] = new AccountClient(iterator.value().path());
        qDebug() << iterator.key();
    }
}
