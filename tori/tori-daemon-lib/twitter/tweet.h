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
#include <QJsonObject>
#include "entity.h"
#include "contributor.h"
#include "coordinates.h"
#include "place.h"
#include "user.h"

namespace tori
{

namespace twitter
{

class Tweet
{
    Q_PROPERTY(QList<Contributor> contributors READ getContributors)
    Q_PROPERTY(Coordinates coordinates READ getCoordinates)
    Q_PROPERTY(QDateTime creationDate READ getCreationDate)
    Q_PROPERTY(qlonglong retweet READ getRetweet)
    Q_PROPERTY(Entity entities READ getEntities)
    Q_PROPERTY(bool favourited READ getFavourited)
    Q_PROPERTY(qlonglong id READ getId)
    Q_PROPERTY(QString inReplyToScreenName READ getInReplyToScreenName)
    Q_PROPERTY(qlonglong inReplyToTweet READ getInReplyToTweet)
    Q_PROPERTY(qlonglong inReplyToUserId READ getInReplyToUserId)
    Q_PROPERTY(Place place READ getPlace)
    Q_PROPERTY(bool possiblySensitive READ getPossiblySensitive)
    Q_PROPERTY(QVariantMap scopes READ getScopes)
    Q_PROPERTY(int retweetCount READ getRetweetCount)
    Q_PROPERTY(bool retweeted READ getRetweeted)
    Q_PROPERTY(QString source READ getSource)
    Q_PROPERTY(QString text READ getText)
    Q_PROPERTY(bool truncated READ getTruncated)
    Q_PROPERTY(User user READ getUser)

public:
    Tweet();
    Tweet(QJsonObject data);
    Tweet(const Tweet& other);
    Tweet& operator=(const Tweet& other);
    ~Tweet();

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Tweet& tweet);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Tweet& tweet);

    QList<Contributor> getContributors() const;
    Coordinates getCoordinates() const;
    QDateTime getCreationDate() const;
    qlonglong getRetweet() const;
    Entity getEntities() const;
    bool getFavourited() const;
    qlonglong getId() const;
    QString getInReplyToScreenName() const;
    qlonglong getInReplyToTweet() const;
    qlonglong getInReplyToUserId() const;
    Place getPlace() const;
    bool getPossiblySensitive() const;
    QVariantMap getScopes() const;
    int getRetweetCount() const;
    bool getRetweeted() const;
    QString getSource() const;
    QString getText() const;
    bool getTruncated() const;
    User getUser() const;

private:
    static const QString& CONTRIBUTORS_KEY;
    static const QString& COORDINATES_KEY;
    static const QString& CREATION_DATE_KEY;
    static const QString& RETWEET_KEY;
    static const QString& ENTITIES_KEY;
    static const QString& FAVOURITED_KEY;
    static const QString& ID_STRING_KEY;
    static const QString& IN_REPLY_TO_SCREEN_NAME_KEY;
    static const QString& IN_REPLY_TO_TWEET_KEY;
    static const QString& IN_REPLY_TO_USER_ID_KEY;
    static const QString& PLACE_KEY;
    static const QString& POSSIBLY_SENSITIVE_KEY;
    static const QString& SCOPES_KEY;
    static const QString& RETWEET_COUNT_KEY;
    static const QString& RETWEETED_KEY;
    static const QString& SOURCE_KEY;
    static const QString& TEXT_KEY;
    static const QString& TRUNCATED_KEY;
    static const QString& USER_KEY;

    QList<Contributor> _contributors;
    Coordinates _coordinates;
    QDateTime _creationDate;
    qlonglong _retweet;
    Entity _entities;
    bool _favourited;
    qlonglong _id;
    QString _inReplyToScreeName;
    qlonglong _inReplyToTweet;
    qlonglong _inReplyToUserId;
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
