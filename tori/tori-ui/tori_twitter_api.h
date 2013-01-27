#ifndef TORI_TWITTER_API_H
#define TORI_TWITTER_API_H

#include <QObject>
#include <QHash>
#include <QString>
#include <client/account_manager_client.h>
#include <client/account_client.h>

class ToriTwitterAPI : public QObject
{
    Q_OBJECT
public:
    explicit ToriTwitterAPI(QObject *parent = 0);

    void getAccounts();

signals:

public slots:

private:
    AccountManagerClient client;
    QHash<QString, AccountClient*> accountClients;

};

#endif // TORI_TWITTER_API_H
