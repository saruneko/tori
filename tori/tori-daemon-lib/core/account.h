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

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <Accounts/Account>
#include <QtKOAuth>
#include <QNetworkAccessManager>
#include <QObject>
#include <QScopedPointer>
#include <keyring/keyring.h>
#include "keyring/keyring.h"

namespace tori
{

namespace core
{

class AccountPrivate;
class Account : public QObject
{
    Q_DECLARE_PRIVATE(Account)
    Q_OBJECT
public:
    explicit Account(Accounts::Account* acc, keyring::Keyring* key, QObject *parent = 0);
    ~Account();

public:
    QString tokenKey();
    QString tokenSecret();
    QString consumerKey();
    QString consumerSecret();

public slots:
    void authenticate();

    void destroy(const QString &uuid, qlonglong tweet_id, const QVariantMap &options);
    void retweet(const QString &uuid, qlonglong tweet_id, const QVariantMap &options);
    void retweets(const QString &uuid, qlonglong tweet_id, const QVariantMap &options);
    void show(const QString &uuid, qlonglong tweet_id, const QVariantMap &options);
    void update(const QString &uuid, const QString &status, const QVariantMap &options);

signals:
    void authenticated();
    void authenticationError(uint errorCode, QString error);

private:
    Q_PRIVATE_SLOT(d_func(), void onResponse(const SignOn::SessionData&))
    Q_PRIVATE_SLOT(d_func(), void onError(const SignOn::Error&))
    Q_PRIVATE_SLOT(d_func(), void onCredentialsFound(Accounts::AccountId, QString, QString, bool))

private:
    QScopedPointer<AccountPrivate> d_ptr;
};

} // core

} // tori

#endif // ACCOUNT_H
