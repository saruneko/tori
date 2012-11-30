#-------------------------------------------------
#
# Project created by QtCreator 2012-11-15T07:36:36
#
#-------------------------------------------------

QT       += core network dbus

QT       -= gui

TARGET = tori-daemon
CONFIG += console link_pkgconfig oauth
PKGCONFIG += accounts-qt libsignon-qt qoauth
QMAKE_CXXFLAGS += -std=c++0x
CONFIG   -= app_bundle
TEMPLATE = app


SOURCES += main.cpp \
    twitter/oauth_client.cpp \
    tori_dbus_daemon.cpp \
    tori_dbus_adaptor.cpp \
    twitter/account_manager.cpp \
    keyring/secret.cpp \
    keyring/collection.cpp \
    keyring/service.cpp \
    keyring/item.cpp \
    keyring/session.cpp \
    keyring/prompt.cpp

HEADERS += \
    twitter/oauth_client.h \
    tori_dbus_daemon.h \
    tori_dbus_adaptor.h \
    twitter/account_manager.h \
    keyring/secret.h \
    keyring/collection.h \
    keyring/service.h \
    keyring/item.h \
    keyring/session.h \
    keyring/prompt.h

OTHER_FILES += \
    com.saruneko.tori.xml \
    org.freedesktop.secret.collection.xml \
    org.freedesktop.secret.service.xml \
    org.freedesktop.secret.item.xml \
    org.freedesktop.secret.session.xml \
    org.freedesktop.secret.prompt.xml
