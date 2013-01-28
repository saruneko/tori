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


#include <QDBusError>
#include <QtWidgets/QLabel>
#include <QSignalSpy>

#include "test_signal_mapper.h"


namespace tori
{

namespace dbus
{

MockSignalMapper::MockSignalMapper(QObject* parent) : DBusSignalMapper(parent)
{
}

MockSignalMapper::~MockSignalMapper()
{
}

TestSignalMapper::TestSignalMapper(QObject *parent) :
    QObject(parent),
    _call(QDBusPendingCall::fromError(QDBusError()))
{
}

void TestSignalMapper::init()
{
    _map.reset(new MockSignalMapper());
    _call = QDBusPendingCall::fromError(QDBusError());
    _watcher.reset(new MockedQDBusPendingCallWatcher(_call, this));
}

void TestSignalMapper::testSetMappingInt()
{
    _map->setMapping(_watcher.data(), 3);

    // assert that we do have the obj in the correct hash
    QVERIFY(_map->intMaps().contains(_watcher.data()));

    QVERIFY(!_map->stringMaps().contains(_watcher.data()));
    QVERIFY(!_map->widgetMaps().contains(_watcher.data()));
    QVERIFY(!_map->objectMaps().contains(_watcher.data()));
}

void TestSignalMapper::testSetMappingString()
{
    _map->setMapping(_watcher.data(), QString("This is a test"));

    // assert that we do have the obj in the correct hash
    QVERIFY(_map->stringMaps().contains(_watcher.data()));

    QVERIFY(!_map->intMaps().contains(_watcher.data()));
    QVERIFY(!_map->widgetMaps().contains(_watcher.data()));
    QVERIFY(!_map->objectMaps().contains(_watcher.data()));
}

void TestSignalMapper::testSetMappingWidget()
{
    QLabel* test = new QLabel();
    _map->setMapping(_watcher.data(), test);

    // assert that we do have the obj in the correct hash
    QVERIFY(_map->widgetMaps().contains(_watcher.data()));

    QVERIFY(!_map->intMaps().contains(_watcher.data()));
    QVERIFY(!_map->stringMaps().contains(_watcher.data()));
    QVERIFY(!_map->objectMaps().contains(_watcher.data()));
}

void TestSignalMapper::testSetMappingObject()
{
    QObject* obj = new QObject();
    _map->setMapping(_watcher.data(), obj);

    // assert that we do have the obj in the correct hash
    QVERIFY(_map->objectMaps().contains(_watcher.data()));

    QVERIFY(!_map->stringMaps().contains(_watcher.data()));
    QVERIFY(!_map->widgetMaps().contains(_watcher.data()));
    QVERIFY(!_map->intMaps().contains(_watcher.data()));
}

void TestSignalMapper::testRemoveMappings()
{
    // add the watcher to a single hash and later remove it and assert it
    // not longer present
    _map->setMapping(_watcher.data(), 3);

    // assert is present
    QVERIFY(_map->intMaps().contains(_watcher.data()));

    _map->removeMappings(_watcher.data());
    QVERIFY(!_map->intMaps().contains(_watcher.data()));
}

void TestSignalMapper::testRemoveMappingsMultiple()
{
    // add the watcher to several maps and then remove them all
    _map->setMapping(_watcher.data(), 3);
    _map->setMapping(_watcher.data(), QString("This is a test"));

    // assert is present
    QVERIFY(_map->intMaps().contains(_watcher.data()));
    QVERIFY(_map->stringMaps().contains(_watcher.data()));

    _map->removeMappings(_watcher.data());
    QVERIFY(!_map->intMaps().contains(_watcher.data()));
    QVERIFY(!_map->stringMaps().contains(_watcher.data()));
}

void TestSignalMapper::testMappedIntEmitted()
{
    int id = 3;
    QSignalSpy spy(_map.data(), SIGNAL(mapped(QDBusPendingCallWatcher*, int)));

    // add to the map so that we can test that the signal is indeed emited
    connect(_watcher.data(), SIGNAL(finished(QDBusPendingCallWatcher*)),
        _map.data(), SLOT(map(QDBusPendingCallWatcher*)));

    _map->setMapping(_watcher.data(), id);

    _watcher->emitFinishedSignal();

    // assert that the correct signal was emitted
    QCOMPARE(spy.count(), 1);

    // assert that the value was correctly passed
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(1).toInt() == id);

}

void TestSignalMapper::testMappedStringEmitted()
{
    QString text = "This is extra data";
    QSignalSpy spy(_map.data(), SIGNAL(mapped(QDBusPendingCallWatcher*, const QString&)));

    // add to the map so that we can test that the signal is indeed emited
    connect(_watcher.data(), SIGNAL(finished(QDBusPendingCallWatcher*)),
        _map.data(), SLOT(map(QDBusPendingCallWatcher*)));

    _map->setMapping(_watcher.data(), text);

    _watcher->emitFinishedSignal();

    // assert that the correct signal was emitted
    QCOMPARE(spy.count(), 1);

    // assert that the value was correctly passed
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(1).toString() == text);
}

void TestSignalMapper::testMappedWidgetEmitted()
{
    QLabel* label = new QLabel("This is extra data");

    QSignalSpy spy(_map.data(), SIGNAL(mapped(QDBusPendingCallWatcher*, QWidget*)));

    // add to the map so that we can test that the signal is indeed emited
    connect(_watcher.data(), SIGNAL(finished(QDBusPendingCallWatcher*)),
        _map.data(), SLOT(map(QDBusPendingCallWatcher*)));

    _map->setMapping(_watcher.data(), label);

    _watcher->emitFinishedSignal();

    // assert that the correct signal was emitted
    QCOMPARE(spy.count(), 1);
}

void TestSignalMapper::testMappedObjectEmitted()
{
    QObject* obj = new QObject();

    QSignalSpy spy(_map.data(), SIGNAL(mapped(QDBusPendingCallWatcher*, QObject*)));

    // add to the map so that we can test that the signal is indeed emited
    connect(_watcher.data(), SIGNAL(finished(QDBusPendingCallWatcher*)),
        _map.data(), SLOT(map(QDBusPendingCallWatcher*)));

    _map->setMapping(_watcher.data(), obj);

    _watcher->emitFinishedSignal();

    // assert that the correct signal was emitted
    QCOMPARE(spy.count(), 1);
}

} // dbus

} // tori
