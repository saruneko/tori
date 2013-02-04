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
#include <QDebug>
#include "coordinates.h"

namespace tori
{

namespace twitter
{

const QString& Coordinates::COORDINATES_KEY = "coordinates";
const QString& Coordinates::TYPE_KEY = "type";

Coordinates::Coordinates()
{
}

Coordinates::Coordinates(const QJsonObject& jsonObject)
{
	if (jsonObject.contains(Coordinates::COORDINATES_KEY))
	{
		QJsonArray array = jsonObject[Coordinates::COORDINATES_KEY].toArray();

		bool longitudeParsed, latitudeParsed;

		_longitude = array[0].toString().toLongLong(&longitudeParsed);
		_latitude = array[1].toString().toLongLong(&latitudeParsed);
		if (!longitudeParsed || !latitudeParsed)
		{
			qCritical() << "COuld not parsed longitud " << array[0] << " or latitude" << array[1];
		}
	}
	if (jsonObject.contains(Coordinates::TYPE_KEY))
	{
		_type = jsonObject[Coordinates::TYPE_KEY].toString();
	}
}

Coordinates::Coordinates(qlonglong longitude, qlonglong latitude, const QString& type) :
	_longitude(longitude),
	_latitude(latitude),
	_type(type)
{

}

Coordinates::Coordinates(const Coordinates& other) :
	_longitude(other._longitude),
	_latitude(other._latitude),
	_type(other._type)
{
}

Coordinates& Coordinates::operator=(const Coordinates& other)
{
	_longitude = other._latitude;
	_latitude = other._latitude;
	_type = other._type;

	return *this;
}

Coordinates::~Coordinates()
{
}

QDBusArgument &operator<<(QDBusArgument &argument, const Coordinates& coordinates)
{
    argument.beginStructure();
    argument << coordinates._longitude;
    argument << coordinates._latitude;
    argument << coordinates._type;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, Coordinates& coordinates)
{
	argument.beginStructure();
    argument >> coordinates._longitude;
    argument >> coordinates._latitude;
    argument >> coordinates._type;
    argument.endStructure();

    return argument;
}

qlonglong Coordinates::getLongitude() const
{
	return _longitude;
}

qlonglong Coordinates::getLatitude() const
{
	return _latitude;
}

QString Coordinates::getType() const
{
	return _type;
}

} // twitter

} // tori