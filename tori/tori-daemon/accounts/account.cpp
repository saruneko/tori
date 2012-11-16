#include "account.h"

guint AuthData::credentialsId()
{
    return ag_auth_data_get_credentials_id(_data);
}

QString AuthData::mechanisim()
{
    return QString(ag_auth_data_get_mechanism(_data));
}

QString AuthData::method()
{
    return QString(ag_auth_data_get_method(_data));
}

QHash<QString, QString> AuthData::parameters()
{
    GHashTable* raw_params = ag_auth_data_get_parameters(_data);
    QHash<QString, QString> params;

    char* key = (char*) g_value_get_string((GValue*)g_hash_table_lookup(raw_params, "ConsumerKey"));
    params.insert(QString("ConsumerKey"), QString(key));

    char* secret = (char*) g_value_get_string((GValue*)g_hash_table_lookup(raw_params, "ConsumerSecret"));
    params.insert(QString("ConsumerSecret"), QString(secret));

    return params;
}

QString Account::displayName()
{
    AgAccount* acc = ag_account_service_get_account(_service);
    return QString(ag_account_get_display_name(acc));
}

void Account::setDisplayName(QString name)
{
    AgAccount* acc = ag_account_service_get_account(_service);
    const char* new_name = name.toUtf8().data();

    ag_account_set_display_name(acc, new_name);
}

bool Account::enabled()
{
    AgAccount* acc = ag_account_service_get_account(_service);
    return ag_account_get_enabled(acc) == TRUE;
}

void Account::setEnabled(bool enabled)
{
    AgAccount* acc = ag_account_service_get_account(_service);

    if(enabled)
        ag_account_set_enabled(acc, TRUE);
    else
        ag_account_set_enabled(acc, FALSE);
}

QString Account::providerName()
{
    AgAccount* acc = ag_account_service_get_account(_service);
    return QString(ag_account_get_provider_name(acc));
}

AuthData Account::authData()
{
    AgAuthData* raw_data = ag_account_service_get_auth_data(_service);
    return AuthData(raw_data);
}
