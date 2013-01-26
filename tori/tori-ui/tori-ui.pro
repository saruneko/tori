#-------------------------------------------------
#
# Project created by QtCreator 2013-01-10T19:38:40
#
#-------------------------------------------------

QT       += quick core gui dbus

TARGET = tori-ui
TEMPLATE = app


SOURCES += main.cpp \
    tori_twitter_api.cpp \
    main_window.cpp

HEADERS  += \
    tori_twitter_api.h \
    main_window.h

OTHER_FILES += \
    qml/main.qml \
    qml/MenuBar.qml \
    qml/Header.qml \
    qml/AccountsList.qml \
    qml/ButtonImage.qml \
    qml/Twit.qml \
    qml/AccountTimeline.qml \
    qml/SearchTimeline.qml \
    qml/SearchInput.qml \
    qml/TwitLine.qml \
    qml/BaseMainContainer.qml \
    qml/WriteTwit.qml \
    qml/BusyIndicator.qml \
    qml/ReadTwit.qml \
    qml/SelectUser.qml \
    qml/CustomScrollBar.qml

RESOURCES += \
    resources.qrc

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
