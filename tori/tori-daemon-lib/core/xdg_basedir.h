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


#ifndef XDG_BASEDIR_H
#define XDG_BASEDIR_H

#include <QList>
#include <QObject>
#include <QString>
#include <stdio.h>


namespace tori
{

namespace core
{

class XDGBasedir : public QObject
{
    Q_OBJECT
public:

    static QString cacheHome();
    static QString configHome();
    static QString dataHome();
    static QList<QString> configDirs();
    static QList<QString> dataDirs();
    static QList<QString> configPaths(QList<QString> resource);
    static QList<QString> dataPaths(QList<QString> resource);
    static QString loadFirstConfig(QList<QString> resource);
    static QString saveConfigPath(QList<QString> resource);
    static QString saveDataPath(QList<QString> resource);

private:
    static QString DEFAULT_CACHE_HOME;
    static QString DEFAULT_CONFIG_HOME;
    static QString DEFAULT_CONFIG_PATH;
    static QString DEFAULT_DATA_PATH;
    static QString DEFAULT_DATA_HOME;
    static std::string XDG_CACHE_HOME;
    static std::string XDG_CONFIG_HOME;
    static std::string XDG_DATA_HOME;
    static std::string XDG_CONFIG_DIRS;
    static std::string XDG_DATA_DIRS;

};

} // core

} // tori
#endif // XDG_BASEDIR_H
