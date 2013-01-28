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

#include <QtCore/QHash>
#include "signal_mapper.h"

namespace tori
{

namespace dbus
{

DBusSignalMapper::_init DBusSignalMapper::_initializer;

class DBusSignalMapperPrivate
{
    Q_DECLARE_PUBLIC(DBusSignalMapper)
 public:
    DBusSignalMapperPrivate(DBusSignalMapper* parent) :
        q_ptr(parent) {}

    void _q_senderDestroyed() {
        Q_Q(DBusSignalMapper);
        q->removeMappings(q->sender());
    }
    QHash<QObject*, int> intHash;
    QHash<QObject*, QString> stringHash;
    QHash<QObject*, QWidget*> widgetHash;
    QHash<QObject*, QObject*> objectHash;

private:
    DBusSignalMapper* q_ptr;
};

DBusSignalMapper::DBusSignalMapper(QObject *parent) :
    QObject(parent),
    d_ptr(new DBusSignalMapperPrivate(this))
{
}

DBusSignalMapper::~DBusSignalMapper()
{
}

void DBusSignalMapper::setMapping(QObject* sender, int id)
{
    Q_D(DBusSignalMapper);
    d->intHash.insert(sender, id);
    connect(sender, SIGNAL(destroyed()), this, SLOT(_q_senderDestroyed()));
}

void DBusSignalMapper::setMapping(QObject* sender, const QString &text)
{
    Q_D(DBusSignalMapper);
    d->stringHash.insert(sender, text);
    connect(sender, SIGNAL(destroyed()), this, SLOT(_q_senderDestroyed()));
}

void DBusSignalMapper::setMapping(QObject* sender, QWidget *widget)
{
    Q_D(DBusSignalMapper);
    d->widgetHash.insert(sender, widget);
    connect(sender, SIGNAL(destroyed()), this, SLOT(_q_senderDestroyed()));
}

void DBusSignalMapper::setMapping(QObject* sender, QObject *object)
{
    Q_D(DBusSignalMapper);
    d->objectHash.insert(sender, object);
    connect(sender, SIGNAL(destroyed()), this, SLOT(_q_senderDestroyed()));
}

QObject* DBusSignalMapper::mapping(int id) const
{
    Q_D(const DBusSignalMapper);
    return d->intHash.key(id);
}

QObject* DBusSignalMapper::mapping(const QString& id) const
{
    Q_D(const DBusSignalMapper);
    return d->stringHash.key(id);
}

QObject* DBusSignalMapper::mapping(QWidget* widget) const
{
    Q_D(const DBusSignalMapper);
    return d->widgetHash.key(widget);
}

QObject* DBusSignalMapper::mapping(QObject* object) const
{
    Q_D(const DBusSignalMapper);
    return d->objectHash.key(object);
}

void DBusSignalMapper::removeMappings(QObject* sender)
{
    Q_D(DBusSignalMapper);

    d->intHash.remove(sender);
    d->stringHash.remove(sender);
    d->widgetHash.remove(sender);
    d->objectHash.remove(sender);
}

void DBusSignalMapper::map(QDBusPendingCallWatcher* watcher)
{
    map(watcher, sender());
}

void DBusSignalMapper::map(QDBusPendingCallWatcher* watcher, QObject* sender)
{
    Q_D(DBusSignalMapper);
    if (d->intHash.contains(sender))
        emit mapped(watcher, d->intHash.value(sender));
    if (d->stringHash.contains(sender))
        emit mapped(watcher, d->stringHash.value(sender));
    if (d->widgetHash.contains(sender))
        emit mapped(watcher, d->widgetHash.value(sender));
    if (d->objectHash.contains(sender))
        emit mapped(watcher, d->objectHash.value(sender));
}

QList<QObject*> DBusSignalMapper::intMaps()
{
    Q_D(DBusSignalMapper);
    return d->intHash.keys();
}

QList<QObject*> DBusSignalMapper::stringMaps()
{
    Q_D(DBusSignalMapper);
    return d->stringHash.keys();
}

QList<QObject*> DBusSignalMapper::widgetMaps()
{
    Q_D(DBusSignalMapper);
    return d->widgetHash.keys();
}

QList<QObject*> DBusSignalMapper::objectMaps()
{
    Q_D(DBusSignalMapper);
    return d->objectHash.keys();
}


} // dbus

} // tori

#include "moc_signal_mapper.cpp"
