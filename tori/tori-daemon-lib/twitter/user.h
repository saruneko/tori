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

#ifndef USER_H
#define USER_H
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
    Q_PROPERTY(bool contributorsEnabled READ getContributorsEnabled)
    Q_PROPERTY(QDateTime creationDate READ getCreationDate)
    Q_PROPERTY(QString description READ getDescription)
    Q_PROPERTY(Entity entities READ getEntities)
    Q_PROPERTY(int favouritesCount READ getFavouritesCount)
    Q_PROPERTY(bool followRequestSent READ getFollowRequestSent)
    Q_PROPERTY(bool following READ getFollowing)
    Q_PROPERTY(int followersCount READ getFollowersCount)
    Q_PROPERTY(int friendsCount READ getFriendsCount)
    Q_PROPERTY(bool geoEnabled READ getGeoEnabled)
    Q_PROPERTY(qlonglong id READ getId)
    Q_PROPERTY(QString idString READ getIdString)
    Q_PROPERTY(bool isTranslator READ getIsTranslator)
    Q_PROPERTY(QString language READ getLanguage)
    Q_PROPERTY(int listedCount READ getListedCount)
    Q_PROPERTY(QString location READ getLocation)
    Q_PROPERTY(QString name READ getName)
    Q_PROPERTY(bool protectedTweets READ getProtectedTweets)
    Q_PROPERTY(QString screenName READ getScreenName)
    Q_PROPERTY(QString profileImage READ getProfileImage)
    Q_PROPERTY(int tweetCount READ getTweetCount)
    Q_PROPERTY(QString timeZone READ getTimeZone)
    Q_PROPERTY(QString url READ getUrl)
    Q_PROPERTY(int utcOffset READ getUtcOffset)
    Q_PROPERTY(bool verified READ getVerified)

public:
    User();
    User(const QJsonObject& data);
    User(const User& other);
    User& operator=(const User& other);
    ~User();

    friend QDBusArgument &operator<<(QDBusArgument &argument, const User& user);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, User& user);

    bool getContributorsEnabled() const;
    QDateTime getCreationDate() const;
    QString getDescription() const;
    Entity getEntities() const;
    int getFavouritesCount() const;
    bool getFollowRequestSent() const;
    bool getFollowing() const;
    int getFollowersCount() const;
    int getFriendsCount() const;
    bool getGeoEnabled() const;
    qlonglong getId() const;
    QString getIdString() const;
    bool getIsTranslator() const;
    QString getLanguage() const;
    int getListedCount() const;
    QString getLocation() const;
    QString getName() const;
    bool getProtectedTweets() const;
    QString getScreenName() const;
    QString getProfileImage() const;
    int getTweetCount() const;
    QString getTimeZone() const;
    QString getUrl() const;
    int getUtcOffset() const;
    bool getVerified() const;

private:
    static const QString& CONTRIBUTORS_ENABLED_KEY; 
    static const QString& CREATION_DATE_KEY;
    static const QString& DESCRIPTION_KEY;
    static const QString& ENTITIES_KEY;
    static const QString& FAVOURITES_COUNT_KEY;
    static const QString& FOLLOW_REQUEST_SENT_KEY;
    static const QString& FOLLOWING_KEY;
    static const QString& FOLLOWERS_COUNT_KEY;
    static const QString& FRIENDS_COUNT_KEY;
    static const QString& GEO_ENABLED_KEY;
    static const QString& ID_KEY;
    static const QString& ID_STRING_KEY;
    static const QString& IS_TRANSLATOR_KEY;
    static const QString& LANGUAGE_KEY;
    static const QString& LISTED_COUNT_KEY;
    static const QString& LOCATION_KEY;
    static const QString& NAME_KEY;
    static const QString& PROTECTED_TWEETS_KEY;
    static const QString& SCREEN_NAME_KEY;
    static const QString& PROFILE_IMAGE_KEY;
    static const QString& LAST_TWEET_KEY;
    static const QString& TWEET_COUNT_KEY;
    static const QString& TIME_ZONE_KEY;
    static const QString& URL_KEY;
    static const QString& UTC_OFFSET_KEY;
    static const QString& VERIFIED_KEY;

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
    int _tweetCount;
    QString _timeZone;
    QString _url;
    int _utcOffset;
    bool _verified;

};


} // twitter

} // tori

Q_DECLARE_METATYPE(tori::twitter::User)

#endif