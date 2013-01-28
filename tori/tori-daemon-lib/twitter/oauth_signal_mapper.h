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

#ifndef OAUTH_SIGNAL_MAPPER_H
#define OAUTH_SIGNAL_MAPPER_H

#include <QObject>

namespace tori
{

namespace twitter
{

// this is inspired by the QSignalMapper class
class OAuthSignalMapperPrivate;
class OAuthSignalMapper : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(OAuthSignalMapper)
public:
    explicit OAuthSignalMapper(QObject* parent = 0);
    ~OAuthSignalMapper();

    void setMapping(QObject* sender, int id);
    void setMapping(QObject* sender, const QString& text);
    void setMapping(QObject* sender, QWidget* widget);
    void setMapping(QObject* sender, QObject* object);
    void removeMappings(QObject* sender);

    QObject* mapping(int id) const;
    QObject* mapping(const QString& text) const;
    QObject* mapping(QWidget* widget) const;
    QObject* mapping(QObject* object) const;

Q_SIGNALS:
    void mapped(QByteArray data, int id);
    void mapped(QByteArray data, const QString& text);
    void mapped(QByteArray data, QWidget* widget);
    void mapped(QByteArray data, QObject* object);

public Q_SLOTS:
    void map(QByteArray data);
    void map(QByteArray data, QObject* sender);

protected:
    QScopedPointer<OAuthSignalMapperPrivate> d_ptr;
    QList<QObject*> intMaps();
    QList<QObject*> stringMaps();
    QList<QObject*> widgetMaps();
    QList<QObject*> objectMaps();

private:
    Q_DISABLE_COPY(OAuthSignalMapper)
    Q_PRIVATE_SLOT(d_func(), void _q_senderDestroyed())
};

} // twitter

} // tori

#endif // OAUTH_SIGNAL_MAPPER_H
