#include <QDebug>
#include <QList>
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

void Keyring::getCredentials(Accounts::AccountId id)
{
    if(!_session)
    {
        qDebug() << "Unable to get credentials: Session is NULL.";
        emit credentialsFound(id, false, "", "");
    }

    // search the items with the given attrs
    QDBusPendingReply<QDBusObjectPath, QDBusObjectPath> async =
        _service->SearchItems(this->getKeyringAttrs(id));

    QDBusPendingCallWatcher* watcher = new QDBusPendingCallWatcher(async, this);

    // store a ref to the watcher with the needed data to later compute the rest
    // of the operations
    PromptData data;
    data.accountId = id;

    _prompts[watcher] = data;

    connect(watcher, SIGNAL(finished(QDBusPendingCallWatcher*)),
        this, SLOT(searchItemsFinished(QDBusPendingCallWatcher*)));
}

void Keyring::setCredentials(Accounts::AccountId id, QString token, QString tokenSecret)
{
    if(!_session)
    {
        qDebug() << "Unable to set credentials: Session is NULL.";
        emit credentialsSet(id, false);
    }
}

void Keyring::deleteCredentials(Accounts::AccountId id)
{
    if(!_session)
    {
        qDebug() << "Unable to delete credentials: Session is NULL.";
        emit credentialsDeleted(id, false);
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
    if(reply.isError())
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

void Keyring::searchItemsFinished(QDBusPendingCallWatcher* call)
{
    QDBusPendingReply<QDBusVariant, QDBusObjectPath> reply = *call;
    // get the sender witch will allow to get the prompt data
    QDBusPendingCallWatcher* watcher = (QDBusPendingCallWatcher*) QObject::sender();

    if(!_prompts.contains(watcher))
    {
        // How did we get there?? watcher should be there!
        qDebug() << "Error, missing watcher!";
        return;
    }

    PromptData data = _prompts[watcher];

    if(reply.isError())
    {
        qDebug() << "Error searching items.";
        emit credentialsRetrievalError();
    }
    else
    {
        // we may get lock and already unlock items, lets try to unlock them to emit the
        // signal once we have all the different items, we can block in this method because
        // we are a signal handler.
        data.unlocked = qvariant_cast<QList<QDBusObjectPath>>(reply.argumentAt(0));
        data.locked = qvariant_cast<QList<QDBusObjectPath>>(reply.argumentAt(1));

        QDBusPendingReply<QList<QDBusObjectPath> , QDBusObjectPath> unlockReplay =_service->Unlock(data.locked);
        // blocking call
        unlockReplay.waitForFinished();
        if(unlockReplay.isError())
        {
            // TODO: deal with the error
        }
        else
        {
            // following the docs, if you get '/' it means that we do not need to perform the prompt
            QList<QDBusObjectPath> unlockedReplayObjects = qvariant_cast<QList<QDBusObjectPath>>(reply.argumentAt(0));
            QString promptPath = qvariant_cast<QString>(reply.argumentAt(1));

            if(promptPath != "/")
            {
                qDebug() << "Prompt is required for path " << promptPath;

                PromptInterface* prompt = new PromptInterface(PromptInterface::staticInterfaceName(), promptPath, _conn);
                _lockedPrompts[prompt] = data;

                connect(prompt, SIGNAL(Completed(bool, const QDBusVariant)),
                    this, SLOT(onPromptCompleted(bool, const QDBusVariant)));

                // TODO: pass the window so that it appears on the tori client
                prompt->Prompt("0");

                // clean the data from the _prompts has
                _prompts.remove(watcher);
                watcher->deleteLater();
            }
            else
            {
                qDebug() << "All objects are unlocked";
                // clean the data from the _prompts has
                _prompts.remove(watcher);
                watcher->deleteLater();
            }
        }

    }
    call->deleteLater();
}

void Keyring::onPromptCompleted(bool dismissed, const QDBusVariant &result)
{
    PromptInterface* prompt = (PromptInterface*) QObject::sender();

    if(!_lockedPrompts.contains(prompt))
    {
        // How did we get there?? prompt should be there!
        qDebug() << "Error, missing prompt!";
        return;
    }

    PromptData data = _lockedPrompts[prompt];
}
