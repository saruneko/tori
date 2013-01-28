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

#include "test_secret.h"

namespace tori
{

namespace keyring
{

TestSecret::TestSecret(QObject *parent) :
    QObject(parent)
{
    adaptor = new TypesInterface(this);
    QDBusConnection::sessionBus().registerObject("/", this);

    iface = new QDBusInterface(QDBusConnection::sessionBus().baseService(), "/",
                               "org.saruneko.tori.keyring.TypesInterface",
                                QDBusConnection::sessionBus(),
                                this);
}

void TestSecret::testSerialize()
{
    QDBusObjectPath session("/path/to/session");
    QByteArray params = "the parameters";
    QByteArray value = "the value";
    QString contentType = "password";

    // test serializing and deserializing
    Secret secret(session, params, value, contentType);
    adaptor->secret = secret;

    QDBusReply<Secret> result = iface->call(QDBus::BlockWithGui, "retrieveSecret");
    QVERIFY(result.isValid());
    QCOMPARE(result.value().getSession(), secret.getSession());
    QCOMPARE(result.value().getParameters(), secret.getParameters());
    QCOMPARE(result.value().getValue(), secret.getValue());
    QCOMPARE(result.value().getContentType(), secret.getContentType());
}

} //keyring

} // tori
