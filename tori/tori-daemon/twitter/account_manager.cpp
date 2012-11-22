#include <QVariant>
#include "account_manager.h"

AccountManager::AccountManager(QObject *parent) :
    QObject(parent)
{
    _man = new Accounts::Manager("microblogging");

    // connect to the diff signals and filter so that we are only interested
    // in the twitter accounts

    connect(_man, SIGNAL(accountCreated(Accounts::AccountId)),
        this, SLOT(onAccountCreated(Accounts::AccountId)));
    connect(_man, SIGNAL(accountUpdated(Accounts::AccountId)),
        this, SLOT(onAccountUpdated(Accounts::AccountId)));
    connect(_man, SIGNAL(accountRemoved(Accounts::AccountId)),
        this, SLOT(onAccountDeleted(Accounts::AccountId)));
}

QVariantMap AccountManager::getAccounts()
{
    QVariantMap accounts;

    // loop and just add those accounts from twitter
    Accounts::AccountIdList allAccounts = _man->accountList();

    for(int pos = 0; pos < allAccounts.length(); ++pos)
    {
        Accounts::Account* acc = _man->account(allAccounts.at(pos));
        if(acc->providerName() == "twitter")
            accounts[acc->displayName()] = QVariant(acc->id());
    }
    return accounts;
}

bool AccountManager::isTwitterAccount(Accounts::AccountId acc_id)
{
    Accounts::Account* acc = _man->account(acc_id);
    return acc->providerName() == "twitter";
}

void AccountManager::onAccountCreated(Accounts::AccountId acc_id)
{
    if(isTwitterAccount(acc_id))
        emit accountCreated(acc_id);
}

void AccountManager::onAccountDeleted(Accounts::AccountId acc_id)
{
    if(isTwitterAccount(acc_id))
        emit accountDeleted(acc_id);
}

void AccountManager::onAccountUpdated(Accounts::AccountId acc_id)
{
    if(isTwitterAccount(acc_id))
        emit accountUpdated(acc_id);
}
