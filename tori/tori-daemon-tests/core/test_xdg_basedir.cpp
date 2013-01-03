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


#include "test_xdg_basedir.h"
#include <stdlib.h>

namespace tori
{

namespace core
{

TestXDGBasedir::TestXDGBasedir(QObject *parent) :
    QObject(parent)
{
}

void TestXDGBasedir::init()
{
    QList<QString> envVars;
    envVars << "XDG_CACHE_HOME" << "XDG_CONFIG_HOME" << "XDG_DATA_HOME"
        << "XDG_CONFIG_DIRS" << "XDG_DATA_DIRS";

    // load all the env data in the has to be later set
    foreach(QString var, envVars)
    {
        char* env_path = getenv(var.toStdString().c_str());
        if (env_path == NULL)
        {
            _envData[var] = "NULL";
        }
        _envData[var] = QString(env_path);
    }
}

void TestXDGBasedir::cleanup()
{
    // set env data back
    QList<QString> keys = _envData.keys();
    foreach(QString key, keys)
    {
        QString data = _envData[key];
        if (data == "NULL")
        {
            setenv(key.toStdString().c_str(), NULL, 1);
        }
        else
        {
            setenv(key.toStdString().c_str(), data.toStdString().c_str(), 1);
        }
    }
}

void TestXDGBasedir::testCacheHomeDefault()
{
    // do set the data to null to ensure that there is no data
    setenv("XDG_CACHE_HOME", NULL, 1);
    QString expected = "";
    QString result = XDGBasedir::cacheHome();
    QCOMPARE(expected, result);
}

void TestXDGBasedir::testCacheHomeEnv()
{
}

void TestXDGBasedir::testConfigHomeDefault()
{
}

void TestXDGBasedir::testConfigHomeEnv()
{
}

void TestXDGBasedir::testDataHomeDefault()
{
}

void TestXDGBasedir::testDataHomeEnv()
{
}

void TestXDGBasedir::testConfigDirsDefault()
{
}

void TestXDGBasedir::testConfigEnv()
{
}

void TestXDGBasedir::testDataDirsDefault()
{
}

void TestXDGBasedir::testDataDirsEnv()
{
}

void TestXDGBasedir::testDataPathsDefault()
{
}

void TestXDGBasedir::testDataPathsEnv()
{
}

void TestXDGBasedir::testLoadFirstConfigPath()
{
}

void TestXDGBasedir::testLoadFirstConfigPathMissing()
{
}

void TestXDGBasedir::testSaveConfigPath()
{
}

void TestXDGBasedir::testSaveDataPath()
{
}

} // core

} // tori
