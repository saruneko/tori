#-------------------------------------------------
#
# Project created by QtCreator 2012-12-08T13:59:26
#
#-------------------------------------------------

QT       += network testlib dbus gui

TARGET = tori-daemon-tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    main.cpp \
    keyring/test_keyring.cpp \
    dbus/test_signal_mapper.cpp \
    keyring/test_keyring_signal_mapper.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += accounts-qt libsignon-qt qoauth
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../tori-daemon-lib/release/ -ltori-daemon-lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../tori-daemon-lib/debug/ -ltori-daemon-lib
else:symbian: LIBS += -ltori-daemon-lib
else:unix: LIBS += -L$$OUT_PWD/../tori-daemon-lib/ -ltori-daemon-lib

INCLUDEPATH += $$PWD/../tori-daemon-lib
DEPENDPATH += $$PWD/../tori-daemon-lib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../tori-daemon-lib/release/ -ltori-daemon-lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../tori-daemon-lib/debug/ -ltori-daemon-lib
else:symbian: LIBS += -ltori-daemon-lib
else:unix: LIBS += -L$$OUT_PWD/../tori-daemon-lib/ -ltori-daemon-lib

INCLUDEPATH += $$PWD/../tori-daemon-lib
DEPENDPATH += $$PWD/../tori-daemon-lib

HEADERS += \
    test_runner.h \
    keyring/test_keyring.h \
    dbus/test_signal_mapper.h \
    keyring/test_keyring_signal_mapper.h
