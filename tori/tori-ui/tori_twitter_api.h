#ifndef TORI_TWITTER_API_H
#define TORI_TWITTER_API_H

#include <QObject>
#include <QQuickItem>
#include <QHash>
#include <QString>
#include <client/account_manager_client.h>
#include <client/account_client.h>

class ToriTwitterAPI : public QObject
{
    Q_OBJECT
public:
    explicit ToriTwitterAPI(QQuickItem *root, QObject *parent = 0);

    void getAccounts();

signals:

public slots:
    void update(QString user, QString status);
    void destroy(QString user, qlonglong twit_id);
    void retweet(QString user, qlonglong twit_id);
    void retweets(QString user, qlonglong twit_id);
    void show(QString user, qlonglong twit_id);

private:
    QQuickItem *_root;
    AccountManagerClient client;
    QHash<QString, AccountClient*> accountClients;

};

#endif // TORI_TWITTER_API_H
