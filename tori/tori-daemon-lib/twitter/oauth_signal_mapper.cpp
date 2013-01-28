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

#include <QHash>
#include "oauth_signal_mapper.h"

namespace tori
{

namespace twitter
{

class OAuthSignalMapperPrivate
{
    Q_DECLARE_PUBLIC(OAuthSignalMapper)
 public:
    OAuthSignalMapperPrivate(OAuthSignalMapper* parent) :
        q_ptr(parent) {}

    void _q_senderDestroyed() {
        Q_Q(OAuthSignalMapper);
        q->removeMappings(q->sender());
    }
    QHash<QObject*, int> intHash;
    QHash<QObject*, QString> stringHash;
    QHash<QObject*, QWidget*> widgetHash;
    QHash<QObject*, QObject*> objectHash;

private:
    OAuthSignalMapper* q_ptr;
};

OAuthSignalMapper::OAuthSignalMapper(QObject *parent) :
    QObject(parent),
    d_ptr(new OAuthSignalMapperPrivate(this))
{
}

OAuthSignalMapper::~OAuthSignalMapper()
{
}

void OAuthSignalMapper::setMapping(QObject* sender, int id)
{
    Q_D(OAuthSignalMapper);
    d->intHash.insert(sender, id);
    connect(sender, SIGNAL(destroyed()), this, SLOT(_q_senderDestroyed()));
}

void OAuthSignalMapper::setMapping(QObject* sender, const QString &text)
{
    Q_D(OAuthSignalMapper);
    d->stringHash.insert(sender, text);
    connect(sender, SIGNAL(destroyed()), this, SLOT(_q_senderDestroyed()));
}

void OAuthSignalMapper::setMapping(QObject* sender, QWidget *widget)
{
    Q_D(OAuthSignalMapper);
    d->widgetHash.insert(sender, widget);
    connect(sender, SIGNAL(destroyed()), this, SLOT(_q_senderDestroyed()));
}

void OAuthSignalMapper::setMapping(QObject* sender, QObject *object)
{
    Q_D(OAuthSignalMapper);
    d->objectHash.insert(sender, object);
    connect(sender, SIGNAL(destroyed()), this, SLOT(_q_senderDestroyed()));
}

QObject* OAuthSignalMapper::mapping(int id) const
{
    Q_D(const OAuthSignalMapper);
    return d->intHash.key(id);
}

QObject* OAuthSignalMapper::mapping(const QString& id) const
{
    Q_D(const OAuthSignalMapper);
    return d->stringHash.key(id);
}

QObject* OAuthSignalMapper::mapping(QWidget* widget) const
{
    Q_D(const OAuthSignalMapper);
    return d->widgetHash.key(widget);
}

QObject* OAuthSignalMapper::mapping(QObject* object) const
{
    Q_D(const OAuthSignalMapper);
    return d->objectHash.key(object);
}

void OAuthSignalMapper::removeMappings(QObject* sender)
{
    Q_D(OAuthSignalMapper);

    d->intHash.remove(sender);
    d->stringHash.remove(sender);
    d->widgetHash.remove(sender);
    d->objectHash.remove(sender);
}

void OAuthSignalMapper::map(QByteArray watcher)
{
    map(watcher, sender());
}

void OAuthSignalMapper::map(QByteArray watcher, QObject* sender)
{
    Q_D(OAuthSignalMapper);
    if (d->intHash.contains(sender))
        emit mapped(watcher, d->intHash.value(sender));
    if (d->stringHash.contains(sender))
        emit mapped(watcher, d->stringHash.value(sender));
    if (d->widgetHash.contains(sender))
        emit mapped(watcher, d->widgetHash.value(sender));
    if (d->objectHash.contains(sender))
        emit mapped(watcher, d->objectHash.value(sender));
}

QList<QObject*> OAuthSignalMapper::intMaps()
{
    Q_D(OAuthSignalMapper);
    return d->intHash.keys();
}

QList<QObject*> OAuthSignalMapper::stringMaps()
{
    Q_D(OAuthSignalMapper);
    return d->stringHash.keys();
}

QList<QObject*> OAuthSignalMapper::widgetMaps()
{
    Q_D(OAuthSignalMapper);
    return d->widgetHash.keys();
}

QList<QObject*> OAuthSignalMapper::objectMaps()
{
    Q_D(OAuthSignalMapper);
    return d->objectHash.keys();
}
} // twitter

} // tori

#include "moc_oauth_signal_mapper.cpp"
