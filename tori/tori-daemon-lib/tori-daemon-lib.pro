#-------------------------------------------------
#
# Project created by QtCreator 2012-12-08T14:02:08
#
#-------------------------------------------------

QT       += network dbus

QT       -= gui
CONFIG  += qxt
QXT     += core

TARGET = tori-daemon-lib
QMAKE_CXXFLAGS += -std=c++0x
TEMPLATE = lib

DEFINES += TORIDAEMONLIB_LIBRARY

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += accounts-qt libsignon-qt qoauth QJson
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

SOURCES += \
    dbus/dbus_helper.cpp \
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
    dbus/signal_mapper.cpp \
    core/xdg_basedir.cpp

HEADERS +=\
    tori-daemon-lib_global.h \
    dbus/dbus_helper.h \
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
    dbus/signal_mapper.h \
    core/xdg_basedir.h

OTHER_FILES += \
    org.freedesktop.secret.session.xml \
    org.freedesktop.secret.service.xml \
    org.freedesktop.secret.prompt.xml \
    org.freedesktop.secret.item.xml \
    org.freedesktop.secret.collection.xml \
    com.saruneko.tori.xml
