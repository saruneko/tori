/**
 *
 * Copyright (c) 2012 Manuel de la Pena <mandel@themacaque.com>
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

#include "secret.h"


Secret::Secret() :
    _session(),
    _parameters(),
    _value(),
    _contentType()
{
}

Secret::Secret(QDBusObjectPath session, QByteArray parameters, QByteArray value, QString contentType) :
    _session(session),
    _parameters(parameters),
    _value(value),
    _contentType(contentType)
{
}

Secret::Secret(const Secret& other) :
    _session(other._session),
    _parameters(other._parameters),
    _value(other._value),
    _contentType(other._contentType)
{
}

Secret& Secret::operator=(const Secret& other)
{
    _session = other._session;
    _parameters = other._parameters;
    _value = other._value;
    _contentType = other._contentType;

    return *this;
}

Secret::~Secret()
{
}

void Secret::registerMetaType()
{
    qRegisterMetaType<Secret>("Secret");
    qDBusRegisterMetaType<Secret>();
}

QDBusArgument &operator<<(QDBusArgument &argument, const Secret& secret)
{
    argument.beginStructure();
    argument << secret._session;
    argument << secret._parameters;
    argument << secret._value;
    argument << secret._contentType;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, Secret &secret)
{
    argument.beginStructure();
    argument >> secret._session;
    argument >> secret._parameters;
    argument >> secret._value;
    argument >> secret._contentType;
    argument.endStructure();

    return argument;
}

QString Secret::getSession() const
{
    return _session.path();
}

QByteArray Secret::getParameters() const
{
    return _parameters;
}

QByteArray Secret::getValue() const
{
    return _value;
}

QString Secret::getContentType() const
{
    return _contentType;
}
