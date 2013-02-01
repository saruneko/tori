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
#include "collapsed_url.h"

namespace tori
{

namespace twitter
{

QString CollapsedUrl::DISPLAY_URL_KEY = "display_url";
QString CollapsedUrl::EXPANDED_URL_KEY = "expanded_url";
QString CollapsedUrl::URL_KEY = "url";

CollapsedUrl::CollapsedUrl()
{
}

CollapsedUrl::CollapsedUrl(const QJsonObject& data)
{
	if (data.contains(CollapsedUrl::DISPLAY_URL_KEY))
	{
		_displayUrl = data[CollapsedUrl::DISPLAY_URL_KEY].toString();
	}
	if (data.contains(CollapsedUrl::EXPANDED_URL_KEY))
	{
		_expandedUrl = data[CollapsedUrl::EXPANDED_URL_KEY].toString();	
	}
	if (data.contains(CollapsedUrl::URL_KEY))
	{
		_url = data[CollapsedUrl::URL_KEY].toString(); 
	}
}

CollapsedUrl::CollapsedUrl(QString displayUrl, QString expandedUrl, QString url) :
	_displayUrl(displayUrl),
	_expandedUrl(expandedUrl),
	_url(url)
{
}

CollapsedUrl::CollapsedUrl(const CollapsedUrl& other) :
	_displayUrl(other._displayUrl),
	_expandedUrl(other._expandedUrl),
	_url(other._url)
{
}

CollapsedUrl& CollapsedUrl::operator=(const CollapsedUrl& other)
{
	_displayUrl = other._displayUrl;
	_expandedUrl = other._expandedUrl;
	_url = other._url;
	return *this;
}

QDBusArgument &operator<<(QDBusArgument &argument, const CollapsedUrl& url)
{
    argument.beginStructure();
    argument << url._displayUrl;
    argument << url._expandedUrl;
    argument << url._url;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, CollapsedUrl& url)
{
    argument.beginStructure();
    argument >> url._displayUrl;
    argument >> url._expandedUrl;
    argument >> url._url;
    argument.endStructure();

    return argument;
}

QString CollapsedUrl::getDisplayUrl() const
{
	return _displayUrl;
}

QString CollapsedUrl::getExpandedUrl() const
{
	return _expandedUrl;
}

QString CollapsedUrl::getUrl() const
{
	return _url;
}

} // twitter

} // tori