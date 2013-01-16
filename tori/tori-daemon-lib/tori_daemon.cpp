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

#include <QDebug>
#include "./dbus/dbus_helper.h"
#include "tori_daemon.h"


using namespace tori::core;

namespace tori
{

ToriDaemon::ToriDaemon(QObject *parent) :
    QObject(parent),
    _conn(QDBusConnection::sessionBus())
{
    // create the keyring that will be used to store and retrieve the different
    // tokens
    _keyring = new keyring::Keyring(_conn);
    _accManager = new AccountManager(_conn, _keyring);
}

void ToriDaemon::start()
{
    qDebug() << "Starting daemon...";
    _keyring->openSession();
    bool started = startAccountManagerService();
}

bool ToriDaemon::startAccountManagerService()
{
    qDebug("Starting dbus services");
    _accAdaptor = new AccountManagerAdaptor(_accManager);
    bool ret = _conn.registerService("org.saruneko.tori.AccountManager");
    if (ret)
    {
        qDebug("Account manager registered.");
        ret = _conn.registerObject("/", _accManager);
        return ret;
    }
    return false;
}

} // tori
