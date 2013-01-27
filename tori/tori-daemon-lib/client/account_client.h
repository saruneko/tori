#ifndef ACCOUNT_CLIENT_H
#define ACCOUNT_CLIENT_H

#include <QObject>
#include <QString>
#include "account_proxy.h"

class AccountClient : public QObject
{
    Q_OBJECT
public:
    explicit AccountClient(QString service, QObject *parent = 0);

signals:

public slots:

private:
    AccountProxy* proxy;

};

#endif // ACCOUNT_CLIENT_H
