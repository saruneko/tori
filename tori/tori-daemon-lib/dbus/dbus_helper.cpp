#include "dbus_helper.h"

namespace tori
{

namespace dbus
{

// required for the init
int DBusHelper::DBUS_STRING_MAP_ID = 0;
DBusHelper::_init DBusHelper::_initializer;

DBusHelper::DBusHelper(QObject *parent) :
    QObject(parent)
{
}


QVariant DBusHelper::getVariant(DBusStringHash hash)
{
    return QVariant(DBUS_STRING_MAP_ID, &hash);
}

} // dbus

} // tori
