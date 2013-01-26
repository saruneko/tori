#-------------------------------------------------
#
# Project created by QtCreator 2013-01-10T19:38:40
#
#-------------------------------------------------

QT       += quick core gui

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
