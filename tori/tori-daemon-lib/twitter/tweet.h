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

#include <functional>
#include <QDateTime>
#include <QList>
#include <QVariantMap>
#include <QDBusArgument>
#include <QJsonObject>
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
    User(const QJsonObject& data);
    User(const User& other);
    User& operator=(const User& other);
    ~User();

    friend QDBusArgument &operator<<(QDBusArgument &argument, const User& user);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, User& user);

    bool contributorsEnabled() const;
    QDateTime creationDate() const;
    QString description() const;
    Entity entities() const;
    int favouritesCount() const;
    bool followRequestSent() const;
    bool following() const;
    int followersCount() const;
    int friendsCount() const;
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

private:
    static QString CONTRIBUTORS_ENABLED_KEY; 
    static QString CREATION_DATE_KEY;
    static QString DESCRIPTION_KEY;
    static QString ENTITIES_KEY;
    static QString FAVOURITES_COUNT_KEY;
    static QString FOLLOW_REQUEST_SENT_KEY;
    static QString FOLLOWING_KEY;
    static QString FOLLOWERS_COUNT_KEY;
    static QString FRIENDS_COUNT_KEY;
    static QString GEO_ENABLED_KEY;
    static QString ID_KEY;
    static QString ID_STRING_KEY;
    static QString IS_TRANSLATOR_KEY;
    static QString LANGUAGE_KEY;
    static QString LISTED_COUNT_KEY;
    static QString LOCATION_KEY;
    static QString NAME_KEY;
    static QString PROTECTED_TWEETS_KEY;
    static QString SCREEN_NAME_KEY;
    static QString PROFILE_IMAGE_KEY;
    static QString LAST_TWEET_KEY;
    static QString TWEET_COUNT_KEY;
    static QString TIME_ZONE_KEY;
    static QString URL_KEY;
    static QString UTC_OFFSET_KEY;
    static QString VERIFIED_KEY;

    bool _contributorsEnabled;
    QDateTime _creationDate;
    QString _description;
    Entity _entities;
    int _favouritesCount;
    bool _followRequestSent;
    bool _following;
    int _followersCount;
    int _friendsCount;
    bool _geoEnabled;
    qlonglong _id;
    QString _idString;
    bool _isTranslator;
    QString _language;
    int _listedCount;
    QString _location;
    QString _name;
    bool _protectedTweets;
    QString _screenName;
    QString _profileImage;
    Tweet _lastTweet;
    int _tweetCount;
    QString _timeZone;
    QString _url;
    int _utcOffset;
    bool _verified;

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

Q_DECLARE_METATYPE(tori::twitter::User)
Q_DECLARE_METATYPE(tori::twitter::Tweet)

#endif // TWEET_H
