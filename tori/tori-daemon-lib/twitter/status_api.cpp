/**
 *
 * Copyright (c) 2013 mandel
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

#include <QNetworkRequest>
#include <QDebug>
#include <QSharedPointer>
#include <QUrl>
#include "oauth_signal_mapper.h"
#include "status_api.h"
#include "oauth_utils.h"

namespace tori
{

namespace twitter
{

class TweetData : public QObject
{
public:
    TweetData(QObject* parent=0):
        QObject(parent)
    {
    }

    TweetData(QString uuid, qlonglong tweetId, QVariantMap options, QObject* parent=0)
        : QObject(parent),
        _uuid(uuid),
        _tweetId(tweetId),
        _options(options)
    {
    }

    ~TweetData() {}

    QString uuid(){return _uuid;}
    qlonglong tweetId(){return _tweetId;}
    QVariantMap options(){return _options;}

private:
    Q_DISABLE_COPY(TweetData)

private:
    QString _uuid;
    qlonglong _tweetId;
    QVariantMap _options;
};

class UpdateData : public QObject
{
public:
    UpdateData(QObject* parent=0):
        QObject(parent)
    {
        _uuid = "";
        _status = "";
    }

    UpdateData(QString uuid, QString status, QVariantMap options, QObject* parent=0)
        : QObject(parent),
        _uuid(uuid),
        _status(status),
        _options(options)
    {
        _uuid = uuid;
        _status = status;
        _options = options;
    }

    ~UpdateData() {}

    QString uuid() {return _uuid;}
    QString status() {return _status;}
    QVariantMap options() {return _options;}

private:
    Q_DISABLE_COPY(UpdateData)

private:
    QString _uuid;
    QString _status;
    QVariantMap _options;
};

class StatusAPIPrivate
{
    Q_DECLARE_PUBLIC(StatusAPI)
public:
    StatusAPIPrivate(tori::core::Account* acc, StatusAPI* parent);

    void retweets(QString uuid, qlonglong tweet_id, QVariantMap options);
    void show(QString uuid, qlonglong tweet_id, QVariantMap options);
    void destroy(QString uuid, qlonglong tweet_id, QVariantMap options);
    void update(QString uuid, QString status, QVariantMap options);
    void retweet(QString uuid, qlonglong tweet_id, QVariantMap options);

protected:
    KQOAuthRequest* createOAuthRequest(QString url, KQOAuthRequest::RequestHttpMethod method);

    void onUpdateFinished(QByteArray response, UpdateData* data);
    void onDestroyFinished(QByteArray response, TweetData* data);
    void onShowFinished(QByteArray response, TweetData* data);
    void onRetweetsFinished(QByteArray response, TweetData* data);
    void onRetweetFinished(QByteArray response, TweetData* data);

private:
    static const QString SHOW_URL;
    static const QString RETWEETS_URL;
    static const QString DESTROY_URL;
    static const QString UPDATE_URL;
    static const QString RETWEET_URL;

    StatusAPI* q_ptr;
    QSharedPointer<tori::core::Account> _acc;
    OAuthSignalMapper* _updateMapper;
    OAuthSignalMapper* _destroyMapper;
    OAuthSignalMapper* _showMapper;
    OAuthSignalMapper* _retweetsMapper;
    OAuthSignalMapper* _retweetMapper;
};

const QString StatusAPIPrivate::SHOW_URL = "https://api.twitter.com/1.1/statuses/show.json";
const QString StatusAPIPrivate::RETWEETS_URL = "https://api.twitter.com/1.1/statuses/retweet/%1.json";
const QString StatusAPIPrivate::DESTROY_URL = "https://api.twitter.com/1.1/statuses/destroy/%1.json ";
const QString StatusAPIPrivate::UPDATE_URL = "https://api.twitter.com/1.1/statuses/update.json";
const QString StatusAPIPrivate::RETWEET_URL = "https://api.twitter.com/1.1/statuses/retweet/%1.json";

StatusAPIPrivate::StatusAPIPrivate(tori::core::Account* acc, StatusAPI* parent) :
    q_ptr(parent),
    _acc(acc)
{
    Q_Q(StatusAPI);
    qRegisterMetaType<UpdateData*>("UpdateData*");
    qRegisterMetaType<TweetData*>("TweetData*");

    SETUP_OAUTH_MAPPER(_updateMapper, onUpdateFinished, UpdateData)
    SETUP_OAUTH_MAPPER(_destroyMapper, onDestroyFinished, TweetData)
    SETUP_OAUTH_MAPPER(_showMapper, onShowFinished, TweetData)
    SETUP_OAUTH_MAPPER(_retweetsMapper, onRetweetsFinished, TweetData)
    SETUP_OAUTH_MAPPER(_retweetMapper, onRetweetFinished, TweetData)

}

KQOAuthRequest* StatusAPIPrivate::createOAuthRequest(QString url, KQOAuthRequest::RequestHttpMethod method)
{
    KQOAuthRequest* oauthRequest = new KQOAuthRequest();

    oauthRequest->initRequest(KQOAuthRequest::AuthorizedRequest, QUrl(url));
    oauthRequest->setConsumerKey(_acc->consumerKey());
    oauthRequest->setConsumerSecretKey(_acc->consumerSecret());
    oauthRequest->setToken(_acc->tokenKey());
    oauthRequest->setTokenSecret(_acc->tokenSecret());
    oauthRequest->setHttpMethod(method);

    return oauthRequest;
}

void StatusAPIPrivate::retweets(QString uuid, qlonglong tweet_id, QVariantMap options)
{
    qDebug() << "retweets(" << tweet_id << ")";
    Q_Q(StatusAPI);
    TweetData* tweetData = new TweetData(uuid, tweet_id, options);

    SET_OAUTH_MANAGER(man, _retweetsMapper, tweetData)

    KQOAuthRequest* oauthRequest = createOAuthRequest(StatusAPIPrivate::RETWEETS_URL.arg(tweet_id), KQOAuthRequest::GET);
    KQOAuthParameters params;

    ADD_OPTIONAL_PARAMETER(options, "trim_user", params, options["trim_user"].toBool()? "true" : "false")
    ADD_OPTIONAL_PARAMETER(options, "counts", params, QString::number(options["count"].toInt()))

    oauthRequest->setAdditionalParameters(params);
    man->executeRequest(oauthRequest);
}

void StatusAPIPrivate::onRetweetsFinished(QByteArray response, TweetData* data)
{
    Q_Q(StatusAPI);
    QString jsonString(response);
    qDebug() << jsonString;
}

void StatusAPIPrivate::show(QString uuid, qlonglong tweet_id, QVariantMap options)
{

    qDebug() << "show(" << tweet_id << ")";
    Q_Q(StatusAPI);
    TweetData* tweetData = new TweetData(uuid, tweet_id, options);

    SET_OAUTH_MANAGER(man, _showMapper, tweetData)

    KQOAuthRequest* oauthRequest = createOAuthRequest(StatusAPIPrivate::SHOW_URL, KQOAuthRequest::GET);
    KQOAuthParameters params;
    params.insert("id", QString::number(tweet_id));

    ADD_OPTIONAL_PARAMETER(options, "trim_user", params, options["trim_user"].toBool()? "true" : "false")
    ADD_OPTIONAL_PARAMETER(options, "include_my_retweet", params, options["include_my_retweet"].toBool()? "true" : "false")
    ADD_OPTIONAL_PARAMETER(options, "include_entities", params, options["include_entities"].toBool()? "true" : "false")

    oauthRequest->setAdditionalParameters(params);
    man->executeRequest(oauthRequest);
}

void StatusAPIPrivate::onShowFinished(QByteArray response, TweetData* data)
{
    Q_Q(StatusAPI);
    QString jsonString(response);
    qDebug() << jsonString;
}

void StatusAPIPrivate::destroy(QString uuid, qlonglong tweet_id, QVariantMap options)
{
    qDebug() << "destroy(" << tweet_id << ")";
    Q_Q(StatusAPI);
    TweetData* tweetData = new TweetData(uuid, tweet_id, options);

    SET_OAUTH_MANAGER(man, _destroyMapper, tweetData)

    KQOAuthRequest* oauthRequest = createOAuthRequest(StatusAPIPrivate::DESTROY_URL.arg(tweet_id), KQOAuthRequest::POST);
    KQOAuthParameters params;

    ADD_OPTIONAL_PARAMETER(options, "trim_user", params, options["trim_user"].toBool()? "true" : "false")

    oauthRequest->setAdditionalParameters(params);
    man->executeRequest(oauthRequest);
}

void StatusAPIPrivate::onDestroyFinished(QByteArray response, TweetData* data)
{
    Q_Q(StatusAPI);
    QString jsonString(response);
    qDebug() << jsonString;
}

void StatusAPIPrivate::update(QString uuid, QString status, QVariantMap options)
{
    qDebug() << "update(" << status << ")";
    Q_Q(StatusAPI);
    UpdateData* update = new UpdateData(uuid, status, options);

    SET_OAUTH_MANAGER(man, _updateMapper, update)

    KQOAuthRequest* oauthRequest = createOAuthRequest(StatusAPIPrivate::UPDATE_URL, KQOAuthRequest::POST);

    KQOAuthParameters params;
    params.insert("status", status);

    ADD_OPTIONAL_PARAMETER(options, "trim_user", params, options["trim_user"].toBool()? "true" : "false")
    ADD_OPTIONAL_PARAMETER(options, "in_reply_to_status_id", params, QString::number(options["in_reply_to_status_id"].toInt()))
    ADD_OPTIONAL_PARAMETER(options, "latitude", params, QString::number(options["latitude"].toDouble()))
    ADD_OPTIONAL_PARAMETER(options, "longitude", params, QString::number(options["longitude"].toDouble()))
    ADD_OPTIONAL_PARAMETER(options, "place_id", params, options["place_id"].toString())
    ADD_OPTIONAL_PARAMETER(options, "display_coordinates", params, options["display_coordinates"].toBool()? "true" : "false")

    oauthRequest->setAdditionalParameters(params);
    man->executeRequest(oauthRequest);

}

void StatusAPIPrivate::onUpdateFinished(QByteArray response, UpdateData* data)
{
    Q_Q(StatusAPI);
    QString jsonString(response);
    qDebug() << jsonString;
}

void StatusAPIPrivate::retweet(QString uuid, qlonglong tweet_id, QVariantMap options)
{
    qDebug() << "retweet(" << tweet_id << ")";
    Q_Q(StatusAPI);
    TweetData* tweetData = new TweetData(uuid, tweet_id, options);

    SET_OAUTH_MANAGER(man, _destroyMapper, tweetData)

    KQOAuthRequest* oauthRequest = createOAuthRequest(StatusAPIPrivate::RETWEET_URL.arg(tweet_id), KQOAuthRequest::POST);
    KQOAuthParameters params;

    ADD_OPTIONAL_PARAMETER(options, "trim_user", params, options["trim_user"].toBool()? "true" : "false")

    oauthRequest->setAdditionalParameters(params);
    man->executeRequest(oauthRequest);
}

void StatusAPIPrivate::onRetweetFinished(QByteArray response, TweetData* data)
{
    Q_Q(StatusAPI);
    QString jsonString(response);
    qDebug() << jsonString;
}

StatusAPI::StatusAPI(tori::core::Account* acc, QObject *parent) :
    QObject(parent),
    d_ptr(new StatusAPIPrivate(acc, this))
{
}

StatusAPI::~StatusAPI()
{
}

void StatusAPI::retweets(QString uuid, qlonglong tweet_id, QVariantMap options)
{
    Q_D(StatusAPI);
    d->retweets(uuid, tweet_id, options);
}

void StatusAPI::show(QString uuid, qlonglong tweet_id, QVariantMap options)
{
    Q_D(StatusAPI);
    d->show(uuid, tweet_id, options);
}

void StatusAPI::destroy(QString uuid, qlonglong tweet_id, QVariantMap options)
{
    Q_D(StatusAPI);
    d->destroy(uuid, tweet_id, options);
}

void StatusAPI::update(QString uuid, QString status, QVariantMap options)
{
    Q_D(StatusAPI);
    d->update(uuid, status, options);
}

void StatusAPI::retweet(QString uuid, qlonglong tweet_id, QVariantMap options)
{
    Q_D(StatusAPI);
    d->retweet(uuid, tweet_id, options);
}

} // twitter

} // tori

#include "moc_status_api.cpp"
