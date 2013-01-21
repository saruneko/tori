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
#include "status_api.h"

namespace tori
{

namespace twitter
{

class StatusAPIPrivate
{
    Q_DECLARE_PUBLIC(StatusAPI)
public:
    StatusAPIPrivate(OAuth* oauth, QNetworkAccessManager* man, StatusAPI* parent);

    void retweets(QString uuid, uint tweet_id, QVariantMap options);
    void show(QString uuid, uint tweet_id, QVariantMap options);
    void destroy(QString uuid, uint tweet_id, QVariantMap options);
    void update(QString uuid, QString status, QVariantMap options);
    void retweet(QString uuid, uint tweet_id, QVariantMap options);

protected:
    void onUpdateFinished();
    void onUpdateError(QNetworkReply::NetworkError error);

private:
    static const QString SHOW_URL;
    static const QString RETWEETS_URL;
    static const QString DESTROY_URL;
    static const QString UPDATE_URL;
    static const QString RETWEET_URL;

    StatusAPI* q_ptr;
    QSharedPointer<OAuth> _oauth;
    QSharedPointer<QNetworkAccessManager> _man;
};

const QString StatusAPIPrivate::SHOW_URL = "https://api.twitter.com/1.1/statuses/show.json";
const QString StatusAPIPrivate::RETWEETS_URL = "https://api.twitter.com/1.1/statuses/retweet/%1.json";
const QString StatusAPIPrivate::DESTROY_URL = "https://api.twitter.com/1.1/statuses/destroy/%1.json ";
const QString StatusAPIPrivate::UPDATE_URL = "https://api.twitter.com/1.1/statuses/update.json";
const QString StatusAPIPrivate::RETWEET_URL = "https://api.twitter.com/1.1/statuses/retweet/%1.json";

StatusAPIPrivate::StatusAPIPrivate(OAuth* oauth, QNetworkAccessManager* man, StatusAPI* parent) :
    q_ptr(parent),
    _oauth(oauth),
    _man(man)
{
}

void StatusAPIPrivate::retweets(QString uuid, uint tweet_id, QVariantMap options)
{
    qDebug() << "retweets(" << tweet_id << ")";

    QUrl url(StatusAPIPrivate::RETWEETS_URL.arg(tweet_id));
    if (options.contains("trim_user"))
    {
        qDebug() << "trim_user" << options["trim_user"];
        url.addQueryItem("trim_user", options["trim_user"].toBool()? "true" : "false");
    }
    if (options.contains("counts"))
    {
        qDebug() << "counts" << options["counts"];
        url.addQueryItem("count", QString::number(options["count"].toInt()));
    }

    QNetworkRequest req(url);
    req.setRawHeader(OAuth::AUTH_HEADER, _oauth->generateAuthorizationHeader(url, OAuth::GET));
    QNetworkReply *reply = _man->get(req);

    // TODO: connect to reply signal
}

void StatusAPIPrivate::show(QString uuid, uint tweet_id, QVariantMap options)
{
    qDebug() << "show(" << tweet_id << ")";

    QUrl url(StatusAPIPrivate::SHOW_URL);

    // add the parameters
    url.addQueryItem("id", QString::number(tweet_id));
    if (options.contains("trim_user"))
    {
        qDebug() << "trim_user" << options["trim_user"];
        url.addQueryItem("trim_user", options["trim_user"].toBool()? "true" : "false");
    }
    if (options.contains("include_my_retweet"))
    {
        qDebug() << "include_my_retweet" << options["include_my_retweet"];
        url.addQueryItem("include_my_retweet", options["include_my_retweet"].toBool()? "true" : "false");
    }
    if (options.contains("include_entities"))
    {
        qDebug() << "include_entities" << options["include_entities"];
        url.addQueryItem("include_entities", options["include_entities"].toBool()? "true" : "false");
    }

    QNetworkRequest req(url);
    req.setRawHeader(OAuth::AUTH_HEADER, _oauth->generateAuthorizationHeader(url, OAuth::GET));
    QNetworkReply *reply = _man->get(req);

    // TODO: connect to reply signal
}

void StatusAPIPrivate::destroy(QString uuid, uint tweet_id, QVariantMap options)
{
    qDebug() << "destroy(" << tweet_id << ")";
    QUrl url(StatusAPIPrivate::DESTROY_URL.arg(tweet_id));

    if (options.contains("trim_user"))
    {
        qDebug() << "trim_user" << options["trim_user"];
        url.addQueryItem("trim_user", options["trim_user"].toBool()? "true" : "false");
    }

    QNetworkRequest req(url);
    req.setRawHeader(OAuth::AUTH_HEADER, _oauth->generateAuthorizationHeader(url, OAuth::POST));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QNetworkReply *reply = _man->post(req, QByteArray());

    // TODO: connecto to reply signal
}

void StatusAPIPrivate::update(QString uuid, QString status, QVariantMap options)
{
    Q_Q(StatusAPI);
    QUrl url(StatusAPIPrivate::UPDATE_URL);
    qDebug() << "show(" << status << ")";
    url.addQueryItem("status", status);

    if (options.contains("in_reply_to_status_id"))
    {
        qDebug() << "in_reply_to_status_id" << options["in_reply_to_status_id"];
        url.addQueryItem("in_reply_to_status_id", QString::number(options["in_reply_to_status_id"].toInt()));
    }
    if (options.contains("latitude"))
    {
        qDebug() << "latitude" << options["latitude"];
        url.addQueryItem("latitude", QString::number(options["latitude"].toDouble()));
    }
    if (options.contains("longitude"))
    {
        qDebug() << "longitude" << options["longitude"];
        url.addQueryItem("longitude", QString::number(options["longitude"].toDouble()));
    }
    if (options.contains("place_id"))
    {
        qDebug() << "place_id" << options["place_id"];
        url.addQueryItem("place_id", options["place_id"].toString());
    }
    if (options.contains("display_coordinates"))
    {
        qDebug() << "display_coordinates" << options["display_coordinates"];
        url.addQueryItem("display_coordinates", options["display_coordinates"].toBool()? "true" : "false");
    }

    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    req.setRawHeader(OAuth::AUTH_HEADER, _oauth->generateAuthorizationHeader(url, OAuth::POST));
    QNetworkReply* reply = _man->post(req, QByteArray());

    q->connect(reply, SIGNAL(finished()), q, SLOT(onUpdateFinished()));
    q->connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
        q, SLOT(onUpdateError(QNetworkReply::NetworkError)));
}

void StatusAPIPrivate::onUpdateFinished()
{
    Q_Q(StatusAPI);
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(q->sender());
    qDebug() << "onUpdateFinished with error" << reply->error();

    if (reply->error() == QNetworkReply::NoError)
    {
        // Reading the data from the response
        QByteArray bytes = reply->readAll();
        QString jsonString(bytes); // string
        qDebug() << jsonString;
    }
    else
    {
        qDebug() << "Dealing with error.";
    }
}

void StatusAPIPrivate::onUpdateError(QNetworkReply::NetworkError error)
{
    Q_Q(StatusAPI);
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(q->sender());
    // Reading the data from the response
    QByteArray bytes = reply->readAll();
    QString jsonString(bytes); // string
    qDebug() << jsonString;
}

void StatusAPIPrivate::retweet(QString uuid, uint tweet_id, QVariantMap options)
{
    QUrl url(StatusAPIPrivate::RETWEET_URL.arg(tweet_id));
    if (options.contains("trim_user"))
    {
        qDebug() << "trim_user" << options["trim_user"];
        url.addQueryItem("trim_user", options["trim_user"].toBool()? "true" : "false");
    }
    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    req.setRawHeader(OAuth::AUTH_HEADER, _oauth->generateAuthorizationHeader(url, OAuth::POST));
    QNetworkReply *reply = _man->post(req, QByteArray());

    // TODO: connecto to reply signal
}

StatusAPI::StatusAPI(OAuth* oauth, QNetworkAccessManager* man, QObject *parent) :
    QObject(parent),
    d_ptr(new StatusAPIPrivate(oauth, man, this))
{
}

StatusAPI::~StatusAPI()
{
}

void StatusAPI::retweets(QString uuid, uint tweet_id, QVariantMap options)
{
    Q_D(StatusAPI);
    d->retweets(uuid, tweet_id, options);
}

void StatusAPI::show(QString uuid, uint tweet_id, QVariantMap options)
{
    Q_D(StatusAPI);
    d->show(uuid, tweet_id, options);
}

void StatusAPI::destroy(QString uuid, uint tweet_id, QVariantMap options)
{
    Q_D(StatusAPI);
    d->destroy(uuid, tweet_id, options);
}

void StatusAPI::update(QString uuid, QString status, QVariantMap options)
{
    Q_D(StatusAPI);
    d->update(uuid, status, options);
}

void StatusAPI::retweet(QString uuid, uint tweet_id, QVariantMap options)
{
    Q_D(StatusAPI);
    d->retweet(uuid, tweet_id, options);
}

} // twitter

} // tori

#include "moc_status_api.cpp"
