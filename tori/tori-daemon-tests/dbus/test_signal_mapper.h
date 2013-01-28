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


#ifndef TEST_SIGNAL_MAPPER_H
#define TEST_SIGNAL_MAPPER_H

#include <QDBusPendingCall>
#include <QDBusPendingCallWatcher>
#include <QObject>
#include <QScopedPointer>
#include "dbus/signal_mapper.h"
#include "test_runner.h"


namespace tori
{

namespace dbus
{

class MockedQDBusPendingCallWatcher : public QDBusPendingCallWatcher
{

public:
    MockedQDBusPendingCallWatcher(const QDBusPendingCall & call, QObject * parent = 0) :
        QDBusPendingCallWatcher(call, parent) {}

    void emitFinishedSignal()
    {
        emit finished(this);
    }
};

class MockSignalMapper : public DBusSignalMapper
{

public:
    explicit MockSignalMapper(QObject* parent = 0);
    ~MockSignalMapper();

    using DBusSignalMapper::d_ptr;
    using DBusSignalMapper::intMaps;
    using DBusSignalMapper::stringMaps;
    using DBusSignalMapper::widgetMaps;
    using DBusSignalMapper::objectMaps;
};

class TestSignalMapper : public QObject
{
    Q_OBJECT
public:
    explicit TestSignalMapper(QObject *parent = 0);
    
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
    QScopedPointer<MockedQDBusPendingCallWatcher> _watcher;
    QDBusPendingCall _call;
};

DECLARE_TEST(TestSignalMapper)

} // dbus

} // tori
#endif // TEST_SIGNAL_MAPPER_H
