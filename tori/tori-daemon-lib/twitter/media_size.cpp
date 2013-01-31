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

QString _name;
	int _height;
	int _width;
	QString _resize;
	
MediaSizeInfo::MediaSizeInfo()
{

}

MediaSizeInfo::MediaSizeInfo(QJsonObject data)
{

}

MediaSizeInfo::MediaSizeInfo(const MediaSizeInfo& other)
{

}

MediaSizeInfo& MediaSizeInfo::operator=(const MediaSizeInfo& other)
{

}

MediaSizeInfo::~MediaSizeInfo()
{

}

QDBusArgument &operator<<(QDBusArgument &argument, const MediaSize& media)
{

}

const QDBusArgument &operator>>(const QDBusArgument &argument, MediaSize& media)
{

}

QString MediaSizeInfo::getName()
{

}

int MediaSizeInfo::getHeight()
{

}

int MediaSizeInfo::getWidth()
{

}

QString MediaSizeInfo::getResize()
{

}

} // twitter

} // tori