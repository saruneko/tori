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

#include <QNetworkAccessManager>
#include <QObject>
#include <QScopedPointer>
#include <QVariantMap>
#include "oauth.h"

namespace tori
{

namespace twitter
{

class StatusAPIPrivate;
class StatusAPI : public QObject
{
    Q_DECLARE_PRIVATE(StatusAPI)
    Q_OBJECT
public:
    StatusAPI(OAuth* oauth, QNetworkAccessManager* man, QObject *parent = 0);
    ~StatusAPI();
    
public:
   void retweets(uint tweet_id, QVariantMap options);
   void show(uint tweet_id, QVariantMap options);
   void destroy(uint tweet_id, QVariantMap options);
   void update(QString status, QVariantMap options);
   void retweet(uint tweet_id, QVariantMap options);

private:
    QScopedPointer<StatusAPIPrivate> d_ptr;
};

} // twitter

} // tori

#endif // STATUS_API_H
