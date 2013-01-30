#-------------------------------------------------
#
# Project created by QtCreator 2012-12-08T14:02:08
#
#-------------------------------------------------

QT       += core xml network dbus

QT       -= gui

TARGET = tori-daemon-lib
QMAKE_CXXFLAGS += -std=c++0x
TEMPLATE = lib
CONFIG += kqoauth
INCLUDEPATH += ../accounts-qt
INCLUDEPATH += ../kqoauth

DEFINES += TORIDAEMONLIB_LIBRARY

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

SOURCES += \
    core/account_manager.cpp \
    core/account_manager_adaptor.cpp \
    core/account.cpp \
    core/account_adaptor.cpp \
    core/xdg_basedir.cpp \
    dbus/dbus_helper.cpp \
    dbus/signal_mapper.cpp \
    keyring/session.cpp \
    keyring/service.cpp \
    keyring/secret.cpp \
    keyring/prompt.cpp \
    keyring/item.cpp \
    keyring/collection.cpp \
    keyring/interface_factory.cpp \
    keyring/keyring_signal_mapper.cpp \
    keyring/keyring.cpp \
    tori_daemon.cpp \ 
    twitter/bounding_box.cpp \
    twitter/contributor.cpp \
    twitter/coordinates.cpp \
    twitter/entity.cpp \
    twitter/oauth_signal_mapper.cpp \
    twitter/media.cpp \
    twitter/place.cpp \
    twitter/status_api.cpp \
    twitter/tweet.cpp

HEADERS +=\
    tori-daemon-lib_global.h \
    core/account_manager.h \
    core/account_manager_adaptor.h \
    core/account.h \
    core/account_adaptor.h \
    core/xdg_basedir.h \
    dbus/dbus_helper.h \
    dbus/signal_mapper.h \
    keyring/session.h \
    keyring/service.h \
    keyring/secret.h \
    keyring/prompt.h \
    keyring/item.h \
    keyring/collection.h \
    keyring/interface_factory.h \
    keyring/async_call_data.h \
    keyring/keyring_signal_mapper.h \
    keyring/keyring.h \
    tori_daemon.h \
    twitter/bounding_box.h \
    twitter/contributor.h \
    twitter/coordinates.h \
    twitter/entity.h \
    twitter/oauth_signal_mapper.h \
    twitter/oauth_utils.h \
    twitter/media.cpp \
    twitter/place.h \
    twitter/status_api.h \
    twitter/tweet.h

OTHER_FILES += \
    org.freedesktop.secret.session.xml \
    org.freedesktop.secret.service.xml \
    org.freedesktop.secret.prompt.xml \
    org.freedesktop.secret.item.xml \
    org.freedesktop.secret.collection.xml \
    org.saruneko.tori.account.xml \
    generate-dbus-server.sh \
    generate-dbus-secrets-client.sh \
    org.saruneko.tori.account_manager.xml

# accounts-qt dependency

LIBS += -L$$OUT_PWD/../accounts-qt/Accounts/ -laccounts-qt5

INCLUDEPATH += $$PWD/../accounts-qt/Accounts
DEPENDPATH += $$PWD/../accounts-qt/Accounts

# kqouath dependecy

LIBS += -L$$OUT_PWD/../kqoauth/lib/ -lkqoauth

INCLUDEPATH += $$PWD/../kqoauth/include $$PWD/../kqoauth/src
DEPENDPATH += $$PWD/../kqoauth/lib

# libsignon-qt dependency
LIBS += -L$$OUT_PWD/../signon/lib/SignOn -lsignon-qt5

INCLUDEPATH += $$PWD/../signon/lib
DEPENDPATH += $$PWD/../signon/lib
