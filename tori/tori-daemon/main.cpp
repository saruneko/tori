#include <QCoreApplication>
#include <cstdio>
#include "accounts/accounts_manager.h"

int main(int argc, char *argv[])
{
    g_type_init();

    QCoreApplication a(argc, argv);

    AccountsManager man(0);

    QList<Account> accs = man.getAllAccounts();
    printf("Found %d accounts", accs.length());
    
    return a.exec();
}
