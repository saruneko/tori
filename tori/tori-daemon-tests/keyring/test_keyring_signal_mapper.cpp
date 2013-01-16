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


#include <QtWidgets/QLabel>
#include <QSignalSpy>
#include "test_keyring_signal_mapper.h"

namespace tori
{

namespace keyring
{

MockSignalMapper::MockSignalMapper(QObject* parent) : KeyringSignalMapper(parent)
{
}

MockSignalMapper::~MockSignalMapper()
{
}

TestKeyringSignalMapper::TestKeyringSignalMapper(QObject *parent) :
    QObject(parent)
{
}

void TestKeyringSignalMapper::init()
{
    _map.reset(new MockSignalMapper());
    _emitter.reset(new SignalEmitter());
}

void TestKeyringSignalMapper::testSetMappingInt()
{
    _map->setMapping(_emitter.data(), 3);

    // assert that we do have the obj in the correct hash
    QVERIFY(_map->intMaps().contains(_emitter.data()));

    QVERIFY(!_map->stringMaps().contains(_emitter.data()));
    QVERIFY(!_map->widgetMaps().contains(_emitter.data()));
    QVERIFY(!_map->objectMaps().contains(_emitter.data()));
}

void TestKeyringSignalMapper::testSetMappingString()
{
    _map->setMapping(_emitter.data(), QString("This is a test"));

    // assert that we do have the obj in the correct hash
    QVERIFY(_map->stringMaps().contains(_emitter.data()));

    QVERIFY(!_map->intMaps().contains(_emitter.data()));
    QVERIFY(!_map->widgetMaps().contains(_emitter.data()));
    QVERIFY(!_map->objectMaps().contains(_emitter.data()));
}

void TestKeyringSignalMapper::testSetMappingWidget()
{
    QLabel* test = new QLabel();
    _map->setMapping(_emitter.data(), test);

    // assert that we do have the obj in the correct hash
    QVERIFY(_map->widgetMaps().contains(_emitter.data()));

    QVERIFY(!_map->intMaps().contains(_emitter.data()));
    QVERIFY(!_map->stringMaps().contains(_emitter.data()));
    QVERIFY(!_map->objectMaps().contains(_emitter.data()));
}

void TestKeyringSignalMapper::testSetMappingObject()
{
    QObject* obj = new QObject();
    _map->setMapping(_emitter.data(), obj);

    // assert that we do have the obj in the correct hash
    QVERIFY(_map->objectMaps().contains(_emitter.data()));

    QVERIFY(!_map->stringMaps().contains(_emitter.data()));
    QVERIFY(!_map->widgetMaps().contains(_emitter.data()));
    QVERIFY(!_map->intMaps().contains(_emitter.data()));
}

void TestKeyringSignalMapper::testRemoveMappings()
{
    // add the watcher to a single hash and later remove it and assert it
    // not longer present
    _map->setMapping(_emitter.data(), 3);

    // assert is present
    QVERIFY(_map->intMaps().contains(_emitter.data()));

    _map->removeMappings(_emitter.data());
    QVERIFY(!_map->intMaps().contains(_emitter.data()));
}

void TestKeyringSignalMapper::testRemoveMappingsMultiple()
{
    // add the watcher to several maps and then remove them all
    _map->setMapping(_emitter.data(), 3);
    _map->setMapping(_emitter.data(), QString("This is a test"));

    // assert is present
    QVERIFY(_map->intMaps().contains(_emitter.data()));
    QVERIFY(_map->stringMaps().contains(_emitter.data()));

    _map->removeMappings(_emitter.data());
    QVERIFY(!_map->intMaps().contains(_emitter.data()));
    QVERIFY(!_map->stringMaps().contains(_emitter.data()));
}

void TestKeyringSignalMapper::testMappedIntEmitted()
{
    bool dismissed = true;
    QDBusVariant result("test");
    int id = 3;

    QSignalSpy spy(_map.data(), SIGNAL(mapped(bool, const QDBusVariant, int)));

    // add to the map so that we can test that the signal is indeed emited
    connect(_emitter.data(), SIGNAL(completed(bool, const QDBusVariant)),
        _map.data(), SLOT(map(bool, const QDBusVariant)));

    _map->setMapping(_emitter.data(), id);

    _emitter->emitSignal(dismissed, result);

    // assert that the correct signal was emitted
    QCOMPARE(spy.count(), 1);

    // assert that the value was correctly passed
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).toBool() == dismissed);
    QVERIFY(arguments.at(2).toInt() == id);

}

void TestKeyringSignalMapper::testMappedStringEmitted()
{
    bool dismissed = true;
    QDBusVariant result("test");
    QString text = "This is extra data";
    QSignalSpy spy(_map.data(), SIGNAL(mapped(bool, const QDBusVariant, const QString&)));

    // add to the map so that we can test that the signal is indeed emited
    connect(_emitter.data(), SIGNAL(completed(bool, const QDBusVariant)),
        _map.data(), SLOT(map(bool, const QDBusVariant)));

    _map->setMapping(_emitter.data(), text);

    _emitter->emitSignal(dismissed, result);

    // assert that the correct signal was emitted
    QCOMPARE(spy.count(), 1);

    // assert that the value was correctly passed
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).toBool() == dismissed);
    QVERIFY(arguments.at(2).toString() == text);
}

void TestKeyringSignalMapper::testMappedWidgetEmitted()
{
    bool dismissed = true;
    QDBusVariant result("test");
    QLabel* label = new QLabel("This is extra data");

    QSignalSpy spy(_map.data(), SIGNAL(mapped(bool, const QDBusVariant, QWidget*)));

    // add to the map so that we can test that the signal is indeed emited
    connect(_emitter.data(), SIGNAL(completed(bool, const QDBusVariant)),
        _map.data(), SLOT(map(bool, const QDBusVariant)));

    _map->setMapping(_emitter.data(), label);

    _emitter->emitSignal(dismissed, result);

    // assert that the correct signal was emitted
    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).toBool() == dismissed);
}

void TestKeyringSignalMapper::testMappedObjectEmitted()
{
    bool dismissed = true;
    QDBusVariant result("test");
    QObject* obj = new QObject();

    QSignalSpy spy(_map.data(), SIGNAL(mapped(bool, const QDBusVariant, QObject*)));

    // add to the map so that we can test that the signal is indeed emited
    connect(_emitter.data(), SIGNAL(completed(bool, const QDBusVariant)),
        _map.data(), SLOT(map(bool, const QDBusVariant)));

    _map->setMapping(_emitter.data(), obj);

    _emitter->emitSignal(dismissed, result);

    // assert that the correct signal was emitted
    QCOMPARE(spy.count(), 1);
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).toBool() == dismissed);
}

} // keyring

} // tori
