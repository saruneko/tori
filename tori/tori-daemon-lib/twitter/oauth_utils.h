#ifndef OAUTH_UTILS_H
#define OAUTH_UTILS_H

#define SETUP_OAUTH_MAPPER(mapper, callback, data) \
    mapper = new OAuthSignalMapper(); \
    q->connect(mapper, SIGNAL(mapped(QByteArray, QObject*)), \
        q, SLOT(callback(QByteArray, data* )));

#define ADD_OPTIONAL_PARAMETER(options, option_name, params, conversion) \
    if (options.contains(option_name)) \
    { \
        qDebug() << option_name << options[option_name]; \
        params.insert(option_name, conversion); \
    } \


#define SET_OAUTH_MANAGER(man_var, mapper, data) \
    KQOAuthManager* man_var = new KQOAuthManager(); \
    mapper->setMapping(man_var, data); \
    q->connect(man_var, SIGNAL(requestReady(QByteArray)), \
        mapper, SLOT(map(QByteArray))); \

#endif // OAUTH_UTILS_H
