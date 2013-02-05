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

#include "user.h"

namespace tori
{

namespace twitter
{

const QString& User::CONTRIBUTORS_ENABLED_KEY = "contributors_enabled"; 
const QString& User::CREATION_DATE_KEY = "created_at";
const QString& User::DESCRIPTION_KEY = "description";
const QString& User::ENTITIES_KEY = "entities";
const QString& User::FAVOURITES_COUNT_KEY = "favourites_count";
const QString& User::FOLLOW_REQUEST_SENT_KEY = "follow_request_sent";
const QString& User::FOLLOWING_KEY = "following";
const QString& User::FOLLOWERS_COUNT_KEY = "followers_count";
const QString& User::FRIENDS_COUNT_KEY = "friends_count";
const QString& User::GEO_ENABLED_KEY = "geo_enabled";
const QString& User::ID_KEY = "id";
const QString& User::ID_STRING_KEY = "id_str";
const QString& User::IS_TRANSLATOR_KEY = "is_translator";
const QString& User::LANGUAGE_KEY = "lang";
const QString& User::LISTED_COUNT_KEY = "listed_count";
const QString& User::LOCATION_KEY = "location";
const QString& User::NAME_KEY = "name";
const QString& User::PROTECTED_TWEETS_KEY = "protected";
const QString& User::SCREEN_NAME_KEY = "screen_name";
const QString& User::PROFILE_IMAGE_KEY = "profile_image_url";
const QString& User::TWEET_COUNT_KEY = "statuses_count";
const QString& User::TIME_ZONE_KEY = "time_zone";
const QString& User::URL_KEY = "url";
const QString& User::UTC_OFFSET_KEY = "utc_offset";
const QString& User::VERIFIED_KEY = "verified";

User::User()
{
}

User::User(const QJsonObject& data)
{
	if (data.contains(User::CONTRIBUTORS_ENABLED_KEY))
	{
		_contributorsEnabled = data[User::CONTRIBUTORS_ENABLED_KEY].toBool();
	}
	if (data.contains(User::CREATION_DATE_KEY))
	{
		_creationDate = QDateTime::fromString(data[User::CREATION_DATE_KEY].toString(), "ddd MMM dd HH:mm:ss zzzz yyyy");
	}
	if (data.contains(User::DESCRIPTION_KEY))
	{
		_description = data[User::DESCRIPTION_KEY].toString();
	}
	if (data.contains(User::ENTITIES_KEY))
	{
		_entities = Entity(data[User::ENTITIES_KEY].toObject());
	}
	if (data.contains(User::FAVOURITES_COUNT_KEY))
	{
		_favouritesCount = static_cast<int>(data[User::FAVOURITES_COUNT_KEY].toDouble());
	}
	if (data.contains(User::FOLLOW_REQUEST_SENT_KEY))
	{
		_followRequestSent = data[User::FOLLOW_REQUEST_SENT_KEY].toBool();
	}
	if (data.contains(User::FOLLOWING_KEY))
	{
		_following = data[User::FOLLOWING_KEY].toBool();
	}
	if (data.contains(User::FOLLOWERS_COUNT_KEY))
	{
		_followersCount = static_cast<int>(data[User::FOLLOWERS_COUNT_KEY].toDouble());
	}
	if (data.contains(User::FRIENDS_COUNT_KEY))
	{
		_friendsCount = static_cast<int>(data[User::FRIENDS_COUNT_KEY].toDouble()); 
	}
	if (data.contains(User::GEO_ENABLED_KEY))
	{
		_geoEnabled = data[User::GEO_ENABLED_KEY].toBool();
	}
	
	if (data.contains(User::ID_STRING_KEY))
	{
		_idString = data[User::ID_STRING_KEY].toString();
		_id = _idString.toLongLong();	
	}
	if (data.contains(User::IS_TRANSLATOR_KEY))
	{
		_isTranslator = data[User::IS_TRANSLATOR_KEY].toBool();
	}
	if (data.contains(User::LANGUAGE_KEY))
	{
		_language = data[User::LANGUAGE_KEY].toString();
	}
	if (data.contains(User::LISTED_COUNT_KEY))
	{
		_listedCount = static_cast<int>(data[User::LISTED_COUNT_KEY].toDouble());	
	}
	if (data.contains(User::LOCATION_KEY))
	{
		_location = data[User::LOCATION_KEY].toString();
	}
	if (data.contains(User::NAME_KEY))
	{
		_name = data[User::NAME_KEY].toString();
	}
	if (data.contains(User::PROTECTED_TWEETS_KEY))
	{
		_protectedTweets = data[User::PROTECTED_TWEETS_KEY].toBool();
	}
	if (data.contains(User::SCREEN_NAME_KEY))
	{
		_screenName = data[User::SCREEN_NAME_KEY].toString();
	}
	if (data.contains(User::PROFILE_IMAGE_KEY))
	{
		_profileImage = data[User::PROFILE_IMAGE_KEY].toString();
	}
	if (data.contains(User::TWEET_COUNT_KEY))
	{
		_tweetCount = static_cast<int>(data[User::TWEET_COUNT_KEY].toDouble());
	}
	if (data.contains(User::TIME_ZONE_KEY))
	{
		_timeZone = data[User::TIME_ZONE_KEY].toString();
	}
	if (data.contains(User::URL_KEY))
	{
		_url = data[User::URL_KEY].toString();
	}
	if (data.contains(User::UTC_OFFSET_KEY))
	{
		_utcOffset = static_cast<int>(data[User::UTC_OFFSET_KEY].toDouble());
	}
	if (data.contains(User::VERIFIED_KEY))
	{
		_verified = data[User::VERIFIED_KEY].toBool();
	}

}

User::User(const User& other) :
	_contributorsEnabled(other._contributorsEnabled),
    _creationDate(other._creationDate),
    _description(other._description),
    _entities(other._entities),
    _favouritesCount(other._favouritesCount),
    _followRequestSent(other._followRequestSent),
    _following(other._following),
    _followersCount(other._followersCount),
    _friendsCount(other._friendsCount),
    _geoEnabled(other._geoEnabled),
    _id(other._id),
    _idString(other._idString),
    _isTranslator(other._isTranslator),
    _language(other._language),
    _listedCount(other._listedCount),
    _location(other._location),
    _name(other._name),
    _protectedTweets(other._protectedTweets),
    _screenName(other._screenName),
    _profileImage(other._profileImage),
    _tweetCount(other._tweetCount),
    _timeZone(other._timeZone),
    _url(other._url),
    _utcOffset(other._utcOffset),
    _verified(other._verified)
{

}

User& User::operator=(const User& other)
{
	_contributorsEnabled = other._contributorsEnabled;
    _creationDate = other._creationDate;
    _description = other._description;
    _entities = other._entities;
    _favouritesCount = other._favouritesCount;
    _followRequestSent = other._followRequestSent;
    _following = other._following;
    _followersCount = other._followersCount;
    _friendsCount = other._friendsCount;
    _geoEnabled = other._geoEnabled;
    _id = other._id;
    _idString = other._idString;
    _isTranslator = other._isTranslator;
    _language = other._language;
    _listedCount = other._listedCount;
    _location = other._location;
    _name = other._name;
    _protectedTweets = other._protectedTweets;
    _screenName = other._screenName;
    _profileImage = other._profileImage;
    _tweetCount = other._tweetCount;
    _timeZone = other._timeZone;
    _url = other._url;
    _utcOffset = other._utcOffset;
    _verified = other._verified;

	return *this;
}

User::~User()
{

}

QDBusArgument &operator<<(QDBusArgument &argument, const User& user)
{
	argument.beginStructure();
	argument << user._contributorsEnabled;
    argument << user._creationDate;
    argument << user._description;
    argument << user._entities;
    argument << user._favouritesCount;
    argument << user._followRequestSent;
    argument << user._following;
    argument << user._followersCount;
    argument << user._friendsCount;
    argument << user._geoEnabled;
    argument << user._id;
    argument << user._idString;
    argument << user._isTranslator;
    argument << user._language;
    argument << user._listedCount;
    argument << user._location;
    argument << user._name;
    argument << user._protectedTweets;
    argument << user._screenName;
    argument << user._profileImage;
    argument << user._tweetCount;
    argument << user._timeZone;
    argument << user._url;
    argument << user._utcOffset;
    argument << user._verified;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, User& user)
{
	argument.beginStructure();
	argument >> user._contributorsEnabled;
    argument >> user._creationDate;
    argument >> user._description;
    argument >> user._entities;
    argument >> user._favouritesCount;
    argument >> user._followRequestSent;
    argument >> user._following;
    argument >> user._followersCount;
    argument >> user._friendsCount;
    argument >> user._geoEnabled;
    argument >> user._id;
    argument >> user._idString;
    argument >> user._isTranslator;
    argument >> user._language;
    argument >> user._listedCount;
    argument >> user._location;
    argument >> user._name;
    argument >> user._protectedTweets;
    argument >> user._screenName;
    argument >> user._profileImage;
    argument >> user._tweetCount;
    argument >> user._timeZone;
    argument >> user._url;
    argument >> user._utcOffset;
    argument >> user._verified;
    argument.endStructure();

    return argument;
}

bool User::getContributorsEnabled() const
{
	return _contributorsEnabled;
}

QDateTime User::getCreationDate() const
{
	return _creationDate;
}

QString User::getDescription() const
{
	return _description;
}

Entity User::getEntities() const
{
	return _entities;
}

int User::getFavouritesCount() const
{
	return _favouritesCount;
}

bool User::getFollowRequestSent() const
{
	return _followRequestSent;
}

bool User::getFollowing() const
{
	return _following;
}

int User::getFollowersCount() const
{
	return _followersCount;
}

int User::getFriendsCount() const
{
	return _friendsCount;
}

bool User::getGeoEnabled() const
{
	return _geoEnabled;
}

qlonglong User::getId() const
{
	return _id;
}

QString User::getIdString() const
{
	return _idString;
}

bool User::getIsTranslator() const
{
	return _isTranslator;
}

QString User::getLanguage() const
{
	return _language;
}

int User::getListedCount() const
{
	return _listedCount;
}

QString User::getLocation() const
{
	return _location;
}

QString User::getName() const
{
	return _name;
}

bool User::getProtectedTweets() const
{
	return _protectedTweets;
}

QString User::getScreenName() const
{
	return _screenName;
}

QString User::getProfileImage() const
{
	return _profileImage;
}

int User::getTweetCount() const
{
	return _tweetCount;
}

QString User::getTimeZone() const
{
	return _timeZone;
}

QString User::getUrl() const
{
	return _url;
}

int User::getUtcOffset() const
{
	return _utcOffset;
}

bool User::getVerified() const
{
	return _verified;
}

} // twitter

} // tori