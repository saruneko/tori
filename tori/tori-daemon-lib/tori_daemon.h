/**
 *
 * Copyright (c) 2012 Manuel de la Pena <mandel@themacaque.com>
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

#ifndef TORI_DAEMON_H
#define TORI_DAEMON_H

#include <QDBusConnection>
#include <QObject>
#include <Accounts/Account>
#include "keyring/keyring.h"


namespace tori
{

class ToriDaemon : public QObject
{
    Q_OBJECT
public:
    explicit ToriDaemon(QObject *parent = 0);

    void start();

signals:
    
public slots:

private Q_SLOTS:
    void onKeyringSessionOpened();
    void onAccountSecretStored(Accounts::AccountId id, bool stored);
    void onKeyringSessionOpenError();
    void onCredentialsFound(Accounts::AccountId id, QString token, QString tokenSecret, bool found);

private:
    QDBusConnection _conn;
    keyring::Keyring* _keyring;
};

} // tori
#endif // TORI_DAEMON_H
