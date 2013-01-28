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

#ifndef STATUS_API_H
#define STATUS_API_H

#include <QtKOAuth>
#include <QNetworkReply>
#include <QObject>
#include <QScopedPointer>
#include <QVariantMap>
#include "core/account.h"

namespace tori
{

namespace twitter
{

class UpdateData;
class TweetData;
class StatusAPIPrivate;
class StatusAPI : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(StatusAPI)
public:
    StatusAPI(tori::core::Account* account, QObject *parent = 0);
    ~StatusAPI();

public:
   void retweets(QString uuid, qlonglong tweet_id, QVariantMap options);
   void show(QString uuid, qlonglong tweet_id, QVariantMap options);
   void destroy(QString uuid, qlonglong tweet_id, QVariantMap options);
   void update(QString uuid, QString status, QVariantMap options);
   void retweet(QString uuid, qlonglong tweet_id, QVariantMap options);

Q_SIGNALS:
    void updateFinished(QString uuid);
    void updateError(QString uuid, int errorCode, QString errorMessage);

private:
    QScopedPointer<StatusAPIPrivate> d_ptr;

private:
    Q_PRIVATE_SLOT(d_func(), void onUpdateFinished(QByteArray, UpdateData*))
    Q_PRIVATE_SLOT(d_func(), void onDestroyFinished(QByteArray response, TweetData* data))
    Q_PRIVATE_SLOT(d_func(), void onShowFinished(QByteArray response, TweetData* data))

};

} // twitter

} // tori


#endif // STATUS_API_H
