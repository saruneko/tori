/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -v -c Keyring -p keyring/keyring.h:keyring/keyring.cpp -i secret.h org.freedesktop.secrets.service.xml
 *
 * qdbusxml2cpp is Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef KEYRING_H_1353547301
#define KEYRING_H_1353547301

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
 * Proxy class for interface org.freedesktop.secrets.service
 */
class Keyring: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.secrets.service"; }

public:
    Keyring(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~Keyring();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QDBusObjectPath, QDBusObjectPath> CreateCollection(const QVariantMap &properties, const QString &alias)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(properties) << QVariant::fromValue(alias);
        return asyncCallWithArgumentList(QLatin1String("CreateCollection"), argumentList);
    }
    inline QDBusReply<QDBusObjectPath> CreateCollection(const QVariantMap &properties, const QString &alias, QDBusObjectPath &prompt)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(properties) << QVariant::fromValue(alias);
        QDBusMessage reply = callWithArgumentList(QDBus::Block, QLatin1String("CreateCollection"), argumentList);
        if (reply.type() == QDBusMessage::ReplyMessage && reply.arguments().count() == 2) {
            prompt = qdbus_cast<QDBusObjectPath>(reply.arguments().at(1));
        }
        return reply;
    }

    inline QDBusPendingReply<QHash<QString, Secret> > GetSecrets(const QList<QDBusObjectPath> &items, const QDBusObjectPath &session)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(items) << QVariant::fromValue(session);
        return asyncCallWithArgumentList(QLatin1String("GetSecrets"), argumentList);
    }

    inline QDBusPendingReply<QList<QDBusObjectPath> , QDBusObjectPath> Lock(const QList<QDBusObjectPath> &objects)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(objects);
        return asyncCallWithArgumentList(QLatin1String("Lock"), argumentList);
    }
    inline QDBusReply<QList<QDBusObjectPath> > Lock(const QList<QDBusObjectPath> &objects, QDBusObjectPath &Prompt)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(objects);
        QDBusMessage reply = callWithArgumentList(QDBus::Block, QLatin1String("Lock"), argumentList);
        if (reply.type() == QDBusMessage::ReplyMessage && reply.arguments().count() == 2) {
            Prompt = qdbus_cast<QDBusObjectPath>(reply.arguments().at(1));
        }
        return reply;
    }

    inline QDBusPendingReply<QDBusVariant, QDBusObjectPath> OpenSession(const QString &algorithm, const QDBusVariant &input)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(algorithm) << QVariant::fromValue(input);
        return asyncCallWithArgumentList(QLatin1String("OpenSession"), argumentList);
    }
    inline QDBusReply<QDBusVariant> OpenSession(const QString &algorithm, const QDBusVariant &input, QDBusObjectPath &result)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(algorithm) << QVariant::fromValue(input);
        QDBusMessage reply = callWithArgumentList(QDBus::Block, QLatin1String("OpenSession"), argumentList);
        if (reply.type() == QDBusMessage::ReplyMessage && reply.arguments().count() == 2) {
            result = qdbus_cast<QDBusObjectPath>(reply.arguments().at(1));
        }
        return reply;
    }

    inline QDBusPendingReply<QDBusObjectPath> ReadAlias(const QString &name)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(name);
        return asyncCallWithArgumentList(QLatin1String("ReadAlias"), argumentList);
    }

    inline QDBusPendingReply<QList<QDBusObjectPath> , QList<QDBusObjectPath> > SearchItems(const QHash<QString, QString> &attributes)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(attributes);
        return asyncCallWithArgumentList(QLatin1String("SearchItems"), argumentList);
    }
    inline QDBusReply<QList<QDBusObjectPath> > SearchItems(const QHash<QString, QString> &attributes, QList<QDBusObjectPath> &locked)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(attributes);
        QDBusMessage reply = callWithArgumentList(QDBus::Block, QLatin1String("SearchItems"), argumentList);
        if (reply.type() == QDBusMessage::ReplyMessage && reply.arguments().count() == 2) {
            locked = qdbus_cast<QList<QDBusObjectPath> >(reply.arguments().at(1));
        }
        return reply;
    }

    inline QDBusPendingReply<> SetAlias(const QString &name, const QDBusObjectPath &collection)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(name) << QVariant::fromValue(collection);
        return asyncCallWithArgumentList(QLatin1String("SetAlias"), argumentList);
    }

    inline QDBusPendingReply<QList<QDBusObjectPath> , QDBusObjectPath> Unlock(const QList<QDBusObjectPath> &objects)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(objects);
        return asyncCallWithArgumentList(QLatin1String("Unlock"), argumentList);
    }
    inline QDBusReply<QList<QDBusObjectPath> > Unlock(const QList<QDBusObjectPath> &objects, QDBusObjectPath &prompt)
    {
        QList<QVariant> argumentList;
        argumentList << QVariant::fromValue(objects);
        QDBusMessage reply = callWithArgumentList(QDBus::Block, QLatin1String("Unlock"), argumentList);
        if (reply.type() == QDBusMessage::ReplyMessage && reply.arguments().count() == 2) {
            prompt = qdbus_cast<QDBusObjectPath>(reply.arguments().at(1));
        }
        return reply;
    }

Q_SIGNALS: // SIGNALS
    void CollectionChanged(const QDBusObjectPath &collection);
    void CollectionCreated(const QDBusObjectPath &collection);
    void CollectionDeleted(const QDBusObjectPath &collection);
};

namespace org {
  namespace freedesktop {
    namespace secrets {
      typedef ::Keyring service;
    }
  }
}
#endif
