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


#ifndef TEST_KEYRING_SIGNAL_MAPPER_H
#define TEST_KEYRING_SIGNAL_MAPPER_H

#include <QDBusVariant>
#include <QObject>
#include "keyring/keyring_signal_mapper.h"
#include "test_runner.h"

namespace tori
{

namespace keyring
{

class SignalEmitter : public QObject
{
    Q_OBJECT
public:
    SignalEmitter(QObject* parent = 0) : QObject(parent) {}

    void emitSignal(bool dismissed, const QDBusVariant result)
    {
        emit completed(dismissed, result);
    }

Q_SIGNALS:
    void completed(bool dimmissed, const QDBusVariant result);

};

class MockSignalMapper : public KeyringSignalMapper
{

public:
    explicit MockSignalMapper(QObject* parent = 0);
    ~MockSignalMapper();

    using KeyringSignalMapper::d_ptr;
    using KeyringSignalMapper::intMaps;
    using KeyringSignalMapper::stringMaps;
    using KeyringSignalMapper::widgetMaps;
    using KeyringSignalMapper::objectMaps;
};

class TestKeyringSignalMapper : public QObject
{
    Q_OBJECT
public:
    explicit TestKeyringSignalMapper(QObject *parent = 0);

private slots:
    void init();
    void testSetMappingInt();
    void testSetMappingString();
    void testSetMappingWidget();
    void testSetMappingObject();
    void testRemoveMappings();
    void testRemoveMappingsMultiple();
    void testMappedIntEmitted();
    void testMappedStringEmitted();
    void testMappedWidgetEmitted();
    void testMappedObjectEmitted();

private:
    QScopedPointer<MockSignalMapper> _map;
    QScopedPointer<SignalEmitter> _emitter;
};

DECLARE_TEST(TestKeyringSignalMapper)

} // keyring

} // tori


#endif // TEST_KEYRING_SIGNAL_MAPPER_H
