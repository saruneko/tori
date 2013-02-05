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

#ifndef CONTRIBUTOR_H
#define CONTRIBUTOR_H

#include <QString>
#include <QDBusArgument>
#include <QJsonObject>

namespace tori
{

namespace twitter
{

class Contributor
{
	Q_PROPERTY(qlonglong id READ getId)
	Q_PROPERTY(QString idAsString READ getIdString)
	Q_PROPERTY(QString screenName READ getScreenName)

public:
    Contributor();
    Contributor(const QJsonObject& jsonObject);
	Contributor(qlonglong id, const QString& screenName);
    Contributor(qlonglong id, const QString& idString, const QString& screenName);
    Contributor(const Contributor& other);
    Contributor& operator=(const Contributor& other);
    ~Contributor();

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Contributor& contributor);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Contributor& contributor);

    qlonglong getId() const;
    QString getIdString() const;
    QString getScreenName() const;

private:
    static const QString& ID_STRING_KEY;
    static const QString& SCREEN_NAME_KEY;

	qlonglong _id;
	QString _idString;
	QString _screenName;
};

} // twitter

} // tori

Q_DECLARE_METATYPE(tori::twitter::Contributor)

#endif // CONTRIBUTOR_H
