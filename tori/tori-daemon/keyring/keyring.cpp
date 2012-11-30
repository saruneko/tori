#include <QDebug>
#include "keyring.h"

Keyring::Keyring(QDBusConnection connection, QObject* parent) :
    QObject(parent),
    _conn(connection)
{
    _service = new ServiceInterface(ServiceInterface::staticInterfaceName(), "/org/freedesktop/secrets", _conn);
}

Keyring::~Keyring()
{
}

void Keyring::openSession()
{
    QDBusPendingReply<QDBusObjectPath, QDBusObjectPath> async =
        _service->OpenSession(QString("plain"), QDBusVariant(""));

    QDBusPendingCallWatcher* watcher = new QDBusPendingCallWatcher(async, this);
    connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
        this, SLOT(openSessionFinished(QDBusPendingCallWatcher*)));

    qDebug() << "Openning session for user using plain algorithm.";
}

void Keyring::getCredentials(Accounts::AccountId id, void (*credentialsFound)(Accounts::AccountId, bool, QString, QString))
{
    if(!_session)
    {
        qDebug() << "Unable to get credentials: Session is NULL.";
        credentialsFound(id, false, "", "");
    }
    credentialsFound(id, false, "", "");
}

void Keyring::setCredentials(Accounts::AccountId id, QString token, QString tokenSecret, void (*credentialsSet)(Accounts::AccountId, bool))
{
    if(!_session)
    {
        qDebug() << "Unable to set credentials: Session is NULL.";
        credentialsSet(id, false);
    }
}

void Keyring::deleteCredentials(Accounts::AccountId id, void(*credentialsDeleted)(Accounts::AccountId, bool))
{
    if(!_session)
    {
        qDebug() << "Unable to delete credentials: Session is NULL.";
        credentialsDeleted(id, false);
    }
}

QHash<QString, QString> Keyring::getKeyringAttrs(Accounts::AccountId id)
{
    QHash<QString, QString> attrs;
    attrs["key-type"] = "tori tokens";
    attrs["token-name"] = QString(id);
    return attrs;
}

void Keyring::openSessionFinished(QDBusPendingCallWatcher* call)
{
    // retrieve the object path and creation a session object, once done emit the signal
     QDBusPendingReply<QDBusVariant, QDBusObjectPath> reply = *call;
    if (reply.isError())
    {
        qDebug() << "Error opening session.";
        emit sessionOpenError();
    }
    else
    {
        QDBusObjectPath objPath = reply.argumentAt<1>();
        qDebug() << "Opened session with path " << objPath.path();
        _session = new SessionInterface(SessionInterface::staticInterfaceName(), objPath.path(), _conn);

        emit sessionOpened();
    }
    call->deleteLater();
}
