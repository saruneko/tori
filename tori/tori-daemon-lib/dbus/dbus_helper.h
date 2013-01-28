/**
 *
 * Copyright (c) 2012 mandel
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

#ifndef DBUS_HELPER_H
#define DBUS_HELPER_H

#include <QDBusMetaType>
#include <QDBusObjectPath>
#include <QHash>
#include <QObject>

typedef QHash<QString, QString> DBusStringHash;
typedef QHash<QString, QDBusObjectPath> DBusObjectPathHash;

namespace tori
{

namespace dbus
{

class DBusHelper : public QObject
{
    Q_OBJECT
public:
    static int DBUS_STRING_MAP_ID;
    static int DBUS_OBJECTPATH_MAP_ID;

    explicit DBusHelper(QObject *parent = 0);

    static class _init
    {
        public:
            _init()
            {
                // diff actions to init
                qRegisterMetaType<DBusStringHash>("DBusStringHash");
                qDBusRegisterMetaType<DBusStringHash>();
                DBUS_STRING_MAP_ID = QMetaType::type("DBusStringHash");

                qRegisterMetaType<DBusObjectPathHash>("DBusObjectPathHash");
                qDBusRegisterMetaType<DBusObjectPathHash>();
                DBUS_OBJECTPATH_MAP_ID = QMetaType::type("DBusObjectPathHash");
            }
    } _initializer;

    static QVariant getVariant(DBusStringHash hash);

};

} // dbus

} // tori

Q_DECLARE_METATYPE(DBusStringHash)
Q_DECLARE_METATYPE(DBusObjectPathHash)

#endif // DBUS_HELPER_H
