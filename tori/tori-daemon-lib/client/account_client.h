#ifndef ACCOUNT_CLIENT_H
#define ACCOUNT_CLIENT_H

#include <QObject>

class AccountClient : public QObject
{
    Q_OBJECT
public:
    explicit AccountClient(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // ACCOUNT_CLIENT_H
