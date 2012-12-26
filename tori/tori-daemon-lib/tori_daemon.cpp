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

#include <QxtLogger>
#include "tori_daemon.h"

namespace tori
{

ToriDaemon::ToriDaemon(QObject *parent) :
    QObject(parent),
    _conn(QDBusConnection::sessionBus())
{
    // create the keyring that will be used to store and retrieve the different
    // tokens
    _keyring = new keyring::Keyring(_conn);

    connect(_keyring, SIGNAL(sessionOpened()),
        this, SLOT(onKeyringSessionOpened()));
    connect(_keyring, SIGNAL(credentialsSet(Accounts::AccountId, bool)),
        this, SLOT(onAccountSecretStored(Accounts::AccountId, bool)));
    connect(_keyring, SIGNAL(credentialsFound(Accounts::AccountId, QString, QString, bool)),
        this, SLOT(onCredentialsFound(Accounts::AccountId, QString, QString, bool)));
}

void ToriDaemon::start()
{
     qxtLog->enableAllLogLevels();
    _keyring->openSession();
}

void ToriDaemon::onKeyringSessionOpened()
{
    // we can start the diff dbus daemons
    qxtLog->debug() << "Keyring session opened.";
    _keyring->setCredentials(0, "test", "testSecret");
}

void ToriDaemon::onAccountSecretStored(Accounts::AccountId id, bool stored)
{
    qxtLog->debug() << "onAccountSecretStored";

    if(stored)
    {
        qxtLog->debug() << "Secrets stored.";
        _keyring->getCredentials(id);
    }
}

void ToriDaemon::onCredentialsFound(Accounts::AccountId id, QString token, QString tokenSecret, bool found)
{
    qxtLog->debug() << "onCredentialsFound";
    if(found)
    {
        qxtLog->debug() << "Credentials found" << id << "token: " << token << "token secret:" << tokenSecret;
        _keyring->deleteCredentials(id);
    }
    else
    {
        qxtLog->debug() << "Creds not found!";
    }
}

void ToriDaemon::onKeyringSessionOpenError()
{
    qDebug() << "Error opening Keyring";
}

} // tori
