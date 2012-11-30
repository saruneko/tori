#include "secret.h"


Secret::Secret() :
    _session(),
    _parameters(),
    _value(),
    _contentType()
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
