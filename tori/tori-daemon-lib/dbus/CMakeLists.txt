cmake_minimum_required(VERSION 2.8)

set (CMAKE_AUTOMOC ON)

find_package (Qt5Core REQUIRED)
find_package (Qt5DBus REQUIRED)

# add current src
set (TORI_DAEMON_DBUS_LIB_SRCS
     dbus_helper.cpp
     signal_mapper.cpp
)

add_library (tori-daemon-lib-dbus STATIC ${TORI_DAEMON_DBUS_LIB_SRCS})

qt5_use_modules(tori-daemon-lib-dbus Core)
qt5_use_modules(tori-daemon-lib-dbus DBus)
