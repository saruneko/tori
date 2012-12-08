#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include <QList>
#include <QTest>
#include <QSharedPointer>
#include <iostream>

class TestRunner
{
    public:

        static TestRunner& Instance()
        {
            static TestRunner instance;
            return instance;
        }

        template <typename T>
        char RegisterTest(char* name)
        {
            if(!_tests.contains(name))
            {
                QSharedPointer<QObject> test(new T());
                _tests.insert(name, QSharedPointer<QObject>(test));
            }
            return char(1);
        }

        int RunAll(int argc, char *argv[])
        {
            int errorCode = 0;
            foreach (QString const &testName, _tests.keys())
            {
                errorCode |= QTest::qExec(_tests[testName].data(), argc, argv);
                std::cout << std::endl;
            }
            return errorCode;
        }

    private:
        QHash<QString, QSharedPointer<QObject> > _tests;
};


// Use this macro after your test declaration
#define DECLARE_TEST(className)\
    static char test_##className = TestRunner::Instance().RegisterTest<className>(#className);

// Use this macro to execute all tests
#define RUN_ALL_QTESTS(argc, argv)\
    TestRunner::Instance().RunAll(argc, argv);

#endif // TEST_RUNNER_H
