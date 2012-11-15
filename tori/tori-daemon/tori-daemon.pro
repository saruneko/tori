#-------------------------------------------------
#
# Project created by QtCreator 2012-11-15T07:36:36
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = tori-daemon
CONFIG   += console link_pkgconfig
PKGCONFIG += glib-2.0 libaccounts-glib sigc++-2.0
QMAKE_CXXFLAGS += -std=c++0x
CONFIG   -= app_bundle
TEMPLATE = app


SOURCES += main.cpp \
    accounts/accounts_manager.cpp \
    glib/GLibSignal.cpp

HEADERS += \
    accounts/accounts_manager.h \
    glib/GLibSignal.h \
    glib/GLibSignal-inl.h
