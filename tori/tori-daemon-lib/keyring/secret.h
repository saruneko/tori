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

#ifndef SECRET_H
#define SECRET_H

#include <QtDBus>
#include <QByteArray>
#include <QHash>
#include <QString>
#include "dbus/dbus_helper.h"

class Secret
{
    Q_PROPERTY(QString session READ getSession)
    Q_PROPERTY(QByteArray parameters READ getParameters)
    Q_PROPERTY(QByteArray value READ getValue)
    Q_PROPERTY(QString contentType READ getContentType)

public:
    Secret();
    Secret(QDBusObjectPath session, QByteArray parameters, QByteArray value, QString contentType);
    Secret(const Secret& other);
    Secret& operator=(const Secret& other);
    ~Secret();

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Secret& secret);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Secret &secret);

    //register Secret with the Qt type system
    static void registerMetaType();

    // property getters
    QString getSession() const;
    QByteArray getParameters() const;
    QByteArray getValue() const;
    QString getContentType() const;

private:
    QDBusObjectPath _session;
    QByteArray _parameters;
    QByteArray _value;
    QString _contentType;
};

typedef QHash<QDBusObjectPath, Secret> DBusSecretHash;

Q_DECLARE_METATYPE(DBusSecretHash)
Q_DECLARE_METATYPE(Secret)

#endif // SECRET_H
