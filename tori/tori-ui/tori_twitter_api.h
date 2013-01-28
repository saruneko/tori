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
    void update(QString user, QString status);
    void destroy(qlonglong twit_id);
    void retweet(qlonglong twit_id);
    void retweets(qlonglong twit_id);
    void show(qlonglong twit_id);

private:
    AccountManagerClient client;
    QHash<QString, AccountClient*> accountClients;

};

#endif // TORI_TWITTER_API_H
