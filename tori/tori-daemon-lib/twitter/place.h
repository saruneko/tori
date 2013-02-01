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

#ifndef PLACE_H
#define PLACE_H
#include <QString>
#include <QVariantMap>
#include <QDBusArgument>
#include <QJsonObject>
#include "bounding_box.h"

namespace tori
{

namespace twitter
{

class Place
{
	Q_PROPERTY(QVariantMap attributes READ getAttributes)
	Q_PROPERTY(BoundingBox boundingBox READ getBoundingBox)
	Q_PROPERTY(QString country READ getCountry)
	Q_PROPERTY(QString countryCode READ getCountryCode)
	Q_PROPERTY(QString fullName READ getFullName)
	Q_PROPERTY(QString id READ getId)
	Q_PROPERTY(QString name READ getName)
	Q_PROPERTY(QString placeType READ getPlaceType)
	Q_PROPERTY(QString url READ getUrl)

public:
	Place();
    Place(const QJsonObject& jsonObject);
    Place(QVariantMap attrs, BoundingBox boundingBox, QString country, QString countryCode, QString fullName,
    	QString id, QString name, QString placeType, QString url);
    Place(const Place& other);
    Place& operator=(const Place& other);
    ~Place();


    friend QDBusArgument &operator<<(QDBusArgument &argument, const Place& place);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Place& place);

    QVariantMap getAttributes() const;
    BoundingBox getBoundingBox() const;
    QString getCountry() const;
    QString getCountryCode() const;
    QString getFullName() const;
    QString getId() const;
    QString getName() const;
    QString getPlaceType() const;
    QString getUrl() const;

private:
	static QString ATTRIBUTES_KEY;
	static QString BOUNDING_BOX_KEY;
	static QString COUNTRY_KEY;
	static QString COUNTRY_CODE_KEY;
	static QString FULL_NAME_KEY;
	static QString ID_KEY;
	static QString NAME_KEY;
	static QString PLACE_TYPE_KEY;
	static QString URL_KEY;

	QVariantMap _attrs;
	BoundingBox _boundingBox;
	QString _country;
	QString _countryCode;
	QString _fullName;
	QString _id;
	QString _name;
	QString _placeType;
	QString _url;
};

} // twitter

} // tori

Q_DECLARE_METATYPE(tori::twitter::Place)
#endif // PLACE_H
