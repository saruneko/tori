/**
 *
 * Copyright (c) 2012 mandel
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

#ifndef OAUTH_H
#define OAUTH_H

#include <QUrl>
#include <QObject>

namespace tori
{

namespace twitter
{

class OAuthPrivate;
class OAuth : public QObject
{

    Q_DECLARE_PRIVATE(OAuth)
    Q_OBJECT
public:
    enum HttpMethod {GET, POST, PUT, DELETE};
    static const QByteArray AUTH_HEADER;

    OAuth(const QByteArray& consumerKey, const QByteArray& consumerSecret,
        const QByteArray& token, const QByteArray& tokenSecret, QObject *parent = 0);
    ~OAuth();

    QByteArray generateAuthorizationHeader(const QUrl& url, HttpMethod method);

private:
    QScopedPointer<OAuthPrivate> d_ptr;
};

} // twitter

} // tori

#endif // OAUTH_H
