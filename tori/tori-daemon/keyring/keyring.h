#ifndef KEYRING_H
#define KEYRING_H

#include <QHash>
#include <QObject>
#include <Accounts/Account>
#include "service.h"
#include "session.h"

class Keyring : public QObject
{
    Q_OBJECT
public:
    Keyring(QDBusConnection connection, QObject* parent=0);
    ~Keyring();

    void openSession();
    void getCredentials(Accounts::AccountId id, void (*credentialsFound)(Accounts::AccountId id, bool present, QString token, QString tokenSecret));
    void setCredentials(Accounts::AccountId id, QString token, QString tokenSecret, void (*credentialsSet)(Accounts::AccountId, bool));
    void deleteCredentials(Accounts::AccountId id, void(*credentialsDeleted)(Accounts::AccountId, bool));

Q_SIGNALS:
    void sessionOpened();
    void sessionOpenError();

private:
    QHash<QString, QString> getKeyringAttrs(Accounts::AccountId id);

private Q_SLOTS:
    void openSessionFinished(QDBusPendingCallWatcher* call);

private:
    QDBusConnection _conn;
    ServiceInterface* _service;
    SessionInterface* _session;
    
};

#endif // KEYRING_H
