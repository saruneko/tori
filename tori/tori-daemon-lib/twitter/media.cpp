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

#include "media.h"

namespace tori
{

namespace twitter
{

const QString& Media::DISPLAY_URL_KEY = "display_url";
const QString& Media::EXPANDED_URL_KEY = "expanded_url";
const QString& Media::ID_KEY = "id";
const QString& Media::ID_STRING_KEY = "id_str";
const QString& Media::MEDIA_URL_KEY = "media_url";
const QString& Media::MEDIA_HTTS_URL_KEY = "media_url_https";
const QString& Media::SIZE_KEY = "sizes";
const QString& Media::SOURCES_STATUS_ID_KEY = "source_status_id";
const QString& Media::SOURCES_STATUS_ID_STRING_KEY = "source_status_id_str";
const QString& Media::TYPE_KEY = "type";
const QString& Media::URL_KEY = "url";

Media::Media()
{
}

Media::Media(QJsonObject data)
{
    if (data.contains(Media::DISPLAY_URL_KEY))
    {
        _displayUrl = data[Media::DISPLAY_URL_KEY].toString();
    }
    if (data.contains(Media::EXPANDED_URL_KEY))
    {
        _expandedUrl = data[Media::EXPANDED_URL_KEY].toString();
    }
    if (data.contains(Media::ID_STRING_KEY))
    {
        _idString = data[Media::ID_STRING_KEY].toString();
        _id = _idString.toLongLong();
    }
    if (data.contains(Media::MEDIA_URL_KEY))
    {
        _mediaUrl = data[Media::MEDIA_URL_KEY].toString();
    }
    if (data.contains(Media::MEDIA_HTTS_URL_KEY))
    {
        _mediaHttpsUrl = data[Media::MEDIA_HTTS_URL_KEY].toString();
    }
    if (data.contains(Media::SIZE_KEY))
    {
        _size = MediaSize(data[Media::SIZE_KEY].toObject());
    }
    if (data.contains(Media::SOURCES_STATUS_ID_STRING_KEY))
    {
        _sourceStatusIdString = data[Media::SOURCES_STATUS_ID_STRING_KEY].toString();
        _sourceStatusId = _sourceStatusIdString.toLongLong();
    }
    if (data.contains(Media::TYPE_KEY))
    {
        _type = data[Media::TYPE_KEY].toString();
    }
    if (data.contains(Media::URL_KEY))
    {
        _url = data[Media::URL_KEY].toString();
    }

}

Media::Media(const Media& other) :
    _displayUrl(other._displayUrl),
    _expandedUrl(other._expandedUrl),
    _id(other._id),
    _idString(other._idString),
    _mediaUrl(other._mediaUrl),
    _mediaHttpsUrl(other._mediaHttpsUrl),
    _size(other._size),
    _sourceStatusId(other._sourceStatusId),
    _sourceStatusIdString(other._sourceStatusIdString),
    _type(other._type),
    _url(other._url)
{
}

Media& Media::operator=(const Media& other)
{

    _displayUrl = other._displayUrl;
    _expandedUrl = other._expandedUrl;
    _id = other._id;
    _idString = other._idString;
    _mediaUrl = other._mediaUrl;
    _mediaHttpsUrl = other._mediaHttpsUrl;
    _size = other._size;
    _sourceStatusId = other._sourceStatusId;
    _sourceStatusIdString = other._sourceStatusIdString;
    _type = other._type;
    _url = other._url;

    return *this;
}

Media::~Media()
{

}

QDBusArgument &operator<<(QDBusArgument &argument, const Media& media)
{
    argument.beginStructure();
    argument << media._displayUrl; 
    argument << media._expandedUrl;
    argument << media._id;
    argument << media._idString;
    argument << media._mediaUrl;
    argument << media._mediaHttpsUrl;
    argument << media._size;
    argument << media._sourceStatusId;
    argument << media._type;
    argument << media._url;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, Media& media)
{
    argument.beginStructure();
    argument >> media._displayUrl; 
    argument >> media._expandedUrl;
    argument >> media._id;
    argument >> media._idString;
    argument >> media._mediaUrl;
    argument >> media._mediaHttpsUrl;
    argument >> media._size;
    argument >> media._sourceStatusId;
    argument >> media._type;
    argument >> media._url;

    argument.endStructure();

    return argument;
}

QString Media::getDisplayUrl() const
{
    return _displayUrl;
}

QString Media::getExpandedUrl() const
{
    return _expandedUrl;
}

qlonglong Media::getId() const
{
    return _id;
}

QString Media::getIdString() const
{
    return _idString;
}

QString Media::getMediaUrl() const
{
    return _mediaUrl;
}

QString Media::getMediaHttpsUrl() const
{
    return _mediaHttpsUrl;
}

MediaSize Media::getSizes() const
{
    return _size;
}

qlonglong Media::getSourceStatusId() const
{
    return _sourceStatusId;
}

QString Media::getSourceStatusIdString() const
{
    return _sourceStatusIdString;
}

QString Media::getType() const
{
    return _type;
}

QString Media::getUrl() const
{
    return _url;
}

} // twitter

} // tori