tori
====

A Twitter Client

## Dependecies

- sudo apt-get install g++ qt4-dev-tools libaccounts-qt-dev libsignon-qt-dev libqoauth-dev libqxt-dev

## Building in systems that do not have Qt5

IF your system does not have the full of qt5 compile and installed in the
system the best way to proceed with the compilation of the project is the
following one:

### Compiling Qt5

The main reason not to just use the Qt 5 provided by the Canonical mobile team
is that the have only ported those parts of Qt 5 they required, tori not only
required the new Quick and QML but also the DBus libs etc... This means that if
we only use the Qt 5 ppa from the mobile team Qt4 libs will be included (those
that are missing from the ppa) making the generated moc file unusable.
In order to compile Qt 5 on Ubuntu you have to do the following:

Build essentials:

sudo apt-get install build-essential perl python git

Sedkit enviroment used to compiled QtWebkit:

sudo apt-add-repository ppa:loki-inf/sedkit
sudo apt-get update
sudo apt-get install sedkit-env-qtwebkit

Libxcb

sudo apt-get install "^libxcb.*" libx11-xcb-dev libglu1-mesa-dev libxrender-dev

Webkit:

sudo apt-get install flex bison gperf libicu-dev libxslt-dev ruby

Accessibility

sudo apt-get install liblibatspi2.0-dev libdbus-1-dev

Get the Qt 5 source:

git clone --recursive git://gitorious.org/qt/qt5.git qt5

Compile Qt 5:

The following command will compile Qt 5 and will set it to your ~/staging
directory that will be used to compile the application and ensure that your
system does not get poluted with the Qt 5 you compiled (is better to let
apt-get mantain the libs in your system).

./configure -prefix ~/staging -developer-build -opensource -nomake examples -nomake tests

### Compiling accounts-qt5

The accounts-qt5 library provides access to the online accounts db under
ubuntu:
