#include "account_client.h"

AccountClient::AccountClient(QString service, QObject *parent) :
    QObject(parent)
{
    this->proxy = new AccountProxy("org.saruneko.tori.AccountManager", service, QDBusConnection::sessionBus());

    QObject::connect(this->proxy, SIGNAL(authenticated()), this, SLOT(userAuthenticated()));
    QObject::connect(this->proxy, SIGNAL(authenticationError(uint,QString)), this, SLOT(authenticationError(uint,QString)));
}

void AccountClient::authenticate()
{
    this->proxy->authenticate();
}

void AccountClient::update(QString& status)
{
    QVariantMap vmap;
    this->proxy->update("", status, vmap);
}

void AccountClient::destroy(qlonglong twit_id)
{
    QVariantMap vmap;
    this->proxy->destroy("", twit_id, vmap);
}

void AccountClient::retweet(qlonglong twit_id)
{
    QVariantMap vmap;
    this->proxy->retweet("", twit_id, vmap);
}

void AccountClient::retweets(qlonglong twit_id)
{
    QVariantMap vmap;
    this->proxy->retweets("", twit_id, vmap);
}

void AccountClient::show(qlonglong twit_id)
{
    QVariantMap vmap;
    this->proxy->show("", twit_id, vmap);
}

void AccountClient::userAuthenticated()
{
    qDebug() << "AUTHENTICATED";
}

void AccountClient::authenticationError(uint a, QString b)
{
    qDebug() << a << b;
}
