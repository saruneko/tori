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

#include <QJsonArray>
#include "entity.h"

namespace tori
{

namespace twitter
{

QString Entity::HASHTAGS_KEY = "hashtags";
QString Entity::HASHTAG_TEXT_KEY = "text";
QString Entity::MEDIA_KEY = "media";
QString Entity::URLS_KEY = "urls";
QString Entity::MENTIONS_KEY = "user_mentions";

Entity::Entity(QList<QString> hashtags, Media media, QList<CollapsedUrl> urls, QList<Mention> mentions) :
	_hashtags(hashtags),
	_media(media),
	_urls(urls),
	_mentions(mentions)
{

}

Entity::Entity(QJsonObject data)
{
	if (data.contains(Entity::HASHTAGS_KEY))
	{
		// get the json object and just retrieve the actuan tag
		QJsonArray hashtags = data[Entity::HASHTAGS_KEY].toArray();
		for (int i = 0; i < hashtags.count(); ++i)
		{
			QString tag = hashtags[i].toString();
			_hashtags.append(tag);
		}
	}
	if (data.contains(Entity::MEDIA_KEY))
	{
		_media = Media(data[Entity::MEDIA_KEY].toObject());
	}
	if (data.contains(Entity::URLS_KEY))
	{
		QJsonArray urls = data[Entity::URLS_KEY].toArray();
		for (int i = 0; i < urls.count(); ++i)
		{
			_urls.append(CollapsedUrl(urls[i].toObject()));
		}
	}
	if (data.contains(Entity::MENTIONS_KEY))
	{
		QJsonArray mentions = data[Entity::MENTIONS_KEY].toArray();
		for (int i = 0; i < mentions.count(); ++i)
		{
			_mentions.append(Mention(mentions[i].toObject()));
		}
	}
}

Entity::Entity(const Entity& other) :
	_hashtags(other._hashtags),
	_media(other._media),
	_urls(other._urls),
	_mentions(other._mentions)
{
}

Entity& Entity::operator=(const Entity& other)
{
	_hashtags = other._hashtags;
	_media = other._media;
	_urls = other._urls;
	_mentions = _mentions;

	return *this;
}

Entity::~Entity()
{
}

QDBusArgument &operator<<(QDBusArgument &argument, const Entity& entity)
{
    argument.beginStructure();
    argument << entity._hashtags;
    argument << entity._media;
    argument << entity._urls;
    argument << entity._mentions;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, Entity& entity)
{
    argument.beginStructure();
    argument >> entity._hashtags;
    argument >> entity._media;
    argument >> entity._urls;
    argument >> entity._mentions;
    argument.endStructure();

    return argument;
}

QList<QString> Entity::getHashtags()
{
	return _hashtags;
}

Media Entity::getMedia()
{
	return _media;
}

QList<CollapsedUrl> Entity::getUrls()
{
	return _urls;
}

QList<Mention> Entity::getMentions()
{
	return _mentions;
}

} // twitter

} // tori