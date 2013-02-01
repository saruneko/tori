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
#ifndef COLLAPSED_URL_H
#define COLLAPSED_URL_H
#include <QString>
#include <QDBusArgument>
#include <QJsonObject>

namespace tori
{

namespace twitter
{

class CollapsedUrl
{
	Q_PROPERTY(QString displayUrl READ getDisplayUrl)
	Q_PROPERTY(QString expandedUrl READ getExpandedUrl)
	Q_PROPERTY(QString url READ getUrl)

public:
	CollapsedUrl();
	CollapsedUrl(const QJsonObject& data);
	CollapsedUrl(QString displayUrl, QString expandedUrl, QString url);
	CollapsedUrl(const CollapsedUrl& other);
	CollapsedUrl& operator=(const CollapsedUrl& other);

    friend QDBusArgument &operator<<(QDBusArgument &argument, const CollapsedUrl& url);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, CollapsedUrl& url);

    QString getDisplayUrl() const;
    QString getExpandedUrl() const;
    QString getUrl() const; 

private:
	static QString DISPLAY_URL_KEY;
	static QString EXPANDED_URL_KEY;
	static QString URL_KEY;

	QString _displayUrl;
	QString _expandedUrl;
	QString _url;
};

} // twitter

} // tori

Q_DECLARE_METATYPE(tori::twitter::CollapsedUrl)
#endif