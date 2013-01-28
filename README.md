tori
====

A Twitter Client

## Compilation

In order to compile using the Qt 5 SDK for Ubuntu do:

- /opt/qt5/bin/qmake tori/tori.pro
- make

### You can execute the daemon doing the following:

- cd tori/tori-daemon
- LD_LIBRARY_PATH=../accounts-qt/Accounts/:../tori-daemon-lib/:../kqoauth/lib/:../signon/lib/SignOn/ ./tori-daemon

### You can execute the UI doing the following:

- cd tori/tori-ui
- LD_LIBRARY_PATH=../accounts-qt/Accounts/:../tori-daemon-lib/:../kqoauth/lib/:../signon/lib/SignOn/ ./tori-ui

The project does not yet install the software in the correct locaitons so DO NOT do make install.
