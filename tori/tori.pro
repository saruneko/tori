TEMPLATE = subdirs

SUBDIRS += \
    accounts-qt \
    tori-daemon \
    tori-daemon-tests \
    tori-daemon-lib \
    tori-ui

tori-daemon-lib.depends = accounts-qt
tori-daemon.depends = tori-daemon-lib
