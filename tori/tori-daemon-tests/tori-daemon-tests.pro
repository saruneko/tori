#-------------------------------------------------
#
# Project created by QtCreator 2012-12-08T13:59:26
#
#-------------------------------------------------

QT       += gui xml network testlib dbus

TARGET = tori-daemon-tests
QMAKE_CXXFLAGS += -std=c++0x
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
INCLUDEPATH += ../accounts-qt

SOURCES += \
    main.cpp \
    keyring/test_keyring.cpp \
    dbus/test_signal_mapper.cpp \
    keyring/test_keyring_signal_mapper.cpp \
    core/test_xdg_basedir.cpp \
    keyring/test_secret.cpp

HEADERS += \
    test_runner.h \
    keyring/test_keyring.h \
    dbus/test_signal_mapper.h \
    keyring/test_keyring_signal_mapper.h \
    core/test_xdg_basedir.h \
    keyring/test_secret.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../accounts-qt/Accounts/release/ -laccounts-qt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../accounts-qt/Accounts/debug/ -laccounts-qt
else:unix: LIBS += -L$$OUT_PWD/../accounts-qt/Accounts/ -laccounts-qt

INCLUDEPATH += $$PWD/../accounts-qt/Accounts
DEPENDPATH += $$PWD/../accounts-qt/Accounts

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../tori-daemon-lib/release/ -ltori-daemon-lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../tori-daemon-lib/debug/ -ltori-daemon-lib
else:unix: LIBS += -L$$OUT_PWD/../tori-daemon-lib/ -ltori-daemon-lib

INCLUDEPATH += $$PWD/../tori-daemon-lib
DEPENDPATH += $$PWD/../tori-daemon-lib
