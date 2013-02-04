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

#ifndef MEDIA_H
#define MEDIA_H
#include <QString>
#include <QDBusArgument>
#include <QJsonObject>
#include "media_size.h"

namespace tori
{

namespace twitter
{

class Media
{
	Q_PROPERTY(QString displayUrl READ getDisplayUrl)
	Q_PROPERTY(QString expandedUrl READ getExpandedUrl)
	Q_PROPERTY(qlonglong id READ getId)
	Q_PROPERTY(QString idString READ getIdString)
	Q_PROPERTY(QString mediaUrl READ getMediaUrl)
	Q_PROPERTY(QString mediaHttpsUrl READ getMediaHttpsUrl)
	Q_PROPERTY(MediaSize sizes READ getSizes)
	Q_PROPERTY(qlonglong sourceStatusId READ getSourceStatusId)
	Q_PROPERTY(QString sourceStatusIdString READ getSourceStatusIdString)
	Q_PROPERTY(QString type READ getType)
	Q_PROPERTY(QString url READ getUrl)

public:
	Media();
	Media(QJsonObject data);
    Media(const Media& other);
    Media& operator=(const Media& other);
    ~Media();

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Media& media);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Media& media);

	QString getDisplayUrl() const;
	QString getExpandedUrl() const;
	qlonglong getId() const;
	QString getIdString() const;
	QString getMediaUrl() const;
	QString getMediaHttpsUrl() const;
	MediaSize getSizes() const;
	qlonglong getSourceStatusId() const;
	QString getSourceStatusIdString() const;
	QString getType() const;
	QString getUrl() const;

private:
    static const QString& DISPLAY_URL_KEY;
    static const QString& EXPANDED_URL_KEY;
    static const QString& ID_KEY;
    static const QString& ID_STRING_KEY;
    static const QString& MEDIA_URL_KEY;
    static const QString& MEDIA_HTTS_URL_KEY;
    static const QString& SIZE_KEY;
    static const QString& SOURCES_STATUS_ID_KEY;
    static const QString& SOURCES_STATUS_ID_STRING_KEY;
    static const QString& TYPE_KEY;
    static const QString& URL_KEY;

	QString _displayUrl;
	QString _expandedUrl;
	qlonglong _id;
	QString _idString;
	QString _mediaUrl;
	QString _mediaHttpsUrl;
	MediaSize _size;
	qlonglong _sourceStatusId;
	QString _sourceStatusIdString;
	QString _type;
	QString _url;
};

} // twitter

} // tori

Q_DECLARE_METATYPE(tori::twitter::Media)
#endif
