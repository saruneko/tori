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

#include "media_size.h"

namespace tori
{

namespace twitter
{

const QString& MediaSizeInfo::HEIGHT_KEY = "h";
const QString& MediaSizeInfo::WIDTH_KEY = "w";
const QString& MediaSizeInfo::RESIZE_KEY = "resize";

MediaSizeInfo::MediaSizeInfo()
{
}

MediaSizeInfo::MediaSizeInfo(QString name, double height, double width, QString resize) :
	_name(name),
	_height(height),
	_width(width),
	_resize(resize)
{
}

MediaSizeInfo::MediaSizeInfo(QString name, QJsonObject data):
	_name(name)
{
	if (data.contains(MediaSizeInfo::HEIGHT_KEY))
	{
		_height = data[MediaSizeInfo::HEIGHT_KEY].toDouble();
	}

	if (data.contains(MediaSizeInfo::WIDTH_KEY))
	{
		_width = data[MediaSizeInfo::WIDTH_KEY].toDouble();	
	}

	if (data.contains(MediaSizeInfo::RESIZE_KEY))
	{
		_resize = data[MediaSizeInfo::RESIZE_KEY].toString();
	}

}

MediaSizeInfo::MediaSizeInfo(const MediaSizeInfo& other):
	_name(other._name),
	_height(other._height),
	_width(other._width),
	_resize(other._resize)
{

}

MediaSizeInfo& MediaSizeInfo::operator=(const MediaSizeInfo& other)
{
	_name = other._name;
	_height = other._height;
	_width = other._width;
	_resize = other._resize;
	return *this;
}

MediaSizeInfo::~MediaSizeInfo()
{

}

QDBusArgument &operator<<(QDBusArgument &argument, const MediaSizeInfo& mediaSizeInfo)
{
    argument.beginStructure();
    argument << mediaSizeInfo._name;
    argument << mediaSizeInfo._height;
    argument << mediaSizeInfo._width;
    argument << mediaSizeInfo._resize;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, MediaSizeInfo& mediaSizeInfo)
{
    argument.beginStructure();
    argument >> mediaSizeInfo._name;
    argument >> mediaSizeInfo._height;
    argument >> mediaSizeInfo._width;
    argument >> mediaSizeInfo._resize;
    argument.endStructure();

    return argument;
}

QString MediaSizeInfo::getName() const
{
	return _name;
}

double MediaSizeInfo::getHeight() const
{
	return _height;
}

double MediaSizeInfo::getWidth() const
{
	return _width;
}

QString MediaSizeInfo::getResize() const
{
	return _resize;
}

MediaSize::MediaSize()
{

}

MediaSize::MediaSize(QJsonObject data)
{
	foreach(QString size, data.keys())
	{
		_sizes.append(MediaSizeInfo(size, data[size].toObject()));
	}
}

MediaSize::MediaSize(const MediaSize& other) :
	_sizes(other._sizes)
{
}

MediaSize& MediaSize::operator=(const MediaSize& other)
{
	_sizes = other._sizes;
	return *this;
}

MediaSize::~MediaSize()
{

}

QDBusArgument &operator<<(QDBusArgument &argument, const MediaSize& mediaSize)
{
    argument.beginStructure();
    argument << mediaSize._sizes;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, MediaSize& mediaSize)
{
    argument.beginStructure();
	argument >> mediaSize._sizes;
    argument.endStructure();

    return argument;
}

QList<MediaSizeInfo> MediaSize::getSizes() const
{
	return _sizes;
}

} // twitter

} // tori