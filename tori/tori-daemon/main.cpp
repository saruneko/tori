#include <QCoreApplication>
#include <glib.h>
#include <cstdio>
#include <libaccounts-glib/ag-manager.h>
#include <libaccounts-glib/ag-account.h>
#include <libaccounts-glib/ag-account-service.h>

int main(int argc, char *argv[])
{
    g_type_init();

    QCoreApplication a(argc, argv);

    // create a new ag manager and use it to get the information that is required to connect
    // to the twitter account
    AgManager* man = ag_manager_new_for_service_type("microblogging");
    GList* accounts = ag_manager_get_account_services(man);

    // print the diff accounts
    for(int pos = 0; pos < g_list_length(accounts); pos++)
    {
        AgAccountService* service = (AgAccountService*) g_list_nth_data(accounts, pos);
        AgAccount* acc = ag_account_service_get_account(service);
        printf("Found account %s\n", ag_account_get_display_name(acc));
    }
    
    return a.exec();
}
