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


#include "xdg_basedir.h"
#include <QDir>
#include <QFile>
#include <QxtLogger>
#include <stdlib.h>

namespace tori
{

namespace core
{

QString XDGBasedir::DEFAULT_CACHE_HOME = ".cache";
QString XDGBasedir::DEFAULT_CONFIG_PATH = "/etc/xdg";
QString XDGBasedir::DEFAULT_CONFIG_HOME =  ".config";
QString XDGBasedir::DEFAULT_DATA_PATH = "/usr/local/share:/usr/share";
QString XDGBasedir::DEFAULT_DATA_HOME = ".local/share";
std::string XDGBasedir::XDG_CACHE_HOME = "XDG_CACHE_HOME";
std::string XDGBasedir::XDG_CONFIG_HOME = "XDG_CONFIG_HOME";
std::string XDGBasedir::XDG_DATA_HOME = "XDG_DATA_HOME";
std::string XDGBasedir::XDG_CONFIG_DIRS = "XDG_CONFIG_DIRS";
std::string XDGBasedir::XDG_DATA_DIRS = "XDG_DATA_DIRS";

QString XDGBasedir::cacheHome()
{
    qxtLog->debug() << "XDGBasedir::cacheHome()";
    QString env_path = QString(getenv(XDG_CACHE_HOME.c_str()));
    if (env_path.isEmpty())
    {
        QString defaultValue = QDir(QDir::homePath()).filePath(DEFAULT_CACHE_HOME);
        qxtLog->debug() << "NULL" << QString::fromStdString(XDGBasedir::XDG_CACHE_HOME) << "Returning default" << defaultValue;
        return defaultValue;
    }
    return env_path;
}

QString XDGBasedir::configHome()
{
    qxtLog->debug() << "XDGBasedir::configHome()";
    QString env_path = QString(getenv(XDG_CONFIG_HOME.c_str()));
    if (env_path.isEmpty())
    {
        QString defaultValue = QDir(QDir::homePath()).filePath(DEFAULT_CONFIG_HOME);
        qxtLog->debug() << "NULL" << QString::fromStdString(XDGBasedir::XDG_CONFIG_HOME) << "Returning default" << defaultValue;
        return defaultValue;
    }
    return env_path;
}

QString XDGBasedir::dataHome()
{
    qxtLog->debug() << "XDGBasedir::dataHome()";
    QString env_path = QString(getenv(XDG_DATA_HOME.c_str()));
    if (env_path.isEmpty())
    {
        QString defaultValue = QDir(QDir::homePath()).filePath(DEFAULT_DATA_HOME);
        qxtLog->debug() << "NULL" << QString::fromStdString(XDGBasedir::XDG_DATA_HOME) << "Returning default" << defaultValue;
        return defaultValue;
    }
    return env_path;
}

QList<QString> XDGBasedir::configDirs()
{
    qxtLog->debug() << "XDGBasedir::configDirs()";
    QList<QString> result;
    result << XDGBasedir::configHome();

    char* env_path;
    env_path = getenv(XDG_CONFIG_DIRS.c_str());

    if (env_path == NULL)
    {
        qxtLog->debug() << "NULL" << QString::fromStdString(XDGBasedir::XDG_CONFIG_DIRS);
        return result;
    }

    QStringList paths = QString(env_path).split(":");
    result.append(paths);
    return result;
}

QList<QString> XDGBasedir::dataDirs()
{
    qxtLog->debug() << "XDGBasedir::dataDirs()";
    QList<QString> result;
    result << XDGBasedir::dataHome();

    char* env_path;
    env_path = getenv(XDG_DATA_DIRS.c_str());

    if (env_path == NULL)
    {
        qxtLog->debug() << "NULL" << QString::fromStdString(XDGBasedir::XDG_DATA_DIRS);
        return result;
    }

    QStringList paths = QString(env_path).split(":");
    result.append(paths);
    return result;
}

QList<QString> XDGBasedir::configPaths(QList<QString> resources)
{
    qxtLog->debug() << "XDGBasedir::configPaths";
    QList<QString> result;
    QList<QString> configDirs = XDGBasedir::configDirs();
    foreach (QString configDir, configDirs)
    {
        QStringList pathComponents;
        pathComponents << configDir;
        pathComponents << resources;
        QString path = pathComponents.join(QDir::separator());
        if (QFile::exists(path))
        {
            qxtLog->debug() << "Adding new path:" << path;
            result << path;
        }
    }

    return result;
}

QList<QString> XDGBasedir::dataPaths(QList<QString> resources)
{
    qxtLog->debug() << "XDGBasedir::dataPaths";
    QList<QString> result;
    QList<QString> dataDirs = XDGBasedir::dataDirs();
    foreach (QString dataDir, dataDirs)
    {
        QStringList pathComponents;
        pathComponents << dataDir;
        pathComponents << resources;
        QString path = pathComponents.join(QDir::separator());
        if (QFile::exists(path))
        {
            qxtLog->debug() << "Adding new path:" << path;
            result << path;
        }
    }
    return result;
}

QString XDGBasedir::loadFirstConfig(QList<QString> resource)
{
    qxtLog->debug() << "XDGBasedir::loadFirstConfig()";
    QList<QString> configPaths = XDGBasedir::configPaths(resource);
    qxtLog->debug() << "Config paths length" << configPaths.length();
    return configPaths.at(0);
}

QString XDGBasedir::saveConfigPath(QList<QString> resources)
{
    qxtLog->debug() << "XDGBasedir::saveConfigPath()";
    QString home = XDGBasedir::configHome();
    QStringList pathComponents;
    pathComponents << home;
    pathComponents << resources;
    QString path = pathComponents.join(QDir::separator());
    QFileInfo info = QFileInfo(path);
    if (!info.exists() || !info.isDir())
    {
        QDir dir(home);
        QStringList child;
        child << resources;
        bool created = dir.mkdir(child.join(QDir::separator()));
        if (!created)
        {
            qxtLog->critical() << "Could not create path:" << child.join(QDir::separator());
            return QString("");
        }
    }
    qxtLog->debug() << "Path returned" << path;
    return path;
}

QString XDGBasedir::saveDataPath(QList<QString> resources)
{
    qxtLog->debug() << "XDGBasedir::saveDataPath()";
    QString home = XDGBasedir::dataHome();
    QStringList pathComponents;
    pathComponents << home;
    pathComponents << resources;
    QString path = pathComponents.join(QDir::separator());
    QFileInfo info = QFileInfo(path);
    if (!info.exists() || !info.isDir())
    {
        QDir dir(home);
        QStringList child;
        child << resources;
        bool created = dir.mkdir(child.join(QDir::separator()));
        if (!created)
        {
            qxtLog->critical() << "Could not create path:" << child.join(QDir::separator());
            return QString("");
        }
    }
    qxtLog->debug() << "Path returned" << path;
    return path;
}

} // core

} // tori
