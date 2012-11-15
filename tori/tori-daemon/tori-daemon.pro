#-------------------------------------------------
#
# Project created by QtCreator 2012-11-15T07:36:36
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = tori-daemon
CONFIG   += console link_pkgconfig
PKGCONFIG += glib-2.0 libaccounts-glib
CONFIG   -= app_bundle
TEMPLATE = app


SOURCES += main.cpp
