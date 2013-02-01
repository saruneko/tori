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
#include "mention.h"

namespace tori
{

namespace twitter
{

QString Mention::ID_STRING_KEY = "id_str";
QString Mention::NAME_KEY = "name";
QString Mention::SCREEN_NAME_KEY = "screen_name";

Mention::Mention()
{
}

Mention::Mention(const QJsonObject& data)
{
	if (data.contains(Mention::ID_STRING_KEY))
	{
		_idString = data[Mention::ID_STRING_KEY].toString();
		_id = _idString.toLongLong();
	}
	if (data.contains(Mention::NAME_KEY))
	{
		_name = data[Mention::NAME_KEY].toString();
	}
	if (data.contains(Mention::SCREEN_NAME_KEY))
	{
		_screenName = data[Mention::SCREEN_NAME_KEY].toString();
	}

}

Mention::Mention(const Mention& other):
	_id(other._id),
	_idString(other._idString),
	_name(other._name),
	_screenName(other._screenName)
{

}

Mention& Mention::operator=(const Mention& other)
{
	_id = other._id;
	_idString = other._idString;
	_name = other._name;
	_screenName = other._screenName;
	return *this;
}

Mention::~Mention()
{
}

QDBusArgument &operator<<(QDBusArgument &argument, const Mention& mention)
{
    argument.beginStructure();
    argument << mention._id;
    argument << mention._idString;
    argument << mention._name;
    argument << mention._screenName;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, Mention& mention)
{
    argument.beginStructure();
    argument >> mention._id;
    argument >> mention._idString;
    argument >> mention._name;
    argument >> mention._screenName;
    argument.endStructure();

    return argument;
}

qlonglong Mention::getId() const
{
	return _id;
}

QString Mention::getIdString() const
{
	return _idString;
}

QString Mention::getName() const
{
	return _name;
}

QString Mention::getScreenName() const
{
	return _screenName;
}

} // twitter

} // tori