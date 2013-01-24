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
#include <SignOn/Identity>
#include <SignOn/Error>
#include <SignOn/SessionData>
#include <QDebug>
#include <QMutex>
#include "account.h"

#include "twitter/status_api.h"


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
    AccountPrivate(Accounts::Account* acc, keyring::Keyring* key, KQOAuthManager* man, Account* parent);

    void authenticate();

    void destroy(const QString& uuid, uint tweet_id, const QVariantMap &options);
    void retweet(const QString& uuid, uint tweet_id, const QVariantMap &options);
    void retweets(const QString& uuid, uint tweet_id, const QVariantMap &options);
    void show(const QString& uuid, uint tweet_id, const QVariantMap &options);
    void update(const QString& uuid, const QString &status, const QVariantMap &options);

    void onResponse(const SignOn::SessionData& sessionData);
    void onError(const SignOn::Error& error);
    void onCredentialsFound(Accounts::AccountId accId, QString token, QString tokenSecret, bool found);

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
    QString _tokenKey;
    QString _tokenSecret;

    // mutex to ensure that we do not try to auth to many times
    QMutex _mutex;
    keyring::Keyring* _key;
    KQOAuthManager* _man;
    twitter::StatusAPI* _status;
};

QString AccountPrivate::CONSUMER_KEY = "ConsumerKey";
QString AccountPrivate::CONSUMER_SECRET = "ConsumerSecret";
QString AccountPrivate::REQUEST_ENDPOINT = "RequestEndpoint";
QString AccountPrivate::TOKEN_ENDPOINT = "TokenEndpoint";
QString AccountPrivate::AUTHERIZATION_ENDPOINT = "AuthorizationEndpoint";
QString AccountPrivate::CALLBACK_ENDPOINT = "Callback";

AccountPrivate::AccountPrivate(Accounts::Account* acc, keyring::Keyring* key, KQOAuthManager* man, Account* parent) :
    _acc(acc),
    _man(man),
    q_ptr(parent),
    _session(0),
    _key(key)
{
    Q_Q(Account);
    _identity = SignOn::Identity::newIdentity(SignOn::IdentityInfo(), q_ptr);

    QList<Accounts::Service> services = _acc->services();

    // TODO: what happens when we have more than one service??
    _serv = new Accounts::AccountService(_acc, services.at(0));

    q->connect(_key, SIGNAL(credentialsFound(Accounts::AccountId, QString, QString, bool)),
        q, SLOT(onCredentialsFound(Accounts::AccountId, QString, QString, bool)));

    _status = new twitter::StatusAPI(q_ptr, _man);
}

void AccountPrivate::authenticate()
{
    Q_Q(Account);

    // lock and either unlock because we already have the data or in the call backs

    _mutex.lock();

    if (_consumerKey.isEmpty()
        || _consumerSecret.isEmpty()
        || _tokenKey.isEmpty()
        || _tokenSecret.isEmpty()) // we are not auth already
    {
        // try to get the credentials form the keyring, if the are not found the onCredentialsFound callback will
        // take care of retrieving the creds from twitter
        _key->getCredentials(_acc->id());
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
    _tokenKey = response.AccessToken();
    _tokenSecret = response.TokenSecret();

    // store the creds in the keyring, lets ignore the signal because we already
    // have the token and token secret
    _key->setCredentials(_acc->id(), _tokenKey, _tokenSecret);

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

void AccountPrivate::onCredentialsFound(Accounts::AccountId accId, QString token, QString tokenSecret, bool found)
{
    Q_Q(Account);
    if (accId == _acc->id())
    {
        Accounts::AuthData authData = _serv->authData();
        QVariantMap params = authData.parameters();

        // store them to simplify the retrieval for the oauth header signature
        _consumerKey = params[AccountPrivate::CONSUMER_KEY].toString().toUtf8();
        _consumerSecret = params[AccountPrivate::CONSUMER_SECRET].toString().toUtf8();

        if (found)
        {
            qDebug() << "Token and token secret were found in the keyring.";
            _tokenKey = token;
            _tokenSecret = tokenSecret;

            // emit and unlock mutex
            q->authenticated();
            _mutex.unlock();
        }
        else
        {
            qDebug() << "Token and token secret were not found in the keyring.";
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
    }
}

void AccountPrivate::destroy(const QString& uuid, uint tweet_id, const QVariantMap &options)
{
    _status->destroy(uuid, tweet_id, options);
}

void AccountPrivate::retweet(const QString& uuid, uint tweet_id, const QVariantMap &options)
{
    _status->retweet(uuid, tweet_id, options);
}

void AccountPrivate::retweets(const QString& uuid, uint tweet_id, const QVariantMap &options)
{
    _status->retweets(uuid, tweet_id, options);
}

void AccountPrivate::show(const QString& uuid, uint tweet_id, const QVariantMap &options)
{
    _status->show(uuid, tweet_id, options);
}

void AccountPrivate::update(const QString& uuid, const QString &status, const QVariantMap &options)
{
    _status->update(uuid, status, options);
}


Account::Account(Accounts::Account* acc, keyring::Keyring* key, KQOAuthManager* man, QObject *parent) : QObject(parent),
    d_ptr(new AccountPrivate(acc, key, man, this))
{
}

Account::~Account()
{
}

void Account::authenticate()
{
    Q_D(Account);
    d->authenticate();
}

QString Account::tokenKey()
{
    Q_D(Account);
    return d->_tokenKey;
}

QString Account::tokenSecret()
{
    Q_D(Account);
    return d->_tokenSecret;
}

QString Account::consumerKey()
{
    Q_D(Account);
    return d->_consumerKey;
}

QString Account::consumerSecret()
{
    Q_D(Account);
    return d->_consumerSecret;
}

void Account::destroy(const QString& uuid, uint tweet_id, const QVariantMap &options)
{
    Q_D(Account);
    d->destroy(uuid, tweet_id, options);
}

void Account::retweet(const QString& uuid, uint tweet_id, const QVariantMap &options)
{
    Q_D(Account);
    d->retweet(uuid, tweet_id, options);
}

void Account::retweets(const QString& uuid, uint tweet_id, const QVariantMap &options)
{
    Q_D(Account);
    d->retweets(uuid, tweet_id, options);
}

void Account::show(const QString& uuid, uint tweet_id, const QVariantMap &options)
{
    Q_D(Account);
    d->show(uuid, tweet_id, options);
}

void Account::update(const QString& uuid, const QString &status, const QVariantMap &options)
{
    Q_D(Account);
    d->update(uuid, status, options);
}

} // core

} // tori

#include "moc_account.cpp"
