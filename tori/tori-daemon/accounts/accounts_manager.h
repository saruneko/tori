#ifndef ACCOUNTS_MANAGER_H
#define ACCOUNTS_MANAGER_H

#include <QObject>
#include <QList>

// Imports required to access the account info

#include <glib.h>
#include <libaccounts-glib/ag-manager.h>
#include <libaccounts-glib/ag-account.h>
#include <libaccounts-glib/ag-account-service.h>
#include "glib/GLibSignal.h"

class Account : public QObject
{
    friend class AccountManager;

    Q_OBJECT

public:
    explicit Account(AgAccountService* service, QObject* parent = 0);
    Account(const Account&) : QObject() {}

    QString displayName();

    void setDisplayName(QString name);

    bool enabled();

    void setEnabled(bool enabled);

    QString providerName();


private:
    AgAccountService* _service;
};

class AccountsManager : public QObject
{
    Q_OBJECT

public:

    explicit AccountsManager(QObject *parent = 0);

    /**
     * Load all the accounts known by the user.
     */
    QList<Account> getAllAccounts();

    /**
     * Get the account with the given id.
     */
    Account getAccount(guint acc_id);

signals:
    void accountCreated(const Account&);
    void accountDeleted(const Account&);
    void accountUpdated(const Account&);

private:
    void onAccountCreated(AgManager* man, guint accountId, gpointer userData);
    void onAccountDeleted(AgManager* man, guint accountId, gpointer userData);
    void onAccountUpdated(AgManager* man, guint accountId, gpointer userData);

    AgManager* _manager;
    glib::SignalManager _sig_manager;

};

#endif // ACCOUNTS_MANAGER_H
