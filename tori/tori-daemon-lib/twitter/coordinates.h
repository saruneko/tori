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

#ifndef COORDINATES_H
#define COORDINATES_H

#include <QString>
#include <QDBusArgument>

class Coordinates
{
    Q_PROPERTY(qlonglong longitude READ getLongitude)
    Q_PROPERTY(qlonglong latitude READ getLatitude)
    Q_PROPERTY(QString type READ getType)

public:
    Coordinates(const QJsonObject& jsonObject);
    Coordinates(qlonglong longitude, qlonglong latitude, QString type);
    Coordinates(const Coordinates& other);
    Coordinates& operator=(const Coordinates& other);
    ~Coordinates();

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Coordinates& coordinates);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Coordinates& coordinates);

    qlonglong getLongitude() const;
    qlonglong getLatitude() const;
    QString getType() const;

private:
    static QString COORDINATES_KEY;
    static QString TYPE_KEY;

	qlonglong _longitude;
	qlonglong _latitude;
	QString _type;
};

#endif // COORDINATES_H
