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

#include "account.h"
#include <Accounts/AccountService>
#include <Accounts/AuthData>
#include <QMutex>
#include <QtOAuth>
#include <QxtLogger>


namespace tori
{

namespace core
{

class AccountPrivate
{
    Q_DECLARE_PUBLIC(Account)
public:
    AccountPrivate(Accounts::Account* acc, tori::keyring::Keyring* key, Account* parent, bool useDefault=false);

    void authenticate();
    void isAuthenticated();
    void setPin(const QString& pin);

protected:
    void onCredentialsFound(Accounts::AccountId id, QString token, QString tokenSecret, bool found);

private:
    static const QString REQUEST_TOKEN_URL;
    static const QString AUTHENTICATE_URL;
    static const QString ACCESS_TOKEN_URL;
    static const QString DEFAULT_TOKEN;
    static const QString DEFAULT_TOKEN_SECRET;

    Accounts::Account* _acc;
    tori::keyring::Keyring* _key;
    Account* q_ptr;
    Accounts::AccountService* _serv;
    QByteArray _consumerKey;
    QByteArray _consumerSecret;
    QByteArray _token;
    QByteArray _tokenSecret;
    QOAuth::Interface* _oauth;
    QMutex _mutex;
};

const QString AccountPrivate::REQUEST_TOKEN_URL = "https://api.twitter.com/oauth/request_token";
const QString AccountPrivate::AUTHENTICATE_URL = "https://api.twitter.com/oauth/authenticate";
const QString AccountPrivate::ACCESS_TOKEN_URL = "https://api.twitter.com/oauth/access_token";

// default values from gwibber
const QString AccountPrivate::DEFAULT_TOKEN = "IOW164CqEJdlrkXlrQ17GA";
const QString AccountPrivate::DEFAULT_TOKEN_SECRET = "mJ38xSp6kqUzB2XMOq9USrmTgWAXOqXpS0g6WUEk";

AccountPrivate::AccountPrivate(Accounts::Account* acc, tori::keyring::Keyring* key, Account* parent, bool useDefault) :
    _acc(acc),
    _key(key),
    q_ptr(parent)
{
    Q_Q(Account);
    QList<Accounts::Service> services = _acc->services();
    // TODO: what happens when we have more than one service??
    _serv = new Accounts::AccountService(_acc, services.at(0));

    Accounts::AuthData data = _serv->authData();
    QVariantMap params = data.parameters();

    _consumerKey = params["ConsumerKey"].toString().toUtf8();
    _consumerSecret = params["ConsumerSecret"].toString().toUtf8();

    _oauth = new QOAuth::Interface();
    _oauth->setRequestTimeout(10000);

    // connect to the keyring signal so that we can try and retrieve the token and token secret
    q->connect(_key, SIGNAL(credentialsFound(Accounts::AccountId, QString, QString, bool)),
            q, SLOT(onCredentialsFound(Accounts::AccountId, QString, QString, bool)));

    qxtLog->debug() << "ConsumerKey and ConsumerSecret retrieved";
    if (useDefault)
    {
        qxtLog->debug() << "Using default token and token secret.";
        _token = AccountPrivate::DEFAULT_TOKEN.toUtf8();
        _tokenSecret = AccountPrivate::DEFAULT_TOKEN_SECRET.toUtf8();
    }
}

void AccountPrivate::authenticate()
{
    Q_Q(Account);
    _mutex.lock();
    // lock just in case we have more than one client asking to auth the data

    if (_token.isEmpty() || _tokenSecret.isEmpty())
    {
        qxtLog->debug() << "Token and TokenSecret are empty";
        _oauth->setConsumerKey(_consumerKey);
        _oauth->setConsumerSecret(_consumerSecret);

        QOAuth::ParamMap args;
        args.insert("oauth_callback", "oob");

        QOAuth::ParamMap reply = _oauth->requestToken(AccountPrivate::REQUEST_TOKEN_URL ,
            QOAuth::POST, QOAuth::HMAC_SHA1, args);

        if (_oauth->error() == QOAuth::NoError)
        {
            _token = reply.value(QOAuth::tokenParameterName());
            _tokenSecret = reply.value(QOAuth::tokenSecretParameterName());
        }

        QString url = QString(AccountPrivate::AUTHENTICATE_URL);
        url.append("?");
        url.append(QOAuth::tokenParameterName() + "=" + _token);

        qxtLog->debug() << "Url for pin is:" << url;
        emit q->oauthPinUrl(url, _acc->displayName());
    }
    else
    {
        qxtLog->debug() << "Credentials already present.";
        emit q->authenticated(true, _acc->displayName());
    }
    _mutex.unlock();
}

void AccountPrivate::isAuthenticated()
{
    Q_Q(Account);
    qxtLog->debug() << "AccountPrivate::isAuthenticated()";

    // check if we do have the token and token secret
    if (_token.isEmpty() || _tokenSecret.isEmpty())
    {
        qxtLog->debug() << "Getting credentials from keyring for accoutn with id:" << _acc->id();
        _key->getCredentials(_acc->id());
    }
    else
    {
        qxtLog->debug() << "Credentials already present";
        emit q->authenticated(true, _acc->displayName());
    }
}

void AccountPrivate::setPin(const QString& pin)
{
    Q_Q(Account);
    _mutex.lock();
    // lock just in case we have more than one client asking to auth the data

    QOAuth::ParamMap args;
    args.insert("oauth_verifier", pin.toAscii());
    QOAuth::ParamMap reply = _oauth->accessToken(ACCESS_TOKEN_URL,
        QOAuth::GET, _token, _tokenSecret, QOAuth::HMAC_SHA1, args);

    if(_oauth->error() == QOAuth::NoError)
    {
        _token = reply.value(QOAuth::tokenParameterName());
        _tokenSecret = reply.value(QOAuth::tokenSecretParameterName());

        // store the tokens in the keyring
        _key->setCredentials(_acc->id(), _token, _tokenSecret);
        emit q->authenticated(true, _acc->displayName());
    }
    else
    {
        // send an error to the client
        emit q->authenticationError(_oauth->error());
    }
    _mutex.unlock();
}

void AccountPrivate::onCredentialsFound(Accounts::AccountId id, QString token, QString tokenSecret, bool found)
{
    Q_Q(Account);
    qxtLog->debug() << "AccountPrivate::onCredentialsFound for id:" << id  << "Was found:" << found;
    // onlye deal with the signal if it is our same account id
    if (_acc->id() == id)
    {
        if (found)
        {
            _token = token.toUtf8();
            _tokenSecret = tokenSecret.toUtf8();
            // do let the client that we are authenticated
            emit q->authenticated(true, _acc->displayName());
        }
        else
        {
            emit q->authenticated(false, _acc->displayName());
        }
    }
}

Account::Account(Accounts::Account* acc, tori::keyring::Keyring* key, bool useDefault,
    QObject *parent) : QObject(parent),
    d_ptr(new AccountPrivate(acc, key, this, useDefault))
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

void Account::isAuthenticated()
{
    Q_D(Account);
    d->isAuthenticated();
}

void Account::setPin(const QString& pin)
{
    Q_D(Account);
    d->setPin(pin);
}

} // core

} // tori

#include "moc_account.cpp"
