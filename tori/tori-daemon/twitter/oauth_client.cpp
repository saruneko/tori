#include <Accounts/Service>
#include <Accounts/AuthData>

#include "oauth_client.h"

const QString OAuthClient::REQUEST_TOKEN_URL = "https://api.twitter.com/oauth/request_token";
const QString OAuthClient::AUTHENTICATE_URL = "https://api.twitter.com/oauth/authenticate";
const QString OAuthClient::ACCESS_TOKEN_URL = "https://api.twitter.com/oauth/access_token";

OAuthClient::OAuthClient(Accounts::AccountId accountId, ToriDBusDaemon* parent)
    : QObject(parent)
{
    _dbusDaemon = parent;

    // connect to the signal of the pin retrieval
    connect(_dbusDaemon, SIGNAL(pinReceived(const QString&, uint)),
        this, SLOT(onPinReceived(const QString&, uint)));

    // load the account from the system and retrieve the required data
    Accounts::Manager man("microblogging");
    _acc = man.account(accountId);

    QList<Accounts::Service> services = _acc->services();

    // TODO: what happens when we have more than one service??
    _serv = new Accounts::AccountService(_acc, services.at(0));
    _oauth = new QOAuth::Interface();
    _oauth->setRequestTimeout(10000);

    _consumerKey = "";
    _consumerSecret = "";
    _token = "";
    _tokenSecret = "";
}


void OAuthClient::loadConsumerData()
{
    // load each of the consumer info
    Accounts::AuthData data = _serv->authData();
    QVariantMap params = data.parameters();

    if(_consumerKey == "")
        _consumerKey = params["ConsumerKey"].toString().toUtf8();

    if(_consumerSecret == "")
        _consumerSecret = params["ConsumerSecret"].toString().toUtf8();
}

void OAuthClient::onPinReceived(const QString& pin, uint account)
{
    // only deal with the pin if we have the same account
    if(account != _acc->id())
        return;

    QOAuth::ParamMap args;
    args.insert("oauth_verifier", pin.toAscii());
    QOAuth::ParamMap reply = _oauth->accessToken(ACCESS_TOKEN_URL,
        QOAuth::GET, _token, _tokenSecret, QOAuth::HMAC_SHA1, args);

    if(_oauth->error() == QOAuth::NoError)
    {
        _token = reply.value(QOAuth::tokenParameterName());
        _tokenSecret = reply.value(QOAuth::tokenSecretParameterName());

    }
    else
    {
//        qDebug() << "ERROR" << oauthInterface->error();
    }
}

void OAuthClient::authenticate()
{
    // if and only if we do not have the secrets we try to retrieve them  from
    // twitter
    if(_consumerKey == "" || _consumerSecret == "")
        loadConsumerData();

    _oauth->setConsumerKey(_consumerKey);
    _oauth->setConsumerSecret(_consumerSecret);

    QOAuth::ParamMap args;
    args.insert("oauth_callback", "oob");

    QOAuth::ParamMap reply = _oauth->requestToken(OAuthClient::REQUEST_TOKEN_URL ,
        QOAuth::POST, QOAuth::HMAC_SHA1, args);

    if(_oauth->error() == QOAuth::NoError)
    {
        _token = reply.value(QOAuth::tokenParameterName());
        _tokenSecret = reply.value(QOAuth::tokenSecretParameterName());
    }

    QString url = QString(OAuthClient::AUTHENTICATE_URL);
    url.append("?");
    url.append(QOAuth::tokenParameterName() + "=" + _token);
    _dbusDaemon->emitOAuthPinUrl(url, _acc->id(), _acc->displayName());
}
