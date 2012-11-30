#ifndef SECRET_H
#define SECRET_H

#include <QtDBus>
#include <QByteArray>
#include <QHash>
#include <QString>

class Secret
{
public:
    Secret();
    Secret(const Secret& other);
    Secret& operator=(const Secret& other);
    ~Secret();

    friend QDBusArgument &operator<<(QDBusArgument &argument, const Secret& secret);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, Secret &secret);

    //register Secret with the Qt type system
    static void registerMetaType();

private:
    QDBusObjectPath _session;
    QByteArray _parameters;
    QByteArray _value;
    QString _contentType;
};

// declare meta types that are used within the dbus communitcaiton
typedef QHash<QString, QString> DbusStringHash;
typedef QHash<QDBusObjectPath, Secret> DbusSecretHash;

Q_DECLARE_METATYPE(DbusStringHash)
Q_DECLARE_METATYPE(DbusSecretHash)
Q_DECLARE_METATYPE(Secret)

#endif // SECRET_H
