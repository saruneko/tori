#ifndef ACCOUNT_MANAGER_CLIENT_H
#define ACCOUNT_MANAGER_CLIENT_H

#include <QObject>
#include "account_manager_proxy.h"

class AccountManagerClient : public QObject
{
    Q_OBJECT
public:
    explicit AccountManagerClient(QObject *parent = 0);

    QHash<QString, QDBusObjectPath> getAccounts();

signals:

public slots:

private:
    AccountManagerProxy* client;

};

#endif // ACCOUNT_MANAGER_CLIENT_H
