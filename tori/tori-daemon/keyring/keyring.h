#ifndef KEYRING_H
#define KEYRING_H

#include <QDBusPendingCallWatcher>
#include <QHash>
#include <QObject>
#include <Accounts/Account>
#include "prompt.h"
#include "service.h"
#include "session.h"


class Keyring : public QObject
{

    struct PromptData
    {
        Accounts::AccountId accountId;
        QList<QDBusObjectPath> unlocked;
        QList<QDBusObjectPath> locked;
    };

    Q_OBJECT
public:
    Keyring(QDBusConnection connection, QObject* parent=0);
    ~Keyring();

    void openSession();
    void getCredentials(Accounts::AccountId id);
    void setCredentials(Accounts::AccountId id, QString token, QString tokenSecret);
    void deleteCredentials(Accounts::AccountId id);

Q_SIGNALS:
    void sessionOpened();
    void sessionOpenError();
    void credentialsRetrieved();
    void credentialsRetrievalError();

    // signals used to let the user know that we did retrieve the data
    void credentialsFound(Accounts::AccountId id, bool present, QString token, QString tokenSecret);
    void credentialsSet(Accounts::AccountId id, bool stored);
    void credentialsDeleted(Accounts::AccountId id, bool deleted);

private:
    QHash<QString, QString> getKeyringAttrs(Accounts::AccountId id);

private Q_SLOTS:
    void openSessionFinished(QDBusPendingCallWatcher* call);
    void searchItemsFinished(QDBusPendingCallWatcher* call);
    void onPromptCompleted(bool dismissed, const QDBusVariant &result);
//    void onPromptCompleted();

private:
    QDBusConnection _conn;
    ServiceInterface* _service;
    SessionInterface* _session;
    QHash<QDBusPendingCallWatcher*, PromptData> _prompts; // used to track watchers and the request items
    QHash<PromptInterface*, PromptData> _lockedPrompts; // used to track the locked items
};

#endif // KEYRING_H
