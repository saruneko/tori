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


#include "keyring_signal_mapper.h"


namespace tori
{

namespace keyring
{

KeyringSignalMapper::_init KeyringSignalMapper::_initializer;

class KeyringSignalMapperPrivate
{
    Q_DECLARE_PUBLIC(KeyringSignalMapper)
 public:
    KeyringSignalMapperPrivate(KeyringSignalMapper* parent) :
        q_ptr(parent) {}

    void _q_senderDestroyed() {
        Q_Q(KeyringSignalMapper);
        q->removeMappings(q->sender());
    }
    QHash<QObject*, int> intHash;
    QHash<QObject*, QString> stringHash;
    QHash<QObject*, QWidget*> widgetHash;
    QHash<QObject*, QObject*> objectHash;

private:
    KeyringSignalMapper* q_ptr;
};

KeyringSignalMapper::KeyringSignalMapper(QObject *parent) :
    QObject(parent),
    d_ptr(new KeyringSignalMapperPrivate(this))
{
}

KeyringSignalMapper::~KeyringSignalMapper()
{
}

void KeyringSignalMapper::setMapping(QObject* sender, int id)
{
    Q_D(KeyringSignalMapper);
    d->intHash.insert(sender, id);
    connect(sender, SIGNAL(destroyed()), this, SLOT(_q_senderDestroyed()));
}

void KeyringSignalMapper::setMapping(QObject* sender, const QString &text)
{
    Q_D(KeyringSignalMapper);
    d->stringHash.insert(sender, text);
    connect(sender, SIGNAL(destroyed()), this, SLOT(_q_senderDestroyed()));
}

void KeyringSignalMapper::setMapping(QObject* sender, QWidget *widget)
{
    Q_D(KeyringSignalMapper);
    d->widgetHash.insert(sender, widget);
    connect(sender, SIGNAL(destroyed()), this, SLOT(_q_senderDestroyed()));
}

void KeyringSignalMapper::setMapping(QObject* sender, QObject *object)
{
    Q_D(KeyringSignalMapper);
    d->objectHash.insert(sender, object);
    connect(sender, SIGNAL(destroyed()), this, SLOT(_q_senderDestroyed()));
}

QObject* KeyringSignalMapper::mapping(int id) const
{
    Q_D(const KeyringSignalMapper);
    return d->intHash.key(id);
}

QObject* KeyringSignalMapper::mapping(const QString& id) const
{
    Q_D(const KeyringSignalMapper);
    return d->stringHash.key(id);
}

QObject* KeyringSignalMapper::mapping(QWidget* widget) const
{
    Q_D(const KeyringSignalMapper);
    return d->widgetHash.key(widget);
}

QObject* KeyringSignalMapper::mapping(QObject* object) const
{
    Q_D(const KeyringSignalMapper);
    return d->objectHash.key(object);
}

void KeyringSignalMapper::removeMappings(QObject* sender)
{
    Q_D(KeyringSignalMapper);

    d->intHash.remove(sender);
    d->stringHash.remove(sender);
    d->widgetHash.remove(sender);
    d->objectHash.remove(sender);
}

void KeyringSignalMapper::map(bool dismissed, const QDBusVariant result)
{
    map(dismissed, result, sender());
}

void KeyringSignalMapper::map(bool dismissed, const QDBusVariant result, QObject* sender)
{
    Q_D(KeyringSignalMapper);
    if (d->intHash.contains(sender))
        emit mapped(dismissed, result, d->intHash.value(sender));
    if (d->stringHash.contains(sender))
        emit mapped(dismissed, result, d->stringHash.value(sender));
    if (d->widgetHash.contains(sender))
        emit mapped(dismissed, result, d->widgetHash.value(sender));
    if (d->objectHash.contains(sender))
        emit mapped(dismissed, result, d->objectHash.value(sender));
}

QList<QObject*> KeyringSignalMapper::intMaps()
{
    Q_D(KeyringSignalMapper);
    return d->intHash.keys();
}

QList<QObject*> KeyringSignalMapper::stringMaps()
{
    Q_D(KeyringSignalMapper);
    return d->stringHash.keys();
}

QList<QObject*> KeyringSignalMapper::widgetMaps()
{
    Q_D(KeyringSignalMapper);
    return d->widgetHash.keys();
}

QList<QObject*> KeyringSignalMapper::objectMaps()
{
    Q_D(KeyringSignalMapper);
    return d->objectHash.keys();
}


} // keyring

} // tori

#include "moc_keyring_signal_mapper.cpp"
