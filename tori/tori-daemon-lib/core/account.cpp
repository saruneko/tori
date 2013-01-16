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


namespace tori
{

namespace core
{

class AccountPrivate
{
    Q_DECLARE_PUBLIC(Account)
public:
    AccountPrivate(Accounts::Account* acc, Account* parent);

private:
    static const QString DEFAULT_TOKEN;
    static const QString DEFAULT_TOKEN_SECRET;

    Accounts::Account* _acc;
    Account* q_ptr;
    Accounts::AccountService* _serv;
    QString _consumerKey;
    QString _consumerSecret;
    QString _token;
    QString _tokenSecret;
    QMutex _mutex;
};

// default values from gwibber
const QString AccountPrivate::DEFAULT_TOKEN = "IOW164CqEJdlrkXlrQ17GA";
const QString AccountPrivate::DEFAULT_TOKEN_SECRET = "mJ38xSp6kqUzB2XMOq9USrmTgWAXOqXpS0g6WUEk";

AccountPrivate::AccountPrivate(Accounts::Account* acc, Account* parent) :
    _acc(acc),
    q_ptr(parent)
{
    QList<Accounts::Service> services = _acc->services();

    // TODO: what happens when we have more than one service??
    _serv = new Accounts::AccountService(_acc, services.at(0));

    Accounts::AuthData data = _serv->authData();
    QVariantMap params = data.parameters();

    _consumerKey = params["ConsumerKey"].toString().toUtf8();
    _consumerSecret = params["ConsumerSecret"].toString().toUtf8();

    qDebug() << "Using default token and token secret.";
    _token = AccountPrivate::DEFAULT_TOKEN.toUtf8();
    _tokenSecret = AccountPrivate::DEFAULT_TOKEN_SECRET.toUtf8();
}

Account::Account(Accounts::Account* acc, QObject *parent) : QObject(parent),
    d_ptr(new AccountPrivate(acc, this))
{
}

Account::~Account()
{
}

} // core

} // tori

#include "moc_account.cpp"
