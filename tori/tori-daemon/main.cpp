#include <QCoreApplication>
#include <cstdio>
#include "accounts/accounts_manager.h"

int main(int argc, char *argv[])
{
    g_type_init();

    QCoreApplication a(argc, argv);

    AccountsManager man(0);

    QList<Account> accs = man.getAllAccounts();
    Account ac1 = accs.at(0);

    // get the provider name
    ac1.providerName();

    // get the auth data
    ac1.authData().parameters();
    
    return a.exec();
}
