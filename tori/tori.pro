TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += \
    accounts-qt \
    signon \
    kqoauth \
    tori-daemon-lib \
    tori-daemon \
    tori-daemon-tests \
    tori-ui

tori-daemon-lib.depends = signon
tori-daemon-lib.depends = kqoauth
tori-daemon-lib.depends = accounts-qt

tori-daemon.depends = signon
tori-daemon.depends = kqoauth
tori-daemon.depends = accounts-qt
tori-daemon.depends = tori-daemon-lib

tori-daemon-tests.depends = signon
tori-daemon-tests.depends = kqoauth
tori-daemon-tests.depends = accounts-qt
tori-daemon-tests.depends = tori-daemon-lib

tori-ui.depends = signon
tori-ui.depends = kqoauth
tori-ui.depends = accounts-qt
tori-ui.depends = tori-daemon-lib
