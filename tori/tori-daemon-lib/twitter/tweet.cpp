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

#include "tweet.h"

namespace tori
{

namespace twitter
{

const QString& Tweet::CONTRIBUTORS_KEY = "contributors";
const QString& Tweet::COORDINATES_KEY = "coordinates";
const QString& Tweet::CREATION_DATE_KEY = "created_at";
const QString& Tweet::RETWEET_KEY = "current_user_retweet";
const QString& Tweet::ENTITIES_KEY = "entities";
const QString& Tweet::FAVOURITED_KEY = "favorited";
const QString& Tweet::ID_STRING_KEY = "id_str";
const QString& Tweet::IN_REPLY_TO_SCREEN_NAME_KEY = "in_reply_to_screen_name";
const QString& Tweet::IN_REPLY_TO_TWEET_KEY = "in_reply_to_status_id_str";
const QString& Tweet::IN_REPLY_TO_USER_ID_KEY = "in_reply_to_user_id_str";
const QString& Tweet::PLACE_KEY = "place";
const QString& Tweet::POSSIBLY_SENSITIVE_KEY = "possibly_sensitive";
const QString& Tweet::SCOPES_KEY = "scopes";
const QString& Tweet::RETWEET_COUNT_KEY = "retweet_count";
const QString& Tweet::RETWEETED_KEY = "retweeted";
const QString& Tweet::SOURCE_KEY = "source";
const QString& Tweet::TEXT_KEY = "text";
const QString& Tweet::TRUNCATED_KEY = "truncated";
const QString& Tweet::USER_KEY = "user";

Tweet::Tweet()
{
}

Tweet::Tweet(QJsonObject data)
{
	if (data.contains(Tweet::CONTRIBUTORS_KEY) && !data[Tweet::CONTRIBUTORS_KEY].isNull())
	{
		QJsonArray contributorsJson = data[Tweet::CONTRIBUTORS_KEY].toArray();
		for (int i = 0; i < contributorsJson.count(); ++i)
		{
			_contributors.append(Contributor(contributorsJson[i].toObject()));
		}
	}
	if (data.contains(Tweet::COORDINATES_KEY) && !data[Tweet::COORDINATES_KEY].isNull())
	{
		_coordinates = Coordinates(data[Tweet::COORDINATES_KEY].toObject());
	}
	if (data.contains(Tweet::CREATION_DATE_KEY))
	{
		_creationDate = QDateTime::fromString(data[Tweet::CREATION_DATE_KEY].toString(), "ddd MMM dd HH:mm:ss zzzz yyyy");
	}
	if (data.contains(Tweet::RETWEET_KEY))
	{
		QJsonObject retweetData = data[Tweet::RETWEET_KEY].toObject();
		_retweet = retweetData[Tweet::ID_STRING_KEY].toString().toLongLong();
	}
	if (data.contains(Tweet::ENTITIES_KEY))
	{
		_entities = Entity(data[Tweet::ENTITIES_KEY].toObject());
	}
	if (data.contains(Tweet::FAVOURITED_KEY))
	{
		_favourited = data[Tweet::FAVOURITED_KEY].toBool();
	}
	if (data.contains(Tweet::ID_STRING_KEY))
	{
		_id = data[Tweet::ID_STRING_KEY].toString().toLongLong();
	}
	if (data.contains(Tweet::IN_REPLY_TO_SCREEN_NAME_KEY) && !data[Tweet::IN_REPLY_TO_SCREEN_NAME_KEY].isNull())
	{
		_inReplyToScreeName = data[Tweet::IN_REPLY_TO_SCREEN_NAME_KEY].toString();
	}
	if (data.contains(Tweet::IN_REPLY_TO_TWEET_KEY) && !data[Tweet::IN_REPLY_TO_TWEET_KEY].isNull())
	{
		_inReplyToTweet = data[Tweet::IN_REPLY_TO_TWEET_KEY].toString().toLongLong();
	}
	if (data.contains(Tweet::IN_REPLY_TO_USER_ID_KEY) && !data[Tweet::IN_REPLY_TO_USER_ID_KEY].isNull())
	{
		_inReplyToUserId = data[Tweet::IN_REPLY_TO_USER_ID_KEY].toString().toLongLong();
	}
	if (data.contains(Tweet::PLACE_KEY) && !data[Tweet::PLACE_KEY].isNull())
	{
		_place = Place(data[Tweet::PLACE_KEY].toObject());
	}
	if (data.contains(Tweet::POSSIBLY_SENSITIVE_KEY) && !data[Tweet::POSSIBLY_SENSITIVE_KEY].isNull())
	{
		_possiblySensitive = data[Tweet::POSSIBLY_SENSITIVE_KEY].toBool();
	}
	if (data.contains(Tweet::SCOPES_KEY))
	{
		QJsonObject scopesData = data[Tweet::SCOPES_KEY].toObject();
		foreach (QString key, scopesData.keys())
		{
			_scopes[key] = scopesData.value(key);
		}
	}
	if (data.contains(Tweet::RETWEET_COUNT_KEY))
	{
		_retweetCount = static_cast<int>(data[Tweet::RETWEET_COUNT_KEY].toDouble());
	}
	if (data.contains(Tweet::RETWEETED_KEY))
	{
		_retweeted = data[Tweet::RETWEETED_KEY].toBool();
	}
	if (data.contains(Tweet::SOURCE_KEY))
	{
		_source = data[Tweet::SOURCE_KEY].toString();
	}
	if (data.contains(Tweet::TEXT_KEY))
	{
		_text = data[Tweet::TEXT_KEY].toString();
	}
	if (data.contains(Tweet::TRUNCATED_KEY))
	{
		_truncated = data[Tweet::TRUNCATED_KEY].toBool();
	}
	if (data.contains(Tweet::USER_KEY))
	{
		_user = User(data[Tweet::USER_KEY].toObject());
	}

}

Tweet::Tweet(const Tweet& other) :
	_contributors(other._contributors),
	_coordinates(other._coordinates),
	_creationDate(other._creationDate),
	_retweet(other._retweet),
	_entities(other._entities),
	_favourited(other._favourited),
	_id(other._id),
	_inReplyToScreeName(other._inReplyToScreeName),
	_inReplyToTweet(other._inReplyToTweet),
	_inReplyToUserId(other._inReplyToUserId),
	_place(other._place),
	_possiblySensitive(other._possiblySensitive),
	_scopes(other._scopes),
	_retweetCount(other._retweetCount),
	_retweeted(other._retweeted),
	_source(other._source),
	_text(other._text),
	_truncated(other._truncated),
	_user(other._user)
{
}

Tweet& Tweet::operator=(const Tweet& other)
{
	_contributors = other._contributors;
	_coordinates = other._coordinates;
	_creationDate = other._creationDate;
	_retweet = other._retweet;
	_entities = other._entities;
	_favourited = other._favourited;
	_id = other._id;
	_inReplyToScreeName = other._inReplyToScreeName;
	_inReplyToTweet = other._inReplyToTweet;
	_inReplyToUserId = other._inReplyToUserId;
	_place = other._place;
	_possiblySensitive = other._possiblySensitive;
	_scopes = other._scopes;
	_retweetCount = other._retweetCount;
	_retweeted = other._retweeted;
	_source = other._source;
	_text = other._text;
	_truncated = other._truncated;
	_user = other._user;

	return *this;
}

Tweet::~Tweet()
{
}

QDBusArgument &operator<<(QDBusArgument &argument, const Tweet& tweet)
{
	argument.beginStructure();
	argument << tweet._contributors;
	argument << tweet._creationDate;
	argument << tweet._retweet;
	argument << tweet._entities;
	argument << tweet._favourited;
	argument << tweet._id;
	argument << tweet._inReplyToScreeName;
	argument << tweet._inReplyToTweet;
	argument << tweet._inReplyToUserId;
	argument << tweet._place;
	argument << tweet._possiblySensitive;
	argument << tweet._scopes;
	argument << tweet._retweetCount;
	argument << tweet._retweeted;
	argument << tweet._source;
	argument << tweet._text;
	argument << tweet._truncated;
	argument << tweet._user;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, Tweet& tweet)
{
	argument.beginStructure();
	argument >> tweet._contributors;
	argument >> tweet._creationDate;
	argument >> tweet._retweet;
	argument >> tweet._entities;
	argument >> tweet._favourited;
	argument >> tweet._id;
	argument >> tweet._inReplyToScreeName;
	argument >> tweet._inReplyToTweet;
	argument >> tweet._inReplyToUserId;
	argument >> tweet._place;
	argument >> tweet._possiblySensitive;
	argument >> tweet._scopes;
	argument >> tweet._retweetCount;
	argument >> tweet._retweeted;
	argument >> tweet._source;
	argument >> tweet._text;
	argument >> tweet._truncated;
	argument >> tweet._user;
    argument.endStructure();

    return argument;
}

QList<Contributor> Tweet::getContributors() const
{
	return _contributors;
}

Coordinates Tweet::getCoordinates() const
{
	return _coordinates;
}

QDateTime Tweet::getCreationDate() const
{
	return _creationDate;
}

qlonglong Tweet::getRetweet() const
{
	return _retweet;
}

Entity Tweet::getEntities() const
{
	return _entities;
}

bool Tweet::getFavourited() const
{
	return _favourited;
}

qlonglong Tweet::getId() const
{
	return _id;
}

QString Tweet::getInReplyToScreenName() const
{
	return _inReplyToScreeName;
}

qlonglong Tweet::getInReplyToTweet() const
{
	return _inReplyToTweet;
}

qlonglong Tweet::getInReplyToUserId() const
{
	return _inReplyToUserId;
}

Place Tweet::getPlace() const
{
	return _place;
}

bool Tweet::getPossiblySensitive() const
{
	return _possiblySensitive;
}

QVariantMap Tweet::getScopes() const
{
	return _scopes;
}

int Tweet::getRetweetCount() const
{
	return _retweetCount;
}

bool Tweet::getRetweeted() const
{
	return _retweeted;
}

QString Tweet::getSource() const
{
	return _source;
}

QString Tweet::getText() const
{
	return _text;
}

bool Tweet::getTruncated() const
{
	return _truncated;
}

User Tweet::getUser() const
{
	return _user;
}


} // twitter

} // tori
