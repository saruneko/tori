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

#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H 

#include <QDBusArgument>
#include <QJsonObject>
#include <QList>
#include <QPair>
#include <QString>

namespace tori
{

namespace twitter
{

// define the type else Q_PORPERTY goes crazy
typedef QList< QPair<qlonglong, qlonglong> > PointCollection;

class BoundingBox
{
	Q_PROPERTY(PointCollection points READ getPoints)
	Q_PROPERTY(QString type READ getType)

public:
	BoundingBox();
	BoundingBox(QList< QPair<qlonglong, qlonglong> > points, QString type);
	BoundingBox(const QJsonObject& jsonObject);
	BoundingBox(const BoundingBox& other);
    BoundingBox& operator=(const BoundingBox& other);
    ~BoundingBox();


    friend QDBusArgument &operator<<(QDBusArgument &argument, const BoundingBox& box);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, BoundingBox& box);

	QList< QPair<qlonglong, qlonglong> > getPoints() const;
	QString getType() const;

private:
	QList< QPair<qlonglong, qlonglong> > _points;
	QString _type;
};

} // twitter

} // tori

Q_DECLARE_METATYPE(tori::twitter::PointCollection)
Q_DECLARE_METATYPE(tori::twitter::BoundingBox)
#endif // BOUNDING_BOX_H