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

    static QString CONSUMER_KEY;
    static QString CONSUMER_SECRET;
    static QString REQUEST_ENDPOINT;
    static QString TOKEN_ENDPOINT;
    static QString AUTHERIZATION_ENDPOINT;
    static QString CALLBACK_ENDPOINT;

    Accounts::Account* _acc;
    Account* q_ptr;
    Accounts::AccountService* _serv;

    SignOn::Identity* _identity;
    SignOn::AuthSession* _session;

    QString _consumerKey;
    QString _consumerSecret;
    QString _token;
    QString _tokenSecret;

    // mutex to ensure that we do not try to auth to many times
    QMutex _mutex;

};

QString AccountPrivate::CONSUMER_KEY = "ConsumerKey";
QString AccountPrivate::CONSUMER_SECRET = "ConsumerSecret";
QString AccountPrivate::REQUEST_ENDPOINT = "RequestEndpoint";
QString AccountPrivate::TOKEN_ENDPOINT = "TokenEndpoint";
QString AccountPrivate::AUTHERIZATION_ENDPOINT = "AuthorizationEndpoint";
QString AccountPrivate::CALLBACK_ENDPOINT = "Callback";

AccountPrivate::AccountPrivate(Accounts::Account* acc, Account* parent) :
    _acc(acc),
    q_ptr(parent),
    _session(0)
{
    _identity = SignOn::Identity::newIdentity(SignOn::IdentityInfo(), q_ptr);

    QList<Accounts::Service> services = _acc->services();

    // TODO: what happens when we have more than one service??
    _serv = new Accounts::AccountService(_acc, services.at(0));

}

void AccountPrivate::authenticate()
{
    Q_Q(Account);

    // lock and either unlock because we already have the data or in the call backs

    _mutex.lock();

    if (_consumerKey.isEmpty()
        || _consumerSecret.isEmpty()
        || _token.isEmpty()
        || _tokenSecret.isEmpty()) // we are not auth already
    {
        // TODO: look into keyring
        Accounts::AuthData authData = _serv->authData();
        QVariantMap params = authData.parameters();

        // store them to simplify the retrieval for the oauth header signature
        _consumerKey = params[AccountPrivate::CONSUMER_KEY].toString().toUtf8();
        _consumerSecret = params[AccountPrivate::CONSUMER_SECRET].toString().toUtf8();

        SignOn::AuthSession *_session = _identity->createSession(authData.method());
        q->connect(_session, SIGNAL(response(const SignOn::SessionData &)),
            q, SLOT(onResponse(const SignOn::SessionData &)));
        q->connect(_session, SIGNAL(error(const SignOn::Error &)),
            q, SLOT(onError(const SignOn::Error &)));

        OAuthData data;
        data.setRequestEndpoint(params[AccountPrivate::REQUEST_ENDPOINT].toString());
        data.setTokenEndpoint(params[AccountPrivate::TOKEN_ENDPOINT].toString());
        data.setAuthorizationEndpoint(params[AccountPrivate::AUTHERIZATION_ENDPOINT].toString());
        data.setConsumerKey(_consumerKey);
        data.setConsumerSecret(_consumerSecret);
        data.setCallback(params[AccountPrivate::CALLBACK_ENDPOINT].toString());
        data.setRealm("");
        data.setUserName(_acc->displayName());

        _session->process(data, authData.mechanism());
    }
    else
    {
        // emit signal we already have the data :)
        q->authenticated();
        _mutex.unlock();
    }
}

void AccountPrivate::onResponse(const SignOn::SessionData& sessionData)
{
    Q_Q(Account);
    qDebug() << "Authentication done";
    OAuthTokenData response = sessionData.data<OAuthTokenData>();
    _token = response.AccessToken();
    _tokenSecret = response.TokenSecret();

    // TODO: store in keyring

    // emit signal and unlock
    q->authenticated();
    _mutex.unlock();
}

void AccountPrivate::onError(const SignOn::Error& error)
{
    Q_Q(Account);
    qDebug() << "Got error:" << error.message();
    q->authenticationError(0, error.message());
    _mutex.unlock();
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
