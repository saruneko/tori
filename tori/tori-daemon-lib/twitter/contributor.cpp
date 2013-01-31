/**
 *
 * Copyright (c) 2013 Manuel de la Pena <mandel@themacaque.com>
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

#include <QDebug>
#include "contributor.h"

namespace tori
{

namespace twitter
{

QString Contributor::ID_STRING_KEY = "id_str";
QString Contributor::SCREEN_NAME_KEY = "screen_name";


Contributor::Contributor()
{
}

Contributor::Contributor(const QJsonObject& jsonObject)
{
	if (jsonObject.contains(Contributor::ID_STRING_KEY))
	{
		_idString = jsonObject[Contributor::ID_STRING_KEY].toString();

		bool idParsed;
		qlonglong id = _idString.toLongLong(&idParsed);

		if (idParsed)
		{
			_id = id;
		} 
		else
		{
			qCritical() << "Could not parse id " << _idString;
		}
	}
	if (jsonObject.contains(Contributor::SCREEN_NAME_KEY))
	{
		_screenName = jsonObject[Contributor::SCREEN_NAME_KEY].toString();
	}
}

Contributor::Contributor(qlonglong id, const QString& screenName) :
	_id(id), 
	_idString(QString::number(id)),
	_screenName(screenName)
{
}

Contributor::Contributor(qlonglong id, const QString& idString, const QString& screenName):
	_id(id),
	_idString(idString),
	_screenName(screenName)
{

}

Contributor::Contributor(const Contributor& other) :
	_id(other._id),
	_idString(other._idString),
	_screenName(other._screenName)
{

}

Contributor& Contributor::operator=(const Contributor& other)
{
	_id = other._id;
	_idString = other._idString;
	_screenName = other._screenName;
	
	return *this;
}

Contributor::~Contributor()
{
}

QDBusArgument &operator<<(QDBusArgument &argument, const Contributor& contributor)
{
    argument.beginStructure();
    argument << contributor._id;
    argument << contributor._idString;
    argument << contributor._screenName;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, Contributor& contributor)
{
    argument.beginStructure();
    argument >> contributor._id;
    argument >> contributor._idString;
    argument >> contributor._screenName;
    argument.endStructure();

    return argument;
}

qlonglong Contributor::getId() const
{
	return _id;
}

QString Contributor::getIdString() const
{
	return _idString;
}

QString Contributor::getScreenName() const
{
	return _screenName;
}

} // twitter

} // tori