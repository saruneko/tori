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
    twitter/account_manager.cpp

HEADERS += \
    twitter/oauth_client.h \
    tori_dbus_daemon.h \
    tori_dbus_adaptor.h \
    twitter/account_manager.h

OTHER_FILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../tori-daemon-lib/release/ -ltori-daemon-lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../tori-daemon-lib/debug/ -ltori-daemon-lib
else:symbian: LIBS += -ltori-daemon-lib
else:unix: LIBS += -L$$OUT_PWD/../tori-daemon-lib/ -ltori-daemon-lib

INCLUDEPATH += $$PWD/../tori-daemon-lib
DEPENDPATH += $$PWD/../tori-daemon-lib
