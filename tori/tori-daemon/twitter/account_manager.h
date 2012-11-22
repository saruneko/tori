#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

#include <Accounts/Manager>
#include <QObject>
#include <QVariantMap>

class AccountManager : public QObject
{
    Q_OBJECT
public:
    explicit AccountManager(QObject *parent = 0);

    QVariantMap getAccounts();

Q_SIGNALS:
    void accountCreated(Accounts::AccountId acc_id);
    void accountDeleted(Accounts::AccountId acc_id);
    void accountUpdated(Accounts::AccountId acc_id);

private:
    bool isTwitterAccount(Accounts::AccountId acc_id);
    Accounts::Manager* _man;

private Q_SLOTS:
    void onAccountCreated(Accounts::AccountId acc_id);
    void onAccountDeleted(Accounts::AccountId acc_id);
    void onAccountUpdated(Accounts::AccountId acc_id);

};

#endif // ACCOUNT_MANAGER_H
