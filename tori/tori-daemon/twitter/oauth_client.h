#ifndef OAUTHCLIENT_H
#define OAUTHCLIENT_H

#include <Accounts/Account>
#include <Accounts/Manager>
#include <Accounts/AccountService>
#include <QByteArray>
#include <QObject>
#include <QtOAuth>

#include "../tori_dbus_daemon.h"

class OAuthClient: public QObject
{
    Q_OBJECT

public:
    static const QString REQUEST_TOKEN_URL;
    static const QString AUTHENTICATE_URL;
    static const QString ACCESS_TOKEN_URL;

    OAuthClient(Accounts::AccountId accountId, ToriDBusDaemon* parent);
    ~OAuthClient() {}

    // authenticate and try to get the tokens
    void authenticate();

    void setTokens(QByteArray token, QByteArray tokenSecret);

private:

    // load the consumer data from the account info
    void loadConsumerData();

    void onPinReceived(const QString& pin, uint account);

    // account info
    Accounts::Account* _acc;
    Accounts::AccountService* _serv;

    ToriDBusDaemon* _dbusDaemon;
    QOAuth::Interface* _oauth;

    // secrets
    QByteArray _consumerKey, _consumerSecret, _token, _tokenSecret;

};

#endif // OAUTHCLIENT_H

