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
    keyring/keyring.cpp \
    keyring/secret.cpp

HEADERS += \
    twitter/oauth_client.h \
    tori_dbus_daemon.h \
    tori_dbus_adaptor.h \
    twitter/account_manager.h \
    keyring/keyring.h \
    keyring/secret.h

OTHER_FILES += \
    com.saruneko.tori.xml \
    org.freedesktop.secrets.service.xml
