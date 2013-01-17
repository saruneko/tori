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
#include <QNetworkAccessManager>
#include <QObject>
#include <QScopedPointer>
#include <keyring/keyring.h>

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
    explicit Account(Accounts::Account* acc, QNetworkAccessManager* man, QObject *parent = 0);
    ~Account();

public slots:
    void destroy(uint tweet_id, const QVariantMap &options);
    void retweet(uint tweet_id, const QVariantMap &options);
    void retweets(uint tweet_id, const QVariantMap &options);
    void show(uint tweet_id, const QVariantMap &options);
    void update(const QString &status, const QVariantMap &options);

signals:
    void authenticationError(uint error);

private:
    QScopedPointer<AccountPrivate> d_ptr;
};

} // core

} // tori

#endif // ACCOUNT_H
