#include "tori_twitter_api.h"
#include <QDebug>

ToriTwitterAPI::ToriTwitterAPI(QQuickItem *root, QObject *parent) :
    QObject(parent)
{
    this->_root = root;
    QObject::connect(this->_root, SIGNAL(send_twit(QString, QString)), this, SLOT(update(QString, QString)));
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
        QMetaObject::invokeMethod(this->_root, "add_account", Q_ARG(QVariant, iterator.key()), Q_ARG(QVariant, ""));
    }
}

void ToriTwitterAPI::update(QString user, QString status)
{
    AccountClient* client = this->accountClients[user];
    client->update(status);
}

void ToriTwitterAPI::destroy(QString user, qlonglong twit_id)
{
    AccountClient* client = this->accountClients[user];
    client->destroy(twit_id);
}

void ToriTwitterAPI::retweet(QString user, qlonglong twit_id)
{
    AccountClient* client = this->accountClients[user];
    client->retweet(twit_id);
}

void ToriTwitterAPI::retweets(QString user, qlonglong twit_id)
{
    AccountClient* client = this->accountClients[user];
    client->retweets(twit_id);
}

void ToriTwitterAPI::show(QString user, qlonglong twit_id)
{
    AccountClient* client = this->accountClients[user];
    client->show(twit_id);
}
