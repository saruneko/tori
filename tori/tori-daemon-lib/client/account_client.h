#ifndef ACCOUNT_CLIENT_H
#define ACCOUNT_CLIENT_H

#include <QObject>
#include <QString>
#include "account_proxy.h"

class AccountClient : public QObject
{
    Q_OBJECT
public:
    explicit AccountClient(QString service, QObject *parent = 0);

    void authenticate();
    void update(QString& status);
    void destroy(qlonglong twit_id);
    void retweet(qlonglong twit_id);
    void retweets(qlonglong twit_id);
    void show(qlonglong twit_id);


signals:

private slots:
    void userAuthenticated();
    void authenticationError(uint, QString);

private:
    AccountProxy* proxy;

};

#endif // ACCOUNT_CLIENT_H
