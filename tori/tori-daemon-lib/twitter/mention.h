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
#ifndef MENTION_H
#define MENTION_H
#include <QString>
#include <QDBusArgument>
#include <QJsonObject>

namespace tori
{

namespace twitter
{

class Mention
{
	Q_PROPERTY(qlonglong id READ getId)
	Q_PROPERTY(QString idString READ getIdString)
	Q_PROPERTY(QString name READ getName)
	Q_PROPERTY(QString screenName READ getScreenName)

public:
	Mention();
	Mention(const QJsonObject& data);
    Mention(const Mention& other);
    Mention& operator=(const Mention& other);
    ~Mention();

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Mention& mention);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Mention& mention);

    qlonglong getId() const;
    QString getIdString() const;
    QString getName() const;
    QString getScreenName() const;

private:
	static const QString& ID_STRING_KEY;
	static const QString& NAME_KEY;
	static const QString& SCREEN_NAME_KEY;
	
	qlonglong _id;
	QString _idString;
	QString _name;
	QString _screenName;
};

} // twitter

} // tori

Q_DECLARE_METATYPE(tori::twitter::Mention)

#endif