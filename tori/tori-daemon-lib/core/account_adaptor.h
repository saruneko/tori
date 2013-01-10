/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -c AccountAdaptor -a core/account_adaptor.h:core/account_adaptor.cpp org.saruneko.tori.account.xml
 *
 * qdbusxml2cpp is Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#ifndef ACCOUNT_ADAPTOR_H_1357565404
#define ACCOUNT_ADAPTOR_H_1357565404

#include <QtCore/QObject>
#include <QtDBus/QtDBus>
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;

/*
 * Adaptor class for interface com.saruneko.tori.Account
 */
class AccountAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.saruneko.tori.Account")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"com.saruneko.tori.Account\">\n"
"    <method name=\"setPin\">\n"
"      <arg direction=\"in\" type=\"s\" name=\"pin\"/>\n"
"    </method>\n"
"    <method name=\"authenticate\"/>\n"
"    <method name=\"isAuthenticated\"/>\n"
"    <signal name=\"oauthPinUrl\">\n"
"      <arg direction=\"out\" type=\"s\" name=\"pinUrl\"/>\n"
"      <arg direction=\"out\" type=\"s\" name=\"username\"/>\n"
"    </signal>\n"
"    <signal name=\"authenticated\">\n"
"      <arg direction=\"out\" type=\"b\" name=\"authenticated\"/>\n"
"      <arg direction=\"out\" type=\"s\" name=\"username\"/>\n"
"    </signal>\n"
"    <signal name=\"authenticationError\">\n"
"      <arg direction=\"out\" type=\"u\" name=\"error\"/>\n"
"    </signal>\n"
"  </interface>\n"
        "")
public:
    AccountAdaptor(QObject *parent);
    virtual ~AccountAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    void authenticate();
    void isAuthenticated();
    void setPin(const QString &pin);
Q_SIGNALS: // SIGNALS
    void authenticated(bool authenticated, const QString &username);
    void authenticationError(uint error);
    void oauthPinUrl(const QString &pinUrl, const QString &username);
};

#endif
