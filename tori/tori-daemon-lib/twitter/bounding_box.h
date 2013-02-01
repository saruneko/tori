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
#include <QJsonArray>
#include <QList>
#include <QPair>
#include <QString>

namespace tori
{

namespace twitter
{

class Point : public QPair<double, double>
{
	Q_PROPERTY(double x READ getX)
	Q_PROPERTY(double y READ getY)

public:
	Point();
	Point(const QJsonArray& jsonArray);
	Point(double x, double y);
	Point(const Point& other);
	Point& operator=(const Point& other);

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Point& box);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Point& box);

    double getX();
    double getY();
};

class BoundingBox
{
	Q_PROPERTY(QList<Point> points READ getPoints)
	Q_PROPERTY(QString type READ getType)

public:
	BoundingBox();
	BoundingBox(QList<Point> points, QString type);
	BoundingBox(const QJsonArray& jsonArray);
	BoundingBox(const BoundingBox& other);
    BoundingBox& operator=(const BoundingBox& other);
    ~BoundingBox();


    friend QDBusArgument &operator<<(QDBusArgument &argument, const BoundingBox& box);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, BoundingBox& box);

	QList<Point> getPoints() const;
	QString getType() const;

private:
	QList<Point> _points;
	QString _type;
};

} // twitter

} // tori

Q_DECLARE_METATYPE(tori::twitter::Point)
Q_DECLARE_METATYPE(tori::twitter::BoundingBox)
#endif // BOUNDING_BOX_H