// Always include sigc BEFORE any Qt code
#include <sigc++/sigc++.h>

#include "accounts_manager.h"


Account::Account(AgAccountService *service, QObject* parent)
    : QObject(parent)
{
    _service = service;
}

QString Account::displayName()
{
    AgAccount* acc = ag_account_service_get_account(_service);
    return QString(ag_account_get_display_name(acc));
}

void Account::setDisplayName(QString name)
{
    AgAccount* acc = ag_account_service_get_account(_service);
    const char* new_name = name.toUtf8().data();

    ag_account_set_display_name(acc, new_name);
}

bool Account::enabled()
{
    AgAccount* acc = ag_account_service_get_account(_service);
    return ag_account_get_enabled(acc) == TRUE;
}

void Account::setEnabled(bool enabled)
{
    AgAccount* acc = ag_account_service_get_account(_service);

    if(enabled)
        ag_account_set_enabled(acc, TRUE);
    else
        ag_account_set_enabled(acc, FALSE);
}

QString Account::providerName()
{
    AgAccount* acc = ag_account_service_get_account(_service);
    return QString(ag_account_get_provider_name(acc));
}

AccountsManager::AccountsManager(QObject *parent) :
    QObject(parent)
{
    typedef glib::Signal<void, AgManager*, guint, gpointer> AccountSignalType;

    _manager = ag_manager_new_for_service_type("microblogging");

    _sig_manager.Add(new AccountSignalType(_manager, "account-created",
        sigc::mem_fun(this, &AccountsManager::onAccountCreated)));

    _sig_manager.Add(new AccountSignalType(_manager, "account-deleted",
        sigc::mem_fun(this, &AccountsManager::onAccountCreated)));

    _sig_manager.Add(new AccountSignalType(_manager, "account-updated",
        sigc::mem_fun(this, &AccountsManager::onAccountCreated)));

}

void AccountsManager::onAccountCreated(AgManager* man, guint accountId, gpointer userData)
{
   AgAccount* raw_acc = ag_manager_get_account(man, accountId);
   AgService* serv = ag_account_get_selected_service(raw_acc);
   Account acc(ag_account_service_new(raw_acc, serv));

   g_object_unref(raw_acc);
   g_object_unref(serv);

   emit accountCreated(acc);
}

void AccountsManager::onAccountDeleted(AgManager* man, guint accountId, gpointer userData)
{
   AgAccount* raw_acc = ag_manager_get_account(man, accountId);
   AgService* serv = ag_account_get_selected_service(raw_acc);
   Account acc(ag_account_service_new(raw_acc, serv));

   g_object_unref(raw_acc);
   g_object_unref(serv);

   emit accountDeleted(acc);
}

void AccountsManager::onAccountUpdated(AgManager* man, guint accountId, gpointer userData)
{
   AgAccount* raw_acc = ag_manager_get_account(man, accountId);
   AgService* serv = ag_account_get_selected_service(raw_acc);
   Account acc(ag_account_service_new(raw_acc, serv));

   g_object_unref(raw_acc);
   g_object_unref(serv);

   emit accountUpdated(acc);
}

QList<Account> AccountsManager::getAllAccounts()
{
   QList<Account> result;
   GList* raw_accs = ag_manager_get_account_services(_manager);

   for(guint pos = 0; pos < g_list_length(raw_accs); pos++)
   {
       AgAccountService* raw_acc = (AgAccountService*) g_list_nth_data(raw_accs, pos);
       Account acc(raw_acc);
       result.append(acc);
   }
   g_list_free_full(raw_accs, g_object_unref);

   return result;

}
