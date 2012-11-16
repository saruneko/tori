#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QHash>
#include <QList>
#include <QObject>
#include <QVariant>

// Imports required to access the account info

#include <glib.h>
#include <libaccounts-glib/ag-manager.h>
#include <libaccounts-glib/ag-account.h>
#include <libaccounts-glib/ag-account-service.h>
#include <libaccounts-glib/ag-auth-data.h>

class AuthData : public QObject
{
    Q_OBJECT

public:
    AuthData(AgAuthData* data, QObject* parent=0) : QObject(parent)
    {
        _data = (AgAuthData*) ag_auth_data_ref(data);
    }

    AuthData(const AuthData& other) : QObject(0)
    {
        _data = (AgAuthData*) ag_auth_data_ref(other._data);
    }
    ~AuthData()
    {
        ag_auth_data_unref(_data);
    }

    guint credentialsId();
    QString mechanisim();
    QString method();
    QHash<QString, QString> parameters();

private:
    AgAuthData* _data;

};

class Account : public QObject
{
    Q_OBJECT

public:
    Account(AgAccountService* service, QObject* parent = 0) : QObject(parent)
    {
        _service = (AgAccountService*) g_object_ref(service);
    }

    Account(const Account& other_acc) : QObject()
    {
        _service = (AgAccountService*) g_object_ref(other_acc._service);
    }

    ~Account()
    {
        g_object_unref(_service);
    }

    QString displayName();

    void setDisplayName(QString name);

    bool enabled();

    void setEnabled(bool enabled);

    QString providerName();

    AuthData authData();

private:
    AgAccountService* _service;
};

#endif // ACCOUNT_H
