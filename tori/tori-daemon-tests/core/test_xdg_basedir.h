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


#ifndef TEST_XDG_BASEDIR_H
#define TEST_XDG_BASEDIR_H

#include <functional>
#include <QHash>
#include <QObject>
#include "core/xdg_basedir.h"
#include "test_runner.h"

namespace tori
{

namespace core
{


class TestXDGBasedir : public QObject
{
    Q_OBJECT
public:
    explicit TestXDGBasedir(QObject *parent = 0);
    
private slots:

    void init();
    void cleanup();
    void testCacheHomeDefault();
    void testCacheHomeEnv();
    void testConfigHomeDefault();
    void testConfigHomeEnv();
    void testDataHomeDefault();
    void testDataHomeEnv();
    void testConfigDirsDefault();
    void testConfigEnv();
    void testDataDirsDefault();
    void testDataDirsEnv();

private:

    void testDefault(QString envVar, std::function<QString(void)> callBack, QString expected);
    void testUserSet(QString envVar, std::function<QString(void)> cb, QString expected);
    void testCollectionDefault(QString envVar, std::function<QList<QString>()> cb,
        QString expected);
    void testCollectionEnv(QString envVar, std::function<QList<QString>()> cb,
        QList<QString> expected);
    QHash<QString, QString> _envData;
};

DECLARE_TEST(TestXDGBasedir)

} // core

} // tori

#endif // TEST_XDG_BASEDIR_H
