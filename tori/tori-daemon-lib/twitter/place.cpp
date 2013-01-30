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

#include "place.h"

namespace tori
{

namespace twiiter
{

QString Place::ATTRIBUTES_KEY = "attributes";
QString Place::BOUNDING_BOX_KEY = "bounding_box ";
QString Place::COUNTRY_KEY = "country";
QString Place::COUNTRY_CODE_KEY = "country_code ";
QString Place::FULL_NAME_KEY = "full_name";
QString Place::ID_KEY = "id";
QString Place::NAME_KEY = "name";
QString Place::PLACE_TYPE_KEY= "place_type";
QString Place::URL_KEY = "url";

Place::Place(const QJsonObject* jsonObject)
{
	if (jsonObject.contains(Place::ATTRIBUTES_KEY))
	{
		// get the data and parse it
		QJsonObject data = jsonObject[Place::ATTRIBUTES_KEY].toObject();
		foreach(QString key, data.keys())
		{
			_attrs[key] = data[key].toString();
		}
	}
	if (jsonObject.contains(Place::BOUNDING_BOX_KEY))
	{
		QJsonObject data = jsonObject[Place::BOUNDING_BOX_KEY].toObject();
		_boundingBox = BoundingBox(data);
	}
	if (jsonObject.contains(Place::COUNTRY_KEY))
	{
		_country = jsonObject[Place::COUNTRY_KEY].toString();
	}
	if (jsonObject.contains(Place::COUNTRY_CODE_KEY))
	{
		_countryCode = jsonObject[Place::COUNTRY_CODE_KEY].toString();
	}
	if (jsonObject.contains(Place::FULL_NAME_KEY))
	{
		_fullName = jsonObject[Place::FULL_NAME_KEY].toString();
	}
	if (jsonObject.contains(Place::ID_KEY))
	{
		_id = jsonObject[Place::ID_KEY].toString();
	}
	if (jsonObject.contains(Place::NAME_KEY))
	{
		_name = jsonObject[Place::NAME_KEY].toString();
	}
	if (jsonObject.contains(Place::PLACE_TYPE_KEY))
	{
		_placeType = jsonObject[Place::PLACE_TYPE_KEY].toString();
	}
	if (jsonObject.contains(Place::URL_KEY))
	{
		_url = jsonObject[Place::URL_KEY].toString();
	}
}

Place::Place(QVariantMap attrs, BoundingBox boundingBox, QString country, QString countryCode, QString fullName,
	QString id, QString name, QString placeType, QString url) :
	_attrs(attrs),
	_boundingBox(boundingBox),
	_country(country),
	_countryCode(countryCode),
	_fullName(fullName),
	_id(id),
	_name(name),
	_placeType(placeType),
	_url(url)
{
}

Place::Place(const Place& other) :
	_attrs(other._attrs),
	_boundingBox(other._boundingBox),
	_country(other._country),
	_countryCode(other._countryCode),
	_fullName(other._fullName),
	_id(other._id),
	_name(other._name),
	_placeType(other._placeType),
	_url(other._url)
{
}

Place& Place::operator=(const Place& other)
{
	_attrs = other._attrs;
	_boundingBox = other._boundingBox;
	_country = other._country;
	_countryCode = other._countryCode;
	_fullName = other._fullName;
	_id = other._id;
	_name = other._name;
	_placeType = other._placeType;
	_url = other._url;

	return *this;
}

Place::~Place()
{
}


QDBusArgument &operator<<(QDBusArgument &argument, const Place& place)
{
    argument.beginStructure();
    argument << place._attrs;
    argument << place._boundingBox;
    argument << place._country;
    argument << place._countryCode;
    argument << place._fullName;
    argument << place._id;
    argument << place._name;
    argument << place._placeType;
    argument << place._url;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, Place& place)
{
	argument.beginStructure();
    argument >> place._attrs;
    argument >> place._boundingBox;
    argument >> place._country;
    argument >> place._countryCode;
    argument >> place._fullName;
    argument >> place._id;
    argument >> place._name;
    argument >> place._placeType;
    argument >> place._url;
    argument.endStructure();

    return argument;
}

QVariantMap Place::getAttributes() const
{
	return _attrs;
}

BoundingBox getBoundingBox() const
{
	return _boundingBox;
}

QString getCountry() const
{
	return _country;
}

QString getCountryCode() const
{
	return _countryCode;
}

QString getFullName() const
{
	return _fullName;
}

QString getId() const
{
	return _id;
}

QString getName() const
{
	return _name;
}

QString getPlaceType() const
{
	return _placeType;
}

QString getUrl() const
{
	return _url;
}

} // twitter

} // tori
