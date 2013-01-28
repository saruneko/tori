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


#ifndef SIGNAL_MAPPER_H
#define SIGNAL_MAPPER_H

#include <QtDBus/QDBusPendingCallWatcher>
#include <QtCore/QList>

namespace tori
{

namespace dbus
{

// this is inspired by the QSignalMapper class
class DBusSignalMapperPrivate;
class DBusSignalMapper : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(DBusSignalMapper)
public:
    explicit DBusSignalMapper(QObject* parent = 0);
    ~DBusSignalMapper();

    void setMapping(QObject* sender, int id);
    void setMapping(QObject* sender, const QString& text);
    void setMapping(QObject* sender, QWidget* widget);
    void setMapping(QObject* sender, QObject* object);
    void removeMappings(QObject* sender);

    QObject* mapping(int id) const;
    QObject* mapping(const QString& text) const;
    QObject* mapping(QWidget* widget) const;
    QObject* mapping(QObject* object) const;

    static class _init
    {
        public:
            _init()
            {
                qRegisterMetaType<QDBusPendingCallWatcher*>("QDBusPendingCallWatcher*");
            }
    } _initializer;

Q_SIGNALS:
    void mapped(QDBusPendingCallWatcher* watcher, int id);
    void mapped(QDBusPendingCallWatcher* watcher, const QString& text);
    void mapped(QDBusPendingCallWatcher* watcher, QWidget* widget);
    void mapped(QDBusPendingCallWatcher* watcher, QObject* object);

public Q_SLOTS:
    void map(QDBusPendingCallWatcher* watcher);
    void map(QDBusPendingCallWatcher* watcher, QObject* sender);

protected:
    QScopedPointer<DBusSignalMapperPrivate> d_ptr;
    QList<QObject*> intMaps();
    QList<QObject*> stringMaps();
    QList<QObject*> widgetMaps();
    QList<QObject*> objectMaps();

private:
    Q_DISABLE_COPY(DBusSignalMapper)
    Q_PRIVATE_SLOT(d_func(), void _q_senderDestroyed())
};

} // dbus

} //tori

#endif // SIGNAL_MAPPER_H
