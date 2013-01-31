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

#ifndef MEDIA_SIZE_H
#define MEDIA_SIZE_H
#include <QList>
#include <QString>
#include <QJsonObject>
#include <QDBusArgument>

namespace tori
{

namespace twitter
{

class MediaSizeInfo
{
	Q_PROPERTY(QString name READ getName)
	Q_PROPERTY(int height READ getHeight)
	Q_PROPERTY(int width READ getWidth)
	Q_PROPERTY(QString resize READ getResize)

public:
	MediaSizeInfo();
	MediaSizeInfo(QString name, int height, int width, QString resize);
	MediaSizeInfo(QJsonObject data);
    MediaSizeInfo(const MediaSizeInfo& other);
    MediaSizeInfo& operator=(const MediaSizeInfo& other);
    ~MediaSizeInfo();

    friend QDBusArgument &operator<<(QDBusArgument &argument, const MediaSizeInfo& media);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, MediaSizeInfo& media);

    QString getName();
    int getHeight();
    int getWidth();
    QString getResize();

private:
	QString _name;
	int _height;
	int _width;
	QString _resize;
};

class MediaSize
{
	Q_PROPERTY(QList<MediaSizeInfo> sizes READ getSizes)

public:
	MediaSize();
	MediaSize(QJsonObject data);
    MediaSize(const MediaSize& other);
    MediaSize& operator=(const MediaSize& other);
    ~MediaSize();

    friend QDBusArgument &operator<<(QDBusArgument &argument, const MediaSize& media);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, MediaSize& media);

	QList<MediaSizeInfo> getSizes() const;

private:
	QList<MediaSizeInfo> _sizes;
};

} // tori

} // twitter

Q_DECLARE_METATYPE(tori::twitter::MediaSizeInfo)
Q_DECLARE_METATYPE(tori::twitter::MediaSize)
#endif
