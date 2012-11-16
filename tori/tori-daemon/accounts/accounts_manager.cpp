// Always include sigc BEFORE any Qt code
#include <sigc++/sigc++.h>
#include <glib.h>

#include "accounts_manager.h"



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
   g_list_free(raw_accs);

   return result;

}
