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

#include "bounding_box.h"

namespace tori
{

namespace twitter
{

Point::Point() : QPair<double, double>()
{
}

Point::Point(const QJsonArray& jsonArray) : QPair<double, double>()
{
	first = jsonArray[0].toDouble();
	second = jsonArray[1].toDouble();
}

Point::Point(double x, double y) : QPair<double, double>(x, y)
{
}

Point::Point(const Point& other) : QPair<double, double>(other)
{
}

Point& Point::operator=(const Point& other)
{
	QPair<double, double>::operator=(other);
}

QDBusArgument &operator<<(QDBusArgument &argument, const Point& point)
{
    argument.beginStructure();
    argument << point.first;
    argument << point.second;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, Point& point)
{
    argument.beginStructure();
    argument >> point.first;
    argument >> point.second;
    argument.endStructure();

    return argument;
}

double Point::getX()
{
	return first;
}

double Point::getY()
{
	return second;
}

BoundingBox::BoundingBox()
{
}

BoundingBox::BoundingBox(QList<Point> points, QString type) :
	_points(points),
	_type(type)
{

}

BoundingBox::BoundingBox(const QJsonArray& jsonArray)
{
	// loop over the array and add the diff points foudn there
	for (int i = 0; i < jsonArray.count(); ++i)
	{
		_points.append(Point(jsonArray[i].toArray()));
	}
}

BoundingBox::BoundingBox(const BoundingBox& other) :
	_points(other._points),
	_type(other._type)
{

}

BoundingBox& BoundingBox::operator=(const BoundingBox& other)
{
	_points = other._points;
	_type = other._type;
	return *this;
}

BoundingBox::~BoundingBox()
{
}


QDBusArgument &operator<<(QDBusArgument &argument, const BoundingBox& box)
{
    argument.beginStructure();
    argument << box._points;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, BoundingBox& box)
{
    argument.beginStructure();
    argument >> box._points;
    argument.endStructure();

    return argument;
}

QList<Point> BoundingBox::getPoints() const
{
	return _points;
}

QString BoundingBox::getType() const
{
	return _type;
}

} // twitter

} // tori