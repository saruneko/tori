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

#include "twitter/status_api.h"


namespace tori
{

namespace core
{

class AccountPrivate
{
    Q_DECLARE_PUBLIC(Account)
public:
    AccountPrivate(Accounts::Account* acc, KQOAuthManager* man, Account* parent);

    void destroy(const QString& uuid, uint tweet_id, const QVariantMap &options);
    void retweet(const QString& uuid, uint tweet_id, const QVariantMap &options);
    void retweets(const QString& uuid, uint tweet_id, const QVariantMap &options);
    void show(const QString& uuid, uint tweet_id, const QVariantMap &options);
    void update(const QString& uuid, const QString &status, const QVariantMap &options);

private:
    static const QString DEFAULT_TOKEN;
    static const QString DEFAULT_TOKEN_SECRET;

    Accounts::Account* _acc;
    Account* q_ptr;
    Accounts::AccountService* _serv;
    KQOAuthManager* _man;
    twitter::StatusAPI* _status;
    QString _consumerKey;
    QString _consumerSecret;
    QString _tokenKey;
    QString _tokenSecret;

};

// default values from gwibber
const QString AccountPrivate::DEFAULT_TOKEN = "qMBra1U4bpNYvDz947M5Q";
const QString AccountPrivate::DEFAULT_TOKEN_SECRET = "Lzdkhg0WvGYFzD9tnsuwC0zYmpJ4z7HrZl3yOxU1g";

AccountPrivate::AccountPrivate(Accounts::Account* acc, KQOAuthManager* man, Account* parent) :
    _acc(acc),
    _man(man),
    q_ptr(parent)
{
    QList<Accounts::Service> services = _acc->services();

    // TODO: what happens when we have more than one service??
    _serv = new Accounts::AccountService(_acc, services.at(0));

    Accounts::AuthData data = _serv->authData();
    QVariantMap params = data.parameters();

    _consumerKey = params["ConsumerKey"].toString();
    _consumerSecret = params["ConsumerSecret"].toString();
    _tokenKey = AccountPrivate::DEFAULT_TOKEN;
    _tokenSecret = AccountPrivate::DEFAULT_TOKEN_SECRET;

    _status = new twitter::StatusAPI(q_ptr, _man);
}

void AccountPrivate::destroy(const QString& uuid, uint tweet_id, const QVariantMap &options)
{
    _status->destroy(uuid, tweet_id, options);
}

void AccountPrivate::retweet(const QString& uuid, uint tweet_id, const QVariantMap &options)
{
    _status->retweet(uuid, tweet_id, options);
}

void AccountPrivate::retweets(const QString& uuid, uint tweet_id, const QVariantMap &options)
{
    _status->retweets(uuid, tweet_id, options);
}

void AccountPrivate::show(const QString& uuid, uint tweet_id, const QVariantMap &options)
{
    _status->show(uuid, tweet_id, options);
}

void AccountPrivate::update(const QString& uuid, const QString &status, const QVariantMap &options)
{
    _status->update(uuid, status, options);
}

Account::Account(Accounts::Account* acc, KQOAuthManager* man, QObject *parent) : QObject(parent),
    d_ptr(new AccountPrivate(acc, man, this))
{
}

Account::~Account()
{
}

QString Account::consumerKey()
{
    Q_D(Account);
    return d->_consumerKey;
}

QString Account::consumerSecret()
{
    Q_D(Account);
    return d->_consumerSecret;
}

QString Account::tokenKey()
{
    Q_D(Account);
    return d->_tokenKey;
}

QString Account::tokenSecret()
{
    Q_D(Account);
    return d->_tokenSecret;
}

void Account::destroy(const QString& uuid, uint tweet_id, const QVariantMap &options)
{
    Q_D(Account);
    d->destroy(uuid, tweet_id, options);
}

void Account::retweet(const QString& uuid, uint tweet_id, const QVariantMap &options)
{
    Q_D(Account);
    d->retweet(uuid, tweet_id, options);
}

void Account::retweets(const QString& uuid, uint tweet_id, const QVariantMap &options)
{
    Q_D(Account);
    d->retweets(uuid, tweet_id, options);
}

void Account::show(const QString& uuid, uint tweet_id, const QVariantMap &options)
{
    Q_D(Account);
    d->show(uuid, tweet_id, options);
}

void Account::update(const QString& uuid, const QString &status, const QVariantMap &options)
{
    Q_D(Account);
    d->update(uuid, status, options);
}

} // core

} // tori

#include "moc_account.cpp"
