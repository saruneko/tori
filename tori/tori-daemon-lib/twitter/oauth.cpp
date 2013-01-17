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

#include <QByteArray>
#include <QDateTime>
#include <QtAlgorithms>
#include <QCryptographicHash>
#include <QtDebug>

#include "oauth.h"

namespace tori
{

namespace twitter
{

static QByteArray hmacSha1(const QByteArray& message, const QByteArray& key)
{
    QByteArray normKey;

    if (key.size() > 64) {
        normKey = QCryptographicHash::hash(key, QCryptographicHash::Sha1);
    } else {
        normKey = key; // no need for zero padding ipad and opad are filled with zeros
    }

    unsigned char* K = (unsigned char *)normKey.constData();

    unsigned char ipad[65];
    unsigned char opad[65];

    memset(ipad, 0, 65);
    memset(opad, 0, 65);

    memcpy(ipad, K, normKey.size());
    memcpy(opad, K, normKey.size());

    for (int i = 0; i < 64; ++i) {
        ipad[i] ^= 0x36;
        opad[i] ^= 0x5c;
    }

    QByteArray context;
    context.append((const char *)ipad, 64);
    context.append(message);

    QByteArray sha1 = QCryptographicHash::hash(context, QCryptographicHash::Sha1);

    context.clear();
    context.append((const char *)opad, 64);
    context.append(sha1);

    sha1.clear();

    sha1 = QCryptographicHash::hash(context, QCryptographicHash::Sha1);

    return sha1;
}

static QByteArray generateTimeStamp()
{
    QDateTime current = QDateTime::currentDateTime();
    uint seconds = current.toTime_t();

    return QString("%1").arg(seconds).toUtf8();
}

static QByteArray generateNonce()
{
    QByteArray chars("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
    int max = chars.size();
    int len = 16;

    QByteArray nonce;
    for(int i = 0; i < len; ++i){
        nonce.append( chars[qrand() % max] );
    }
    return nonce;
}


class OAuthPrivate
{
    Q_DECLARE_PUBLIC(OAuth)
public:

    OAuthPrivate(const QByteArray& consumerKey, const QByteArray& consumerSecret,
        const QByteArray& token, const QByteArray& tokenSecret, OAuth* parent);

    QByteArray generateAuthorizationHeader(const QUrl& url, OAuth::HttpMethod method);

private:
    QByteArray generateSignatureHMACSHA1(const QByteArray& signatureBase);
    QByteArray generateSignatureBase(const QUrl& url, OAuth::HttpMethod method, const QByteArray& timestamp, const QByteArray& nonce);

    QByteArray _consumerKey;
    QByteArray _consumerSecret;
    QByteArray _token;
    QByteArray _tokenSecret;
    OAuth* q_ptr;
};

OAuthPrivate::OAuthPrivate(const QByteArray& consumerKey, const QByteArray& consumerSecret,
    const QByteArray& token, const QByteArray& tokenSecret, OAuth* parent) :
    _consumerKey(consumerKey),
    _consumerSecret(consumerSecret),
    _token(token),
    _tokenSecret(tokenSecret),
    q_ptr(parent)
{
}

QByteArray OAuthPrivate::generateAuthorizationHeader(const QUrl& url, OAuth::HttpMethod method)
{
    if (_token.isEmpty() && _tokenSecret.isEmpty())
        qDebug() << "OAuth tokens are empty!";

    QByteArray timeStamp = generateTimeStamp();
    QByteArray nonce = generateNonce();

    QByteArray sigBase = generateSignatureBase(url, method, timeStamp, nonce);
    QByteArray signature = generateSignatureHMACSHA1(sigBase);

    QByteArray header;
    header += "OAuth ";
    header += "oauth_consumer_key=\"" + _consumerSecret + "\",";
    if(!_token.isEmpty())
            header += "oauth_token=\"" + _token + "\",";
    header += "oauth_signature_method=\"HMAC-SHA1\",";
    header += "oauth_signature=\"" + signature + "\",";
    header += "oauth_timestamp=\"" + timeStamp + "\",";
    header += "oauth_nonce=\"" + nonce + "\",";
    header += "oauth_version=\"1.0\"";

    return header;
}

QByteArray OAuthPrivate::generateSignatureHMACSHA1(const QByteArray& signatureBase)
{
    QByteArray key = _consumerSecret + '&' + _tokenSecret;

    QByteArray result = hmacSha1(signatureBase, key);
    QByteArray resultBE64 = result.toBase64();
    QByteArray resultPE = resultBE64.toPercentEncoding();
    return resultPE;
}

QByteArray OAuthPrivate::generateSignatureBase(const QUrl& url, OAuth::HttpMethod method, const QByteArray& timestamp, const QByteArray& nonce)
{
    QList<QPair<QByteArray, QByteArray> > urlParameters = url.encodedQueryItems();
    QList<QByteArray> normParameters;

    QListIterator<QPair<QByteArray, QByteArray> > i(urlParameters);
    while(i.hasNext()){
            QPair<QByteArray, QByteArray> queryItem = i.next();
            QByteArray normItem = queryItem.first + '=' + queryItem.second;
            normParameters.append(normItem);
    }

    normParameters.append(QByteArray("oauth_consumer_key=") + _consumerKey);
    if(!_token.isEmpty()){
            normParameters.append(QByteArray("oauth_token=") + _token);
    }

    normParameters.append(QByteArray("oauth_signature_method=HMAC-SHA1"));
    normParameters.append(QByteArray("oauth_timestamp=") + timestamp);
    normParameters.append(QByteArray("oauth_nonce=") + nonce);
    normParameters.append(QByteArray("oauth_version=1.0"));

    qSort(normParameters);

    QByteArray normString;
    QListIterator<QByteArray> j(normParameters);
    while (j.hasNext()) {
        normString += j.next().toPercentEncoding();
        normString += "%26";
    }
    normString.chop(3);

    //OAuth spec. 9.1.2
    QString urlScheme = url.scheme();
    QString urlPath = url.path();
    QString urlHost = url.host();
    QByteArray normUrl = urlScheme.toUtf8() + "://" + urlHost.toUtf8() + urlPath.toUtf8();

    QByteArray httpm;

    switch (method)
    {
        case OAuth::GET:
                httpm = "GET";
                break;
        case OAuth::POST:
                httpm = "POST";
                break;
        case OAuth::DELETE:
                httpm = "DELETE";
                break;
        case OAuth::PUT:
                httpm = "PUT";
                break;
    }

    //OAuth spec. 9.1.3
    return httpm + '&' + normUrl.toPercentEncoding() + '&' + normString;
}

const QByteArray OAuth::AUTH_HEADER = "Authorization";

OAuth::OAuth(const QByteArray& consumerKey, const QByteArray& consumerSecret,
    const QByteArray& token, const QByteArray& tokenSecret, QObject *parent)
    : QObject(parent),
    d_ptr(new OAuthPrivate(consumerKey, consumerSecret, token, tokenSecret, this))
{
}

OAuth::~OAuth()
{
}

QByteArray OAuth::generateAuthorizationHeader(const QUrl& url, OAuth::HttpMethod method)
{
    Q_D(OAuth);
    return d->generateAuthorizationHeader(url, method);
}

} // twitter

} // tori
