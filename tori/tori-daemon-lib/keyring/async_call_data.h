/**
 *
 * Copyright (c) 2013 mandel
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


#ifndef ASYNC_CALL_DATA_H
#define ASYNC_CALL_DATA_H

#include <functional>
#include <Accounts/Account>
#include <QDBusObjectPath>
#include <QObject>

namespace tori
{

namespace keyring
{


// class used to pass extra information to the dbus signal mapper
class AsyncCallData : public QObject
{

    typedef std::function<void(AsyncCallData*)> async_callback_cb;
    typedef std::function<void(QString, AsyncCallData*)> locked_items_cb;

    Q_OBJECT
public:
    AsyncCallData(QObject* parent=0) : QObject(parent) {}

    Accounts::AccountId accId;
    QString token;
    QString tokenSecret;
    QString interfacePath;
    QList<QDBusObjectPath> unlocked;
    QList<QDBusObjectPath> locked;
    async_callback_cb unlockedItemsCb;
    async_callback_cb unlockDbusError;
    locked_items_cb lockedItemsCb;
};

} // keyring

} // tori

#endif // ASYNC_CALL_DATA_H
