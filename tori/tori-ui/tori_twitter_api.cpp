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
        AccountClient* proxy = new AccountClient(iterator.value().path());
        proxy->authenticate();
        this->accountClients[iterator.key()] = proxy;
        qDebug() << "Account:" << iterator.key();
    }
}

void ToriTwitterAPI::update(QString user, QString status)
{
    AccountClient* client = this->accountClients[user];
    client->update(status);
}

void ToriTwitterAPI::destroy(qlonglong twit_id)
{
    AccountClient* client = this->accountClients[user];
    client->destroy(twit_id);
}

void ToriTwitterAPI::retweet(qlonglong twit_id)
{
    AccountClient* client = this->accountClients[user];
    client->retweet(twit_id);
}

void ToriTwitterAPI::retweets(qlonglong twit_id)
{
    AccountClient* client = this->accountClients[user];
    client->retweets(twit_id);
}

void ToriTwitterAPI::show(qlonglong twit_id)
{
    AccountClient* client = this->accountClients[user];
    client->show(twit_id);
}
