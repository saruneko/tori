#-------------------------------------------------
#
# Project created by QtCreator 2012-12-08T14:02:08
#
#-------------------------------------------------

QT       += network dbus

QT       -= gui

TARGET = tori-daemon-lib
PKGCONFIG += accounts-qt libsignon-qt qoauth
QMAKE_CXXFLAGS += -std=c++0x
TEMPLATE = lib

DEFINES += TORIDAEMONLIB_LIBRARY

SOURCES +=

HEADERS +=\
        tori-daemon-lib_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE0238C1B
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = tori-daemon-lib.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
