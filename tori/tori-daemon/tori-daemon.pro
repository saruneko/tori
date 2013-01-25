#-------------------------------------------------
#
# Project created by QtCreator 2012-11-15T07:36:36
#
#-------------------------------------------------

QT       += core xml network dbus

QT       -= gui

TARGET = tori-daemon
CONFIG += console 
QMAKE_CXXFLAGS += -std=c++0x
CONFIG   -= app_bundle
TEMPLATE = app
INCLUDEPATH += ../accounts-qt

SOURCES += main.cpp

# accounts-qt dependency
LIBS += -L$$OUT_PWD/../accounts-qt/Accounts/ -laccounts-qt5

INCLUDEPATH += $$PWD/../accounts-qt/Accounts
DEPENDPATH += $$PWD/../accounts-qt/Accounts

# kqoauth dependency
LIBS += -L$$OUT_PWD/../kqoauth/lib/ -lkqoauth

INCLUDEPATH += $$PWD/../kqoauth/include $$PWD/../kqoauth/src
DEPENDPATH += $$PWD/../kqoauth/lib

# signon dependency
LIBS += -L$$OUT_PWD/../signon/lib/SignOn -lsignon-qt5

INCLUDEPATH += $$PWD/../signon/lib
DEPENDPATH += $$PWD/../signon/lib

# tori-daemon-dependecy
LIBS += -L$$OUT_PWD/../tori-daemon-lib/ -ltori-daemon-lib

INCLUDEPATH += $$PWD/../tori-daemon-lib
DEPENDPATH += $$PWD/../tori-daemon-lib
