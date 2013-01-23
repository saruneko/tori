/**
 *
 * Copyright (c) 2012 mandel
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <Accounts/AccountService>
#include <Accounts/AuthData>
#include <SignOn/AuthSession>
#include <SignOn//Identity>
#include <SignOn//Error>
#include <SignOn/SessionData>
#include <QDebug>
#include <QMutex>
#include "account.h"


namespace tori
{

namespace core
{

class OAuthData : public SignOn::SessionData
{
public:
    SIGNON_SESSION_DECLARE_PROPERTY(QString, RequestEndpoint)
    SIGNON_SESSION_DECLARE_PROPERTY(QString, TokenEndpoint)
    SIGNON_SESSION_DECLARE_PROPERTY(QString, AuthorizationEndpoint)
    SIGNON_SESSION_DECLARE_PROPERTY(QString, ConsumerKey)
    SIGNON_SESSION_DECLARE_PROPERTY(QString, ConsumerSecret)
    SIGNON_SESSION_DECLARE_PROPERTY(QString, Callback)
    SIGNON_SESSION_DECLARE_PROPERTY(QString, Realm)
    SIGNON_SESSION_DECLARE_PROPERTY(QString, UserName)
};

class OAuthTokenData : public SignOn::SessionData
{
public:
    OAuthTokenData(const QVariantMap &data = QVariantMap()):
        SignOn::SessionData(data) {}

    SIGNON_SESSION_DECLARE_PROPERTY(QString, AccessToken)
    SIGNON_SESSION_DECLARE_PROPERTY(QString, TokenSecret)
    SIGNON_SESSION_DECLARE_PROPERTY(QString, UserId)
    SIGNON_SESSION_DECLARE_PROPERTY(QString, ScreenName)
};


class AccountPrivate
{
    Q_DECLARE_PUBLIC(Account)
public:
    AccountPrivate(Accounts::Account* acc, Account* parent);

    void authenticate();
    void onResponse(const SignOn::SessionData& sessionData);
    void onError(const SignOn::Error& error);

private:
    static const QString DEFAULT_TOKEN;
    static const QString DEFAULT_TOKEN_SECRET;

    Accounts::Account* _acc;
    Account* q_ptr;
    Accounts::AccountService* _serv;

    SignOn::Identity* _identity;
    SignOn::AuthSession* _session;

    QString _consumerKey;
    QString _consumerSecret;
    QString _token;
    QString _tokenSecret;

};

// default values from gwibber
const QString AccountPrivate::DEFAULT_TOKEN = "IOW164CqEJdlrkXlrQ17GA";
const QString AccountPrivate::DEFAULT_TOKEN_SECRET = "mJ38xSp6kqUzB2XMOq9USrmTgWAXOqXpS0g6WUEk";

AccountPrivate::AccountPrivate(Accounts::Account* acc, Account* parent) :
    _acc(acc),
    q_ptr(parent),
    _session(0)
{
    _identity = SignOn::Identity::newIdentity(SignOn::IdentityInfo(), q_ptr);

    QList<Accounts::Service> services = _acc->services();

    // TODO: what happens when we have more than one service??
    _serv = new Accounts::AccountService(_acc, services.at(0));

    Accounts::AuthData data = _serv->authData();
    QVariantMap params = data.parameters();
    foreach(QString key, params.keys())
    {
        qDebug() << key << " with data " << params[key];
    }

    _consumerKey = params["ConsumerKey"].toString().toUtf8();
    _consumerSecret = params["ConsumerSecret"].toString().toUtf8();

}

void AccountPrivate::authenticate()
{
    Q_Q(Account);
    SignOn::AuthSession *_session = _identity->createSession("oauth2");
    q->connect(_session, SIGNAL(response(const SignOn::SessionData &)),
        q, SLOT(onResponse(const SignOn::SessionData &)));
    q->connect(_session, SIGNAL(error(const SignOn::Error &)),
        q, SLOT(onError(const SignOn::Error &)));

    OAuthData data;
    data.setRequestEndpoint("https://api.twitter.com/oauth/request_token");
    data.setTokenEndpoint("https://api.twitter.com/oauth/access_token");
    data.setAuthorizationEndpoint("https://api.twitter.com/oauth/authorize");
    data.setConsumerKey(_consumerKey);
    data.setConsumerSecret(_consumerSecret);
    data.setCallback("https://wiki.ubuntu.com/");
    data.setRealm("");
    data.setUserName(_acc->displayName());

    _session->process(data, "user_agent");

}

void AccountPrivate::onResponse(const SignOn::SessionData& sessionData)
{
    OAuthTokenData response = sessionData.data<OAuthTokenData>();
    qDebug() << "Access token:" << response.AccessToken();
    qDebug() << "Access secret:" << response.TokenSecret();
}

void AccountPrivate::onError(const SignOn::Error& error)
{
    qDebug() << "Got error:" << error.message();
}

Account::Account(Accounts::Account* acc, QObject *parent) : QObject(parent),
    d_ptr(new AccountPrivate(acc, this))
{
}

void Account::authenticate()
{
    Q_D(Account);
    d->authenticate();
}

Account::~Account()
{
}

} // core

} // tori

#include "moc_account.cpp"
