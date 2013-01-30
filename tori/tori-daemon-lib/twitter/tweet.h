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

#ifndef TWEET_H
#define TWEET_H

#include <QDateTime>
#include <QList>
#include <QVariantMap>
#include <QDBusArgument>
#include "entity.h"
#include "contributor.h"
#include "coordinates.h"
#include "place.h"

namespace tori
{

namespace twitter
{

class User
{
public:
    User();
    User(const User& other);
    User& operator=(const User& other);
    ~User();

    friend QDBusArgument &operator<<(QDBusArgument &argument, const User& user);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, User& user);

    bool contributorsEnabled() const;
    QDateTime creationData() const;
    QString description() const;
    Entity Entity() const;
    int favouritesCount() const;
    bool followRequestSent() const;
    bool following() const;
    int followersCount() const;
    bool geoEnabled() const;
    qlonglong id() const;
    QString idString() const;
    bool isTranslator() const;
    QString language() const;
    int listedCount() const;
    QString location() const;
    QString name() const;
    bool protectedTweets() const;
    QString screenName() const;
    QString profileImage() const;
    Tweet lastTweet() const;
    int tweetCount() const;
    QString timeZone() const;
    QString url() const;
    int utcOffset() const;
    bool verified() const;
};

class Tweet
{
public:
    Tweet(QJsonObject data);
    Tweet(const Tweet& other);
    Tweet& operator=(const Tweet& other);
    ~Tweet();

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Tweet& tweet);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Tweet& tweet);

    QList<Contributor> contributors() const;
    Coordinates coordinates() const;
    QDateTime creationDate() const;
    qlonglong retweet() const;
    Entity Entity() const;
    bool favourited() const;
    qlonglong id() const;
    QString inReplyToScreenName() const;
    qlonglong inReplyToTweet() const;
    qlonglong inReplyToUserId() const;
    Place place() const;
    bool possiblySensitive() const;
    QVariantMap scopes() const;
    int retweetCount() const;
    bool retweeted() const;
    QString source() const;
    QString text() const;
    bool truncated() const;
    User user() const;

private:
    QList<Contributor> _contributors;
    Coordinates _coordinates;
    QDateTime _creationDate;
    qlonglong _retweet;
    Entity _Entity;
    bool _favourited;
    qlonglong _id;
    QString _inReplyToScreeName;
    qlonglong inReplyToTweet;
    qlonglong inReplyToUserId;
    Place _place;
    bool _possiblySensitive;
    QVariantMap _scopes;
    int _retweetCount;
    bool _retweeted;
    QString _source;
    QString _text;
    bool _truncated;
    User _user;
};

} // tweeter

} // tori

Q_DECLARE_METATYPE(tori::twitter::Tweet)

#endif // TWEET_H
