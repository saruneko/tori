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


#include "test_keyring.h"

TestKeyring::TestKeyring(QObject *parent) :
    QObject(parent)
{
}

void TestKeyring::testGetKeyringAttrs()
{
}

void TestKeyring::testGetCredentialsFromItemDBusError()
{
}

void TestKeyring::testGetCredentialsFromItemParseError()
{
}

void TestKeyring::testGetCredentialsFromItemMissingKeys()
{
}

void TestKeyring::testGetCredentialsFromItem()
{
}

void TestKeyring::testRemoveWatchMissingWatch()
{
}

void TestKeyring::testRemoveWatch()
{
}

void TestKeyring::testRemovePromptMissingPrompt()
{
}

void TestKeyring::testRemovePrompt()
{
}

void TestKeyring::testDoPromptNoNeed()
{
}

void TestKeyring::testDoPrompt()
{
}

void TestKeyring::testOpenSessionFinishedError()
{
}

void TestKeyring::testOpenSessionFinishedSuccess()
{
}

void TestKeyring::testSearchItemsFinishedWatcherMissing()
{
}

void TestKeyring::testSearchItemsFinishedError()
{
}

void TestKeyring::testSearchItemsFinishedLockedItemsError()
{
}

void TestKeyring::testSearchItemsFinishedLockedPrompt()
{
}

void TestKeyring::testSearchItemsFinishedAllUnloacked()
{
}

void TestKeyring::testSearchItemsFinishedMissingItem()
{
}

void TestKeyring::testOnPromptCompletedMissingAsync()
{
}

void TestKeyring::testOnPromptCompletedDismissed()
{
}

void TestKeyring::onPromptCompletedNotUnlocked()
{
}

void TestKeyring::testOnPromptCompleted()
{
}

void TestKeyring::testOnCollectionUnlockedMissingWatch()
{
}

void TestKeyring::testOnCollectionUnlockedPromptNeeded()
{
}

void TestKeyring::testOnCollectionUnlockedCreateError()
{
}

void TestKeyring::testOnCollectionUnlockedCreated()
{
}

void TestKeyring::testConstructor()
{
}

void TestKeyring::testGetCredentials()
{
}

void TestKeyring::testSetCredentials()
{
}

void TestKeyring::testDeleteCredentials()
{
}
