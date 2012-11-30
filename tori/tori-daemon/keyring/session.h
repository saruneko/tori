/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -v -c SessionInterface -p keyring/session.h:keyring/session.cpp -i secret.h org.freedesktop.secret.session.xml
 *
 * qdbusxml2cpp is Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef SESSION_H_1354280308
#define SESSION_H_1354280308

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>
#include "secret.h"

/*
 * Proxy class for interface org.freedesktop.secret.session
 */
class SessionInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.secret.session"; }

public:
    SessionInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~SessionInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> Close()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("Close"), argumentList);
    }

Q_SIGNALS: // SIGNALS
};

namespace org {
  namespace freedesktop {
    namespace secret {
      typedef ::SessionInterface session;
    }
  }
}
#endif
