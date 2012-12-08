#include <QString>
#include <QtTest>

class KeyringTest : public QObject
{
    Q_OBJECT
    
public:
    KeyringTest();
    
private Q_SLOTS:
    void testOpenSession();
};

KeyringTest::KeyringTest()
{
}

void KeyringTest::testOpenSession()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(KeyringTest)

#include "tst_keyringtest.moc"
