/**
 *
 * Copyright (c) 2012 mandel
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "account.h"
#include <Accounts/AccountService>
#include <Accounts/AuthData>
#include <QDebug>
#include <QMutex>

#include "twitter/oauth.h"
#include "twitter/status_api.h"


namespace tori
{

namespace core
{

class AccountPrivate
{
    Q_DECLARE_PUBLIC(Account)
public:
    AccountPrivate(Accounts::Account* acc, QNetworkAccessManager* man, Account* parent);

    void destroy(uint tweet_id, const QVariantMap &options);
    void retweet(uint tweet_id, const QVariantMap &options);
    void retweets(uint tweet_id, const QVariantMap &options);
    void show(uint tweet_id, const QVariantMap &options);
    void update(const QString &status, const QVariantMap &options);

private:
    static const QString DEFAULT_TOKEN;
    static const QString DEFAULT_TOKEN_SECRET;

    Accounts::Account* _acc;
    Account* q_ptr;
    Accounts::AccountService* _serv;
    QNetworkAccessManager* _man;
    twitter::OAuth* _oauth;
    twitter::StatusAPI* _status;

};

// default values from gwibber
const QString AccountPrivate::DEFAULT_TOKEN = "IOW164CqEJdlrkXlrQ17GA";
const QString AccountPrivate::DEFAULT_TOKEN_SECRET = "mJ38xSp6kqUzB2XMOq9USrmTgWAXOqXpS0g6WUEk";

AccountPrivate::AccountPrivate(Accounts::Account* acc, QNetworkAccessManager* man, Account* parent) :
    _acc(acc),
    _man(man),
    q_ptr(parent)
{
    QList<Accounts::Service> services = _acc->services();

    // TODO: what happens when we have more than one service??
    _serv = new Accounts::AccountService(_acc, services.at(0));

    Accounts::AuthData data = _serv->authData();
    QVariantMap params = data.parameters();

    _oauth = new twitter::OAuth(params["ConsumerKey"].toString().toUtf8(),
        params["ConsumerSecret"].toString().toUtf8(),
        AccountPrivate::DEFAULT_TOKEN.toUtf8(),
        AccountPrivate::DEFAULT_TOKEN_SECRET.toUtf8());
    _status = new twitter::StatusAPI(_oauth, _man);
}

void AccountPrivate::destroy(uint tweet_id, const QVariantMap &options)
{
    _status->destroy(tweet_id, options);
}

void AccountPrivate::retweet(uint tweet_id, const QVariantMap &options)
{
    _status->retweet(tweet_id, options);
}

void AccountPrivate::retweets(uint tweet_id, const QVariantMap &options)
{
    _status->retweets(tweet_id, options);
}

void AccountPrivate::show(uint tweet_id, const QVariantMap &options)
{
    _status->show(tweet_id, options);
}

void AccountPrivate::update(const QString &status, const QVariantMap &options)
{
    _status->update(status, options);
}

Account::Account(Accounts::Account* acc, QNetworkAccessManager* man, QObject *parent) : QObject(parent),
    d_ptr(new AccountPrivate(acc, man, this))
{
}

Account::~Account()
{
}

void Account::destroy(uint tweet_id, const QVariantMap &options)
{
    Q_D(Account);
    d->destroy(tweet_id, options);
}

void Account::retweet(uint tweet_id, const QVariantMap &options)
{
    Q_D(Account);
    d->retweet(tweet_id, options);
}

void Account::retweets(uint tweet_id, const QVariantMap &options)
{
    Q_D(Account);
    d->retweets(tweet_id, options);
}

void Account::show(uint tweet_id, const QVariantMap &options)
{
    Q_D(Account);
    d->show(tweet_id, options);
}

void Account::update(const QString &status, const QVariantMap &options)
{
    Q_D(Account);
    d->update(status, options);
}

} // core

} // tori

#include "moc_account.cpp"
