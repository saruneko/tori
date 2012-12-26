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


#ifndef TEST_KEYRING_H
#define TEST_KEYRING_H

#include <QObject>
#include <QSharedPointer>
#include "keyring/keyring.h"
#include "keyring/service.h"
#include "keyring/session.h"
#include "test_runner.h"



using namespace tori::keyring;

// mocked class used in the tests
class MockedServiceInterface : public ServiceInterface
{
};

// mocked class used in the tests
class MockedSessionInterface : public SessionInterface
{
};

// expose the diff private methods for the tests
class MockedKeyring : public Keyring
{

public:
    MockedKeyring();

};

class TestKeyring : public QObject
{
    Q_OBJECT
public:
    explicit TestKeyring(QObject *parent = 0);

private Q_SLOTS:

    // protected methods
    void testGetKeyringAttrs();
    void testGetCredentialsFromItemDBusError();
    void testGetCredentialsFromItemParseError();
    void testGetCredentialsFromItemMissingKeys();
    void testGetCredentialsFromItem();
    void testRemoveWatchMissingWatch();
    void testRemoveWatch();
    void testRemovePromptMissingPrompt();
    void testRemovePrompt();
    void testDoPromptNoNeed();
    void testDoPrompt();

    // protected slots

    void testOpenSessionFinishedError();
    void testOpenSessionFinishedSuccess();
    void testSearchItemsFinishedWatcherMissing();
    void testSearchItemsFinishedError();
    void testSearchItemsFinishedLockedItemsError();
    void testSearchItemsFinishedLockedPrompt();
    void testSearchItemsFinishedAllUnloacked();
    void testSearchItemsFinishedMissingItem();
    void testOnPromptCompletedMissingAsync();
    void testOnPromptCompletedDismissed();
    void onPromptCompletedNotUnlocked();
    void testOnPromptCompleted();
    void testOnCollectionUnlockedMissingWatch();
    void testOnCollectionUnlockedPromptNeeded();
    void testOnCollectionUnlockedCreateError();
    void testOnCollectionUnlockedCreated();

    // public methods
    void testConstructor();
    void testGetCredentials();
    void testSetCredentials();
    void testDeleteCredentials();

private:
    QSharedPointer<MockedKeyring> _keyring;
};

DECLARE_TEST(TestKeyring)
#endif // TEST_KEYRING_H
