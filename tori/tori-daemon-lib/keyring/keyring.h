/**
 *
 * Copyright (c) 2013 Manuel de la Pena <mandel@themacaque.com>
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

#ifndef KEYRING_H
#define KEYRING_H

#include <Accounts/Account>
#include <QObject>
#include <QDBusConnection>
#include "secret.h"

namespace tori
{

namespace keyring
{

class KeyringPrivate;
class Keyring : public QObject
{

    Q_OBJECT
    Q_DECLARE_PRIVATE(Keyring)
public:
    Keyring(QDBusConnection connection, QObject* parent=0, QString windowId = "0");
    ~Keyring();

    void openSession();
    void getCredentials(Accounts::AccountId id);
    void setCredentials(Accounts::AccountId id, QString token, QString tokenSecret);
    void deleteCredentials(Accounts::AccountId id);

Q_SIGNALS:
    void userCancelation(Accounts::AccountId id);
    void sessionOpened();
    void sessionOpenError();

    // signals used to let the user know that we did retrieve the data
    void credentialsFound(Accounts::AccountId id, QString token, QString tokenSecret, bool found);
    void credentialsError(Accounts::AccountId id);
    void credentialsSet(Accounts::AccountId id, bool stored);
    void credentialsDeleted(Accounts::AccountId id, bool deleted);

private:
    Q_PRIVATE_SLOT(d_func(), void onSessionOpened(QDBusPendingCallWatcher*))
    Q_PRIVATE_SLOT(d_func(), void onSearchItemsForGet(QDBusPendingCallWatcher*, QObject*))
    Q_PRIVATE_SLOT(d_func(), void onSearchItemsForDelete(QDBusPendingCallWatcher*, QObject*))
    Q_PRIVATE_SLOT(d_func(), void onPromptCompletedForGet(bool, const QDBusVariant&, QObject*))
    Q_PRIVATE_SLOT(d_func(), void onPromptCompletedForDelete(bool, const QDBusVariant&, QObject*))
    Q_PRIVATE_SLOT(d_func(), void onCollectionUnlocked(QDBusPendingCallWatcher*, QObject*))
    Q_PRIVATE_SLOT(d_func(), void onReadAliasDone(QDBusPendingCallWatcher*, QObject*))
    Q_PRIVATE_SLOT(d_func(), void onItemDeleted(QDBusPendingCallWatcher*, QObject*))
    Q_PRIVATE_SLOT(d_func(), void onGetSecret(QDBusPendingCallWatcher*, QObject*))
    Q_PRIVATE_SLOT(d_func(), void onCreateItem(QDBusPendingCallWatcher*, QObject*))
    Q_PRIVATE_SLOT(d_func(), void onUnlock(QDBusPendingCallWatcher* , QObject*))



protected:
    // internal vars
    QScopedPointer<KeyringPrivate> d_ptr;
};

} // keyring

} // tori

#endif // KEYRING_H
