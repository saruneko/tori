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

#include <QDebug>
#include <QHash>
#include <QVariant>
#include <Accounts/Manager>
#include "core/account.h"
#include "core/account_adaptor.h"
#include "account_manager.h"

namespace tori
{

namespace core
{


class AccountManagerPrivate
{

    Q_DECLARE_PUBLIC(AccountManager)

public:
    AccountManagerPrivate(QDBusConnection connection, tori::keyring::Keyring* key, AccountManager* parent, bool useDefault=false);

    QHash<QString, QDBusObjectPath> getAccounts();

protected:
    void onAccountCreated(Accounts::AccountId);
    void onAccountDeleted(Accounts::AccountId);
    void onAccountUpdated(Accounts::AccountId);

private:
    bool isTwitterAccount(Accounts::AccountId acc_id);

    static QString BASE_ACCOUNT_URL;
private:
    AccountManager* q_ptr;
    Accounts::Manager* _man;
    QHash<Accounts::AccountId, QPair<Account*, AccountAdaptor*> > _accounts;
    tori::keyring::Keyring* _key;
    QDBusConnection _conn;
    bool _useDefault;
};

QString AccountManagerPrivate::BASE_ACCOUNT_URL = "/org/saruneko/tori/account/%1";

AccountManagerPrivate::AccountManagerPrivate(QDBusConnection connection, tori::keyring::Keyring* key,
    AccountManager* parent, bool useDefault) :
    q_ptr(parent),
    _conn(connection),
    _useDefault(useDefault)
{
    Q_Q(AccountManager);
    _man = new Accounts::Manager("microblogging");
    _key = key;

    // do connect the signals so that we can let people know changes happened
    q->connect(_man, SIGNAL(accountCreated(Accounts::AccountId)),
        q, SLOT(onAccountCreated(Accounts::AccountId)));
    q->connect(_man, SIGNAL(accountUpdated(Accounts::AccountId)),
        q, SLOT(onAccountUpdated(Accounts::AccountId)));
    q->connect(_man, SIGNAL(accountRemoved(Accounts::AccountId)),
        q, SLOT(onAccountDeleted(Accounts::AccountId)));
}

bool AccountManagerPrivate::isTwitterAccount(Accounts::AccountId acc_id)
{
    Accounts::Account* acc = _man->account(acc_id);
    return acc->providerName() == "twitter";
}

QHash<QString, QDBusObjectPath> AccountManagerPrivate::getAccounts()
{
    QHash<QString, QDBusObjectPath> accounts;

    // loop and just add those accounts from twitter
    Accounts::AccountIdList allAccounts = _man->accountList();

    qDebug() << "Number of accounts found:" << allAccounts.length();

    for(int pos = 0; pos < allAccounts.length(); ++pos)
    {
        Accounts::Account* acc = _man->account(allAccounts.at(pos));
        qDebug() << "Account id:" << acc->id() << "Account provider:" << acc->providerName();

        if(acc->providerName() == "twitter")
        {
            QString path = AccountManagerPrivate::BASE_ACCOUNT_URL.arg(QString::number(acc->id()));
            accounts[acc->displayName()] = QDBusObjectPath(path);

            if (!_accounts.contains(acc->id()))
            {
                Account* account = new Account(acc, _key, _useDefault);
                AccountAdaptor* adaptor = new AccountAdaptor(account);

                QPair<Account*, AccountAdaptor*> pair;
                pair.first = account;
                pair.second = adaptor;
                _accounts[acc->id()] = pair;

                // register the object to the dbus service
                _conn.registerObject(path, account);
            }
        }
    }
    return accounts;
}

void AccountManagerPrivate::onAccountCreated(Accounts::AccountId acc_id)
{
    Q_Q(AccountManager);
    if(isTwitterAccount(acc_id))
    {
        Accounts::Account* acc = _man->account(acc_id);
        Account* account = new Account(acc, _key, _useDefault);
        AccountAdaptor* adaptor = new AccountAdaptor(acc);
        QPair<Account*, AccountAdaptor*> pair;
        pair.first = account;
        pair.second = adaptor;
        _accounts[acc->id()] = pair;

        QString path = AccountManagerPrivate::BASE_ACCOUNT_URL.arg(QString::number(acc->id()));
        _conn.registerObject(path, account);

        emit q->accountCreated(acc->id(), acc->displayName());
    }
}

void AccountManagerPrivate::onAccountDeleted(Accounts::AccountId acc_id)
{
    Q_Q(AccountManager);
    if(isTwitterAccount(acc_id))
    {
        Accounts::Account* acc = _man->account(acc_id);
        QString path = AccountManagerPrivate::BASE_ACCOUNT_URL.arg(QString::number(acc->id()));
        _accounts.remove(acc_id);

        // unregister the account from the dbus connection
        _conn.unregisterObject(path);
        emit q->accountDeleted(acc->id(), acc->displayName());
    }
}

void AccountManagerPrivate::onAccountUpdated(Accounts::AccountId acc_id)
{
    Q_Q(AccountManager);
    if(isTwitterAccount(acc_id))
    {
        Accounts::Account* acc = _man->account(acc_id);
        emit q->accountUpdated(acc->id(), acc->displayName());
    }
}

AccountManager::AccountManager(QDBusConnection connection, tori::keyring::Keyring* key, bool useDefault,
    QObject *parent) :
    QObject(parent),
    d_ptr(new AccountManagerPrivate(connection, key, this, useDefault))
{
}

AccountManager::~AccountManager()
{
}

DBusObjectPathHash AccountManager::getAccounts()
{
    Q_D(AccountManager);
    qDebug() << "AccountManager::getAccounts()";
    return d->getAccounts();
}




} // core

} // tori

//#include "moc_account_manager.cpp"
