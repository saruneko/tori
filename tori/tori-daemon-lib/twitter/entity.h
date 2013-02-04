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

#ifndef ENTITY_H
#define ENTITY_H
#include <QString>
#include <QList>
#include <QDBusArgument>
#include <QJsonObject>
#include "collapsed_url.h"
#include "media.h"
#include "mention.h"
#include "collapsed_url.h"

namespace tori
{

namespace twitter
{

class Entity
{
	Q_PROPERTY(QList<QString> hashtags READ getHashtags)
	Q_PROPERTY(Media media READ getMedia)
	Q_PROPERTY(QList<CollapsedUrl> urls READ getUrls)
	Q_PROPERTY(QList<Mention> mentions READ getMentions)

public:
	Entity();
	Entity(QList<QString> hashtags, Media media, QList<CollapsedUrl> urls, QList<Mention> mentions);
	Entity(QJsonObject data);
    Entity(const Entity& other);
    Entity& operator=(const Entity& other);
    ~Entity();

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Entity& entity);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Entity& entity);

	QList<QString> getHashtags() const;
	Media getMedia() const;
	QList<CollapsedUrl> getUrls() const;
	QList<Mention> getMentions() const;

private:
	static const QString& HASHTAGS_KEY;
	static const QString& HASHTAG_TEXT_KEY;
	static const QString& MEDIA_KEY;
	static const QString& URLS_KEY;
	static const QString& MENTIONS_KEY;

	QList<QString> _hashtags;
	Media _media;
	QList<CollapsedUrl> _urls;
	QList<Mention> _mentions;
};

} // twitter

} // tori

Q_DECLARE_METATYPE(tori::twitter::Entity)
#endif