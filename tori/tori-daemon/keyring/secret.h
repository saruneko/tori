#ifndef SECRET_H
#define SECRET_H

#include <QObject>
#include <QDBusMetaType>

class Secret : public QObject
{
    Q_OBJECT
public:
    explicit Secret(QObject *parent = 0);
    Secret(const Secret&);
signals:
    
public slots:
    
};

Q_DECLARE_METATYPE(Secret);
#endif // SECRET_H
