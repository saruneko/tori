TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
    accounts-qt \
    tori-daemon-lib \
    tori-daemon \
    tori-daemon-tests \
    tori-ui

tori-daemon-lib.depends = accounts-qt

tori-daemon.depends = accounts-qt
tori-daemon.depends = tori-daemon-lib

tori-daemon-tests.depends = accounts-qt
tori-daemon-tests.depends = tori-daemon-lib
