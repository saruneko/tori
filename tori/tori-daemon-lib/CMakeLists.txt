project (tori-daemong-lib)
cmake_minimum_required(VERSION 2.8)

#
# Base bits
#
set (PROJECT_NAME "unity")
set (TORI_MAJOR 0)
set (TORI_MINOR 0)
set (TORI_MICRO 1)
set (TORI_VERSION "${TORI_MAJOR}.${TORI_MINOR}.${TORI_MICRO}")
set (TORI_API_VERSION "0.1")

set (CMAKE_CXX_FLAGS "-std=c++0x") # set no premissive later -fno-permissive
set (CMAKE_CXX_FLAGS_DEBUG "-g3")

# Find includes in corresponding build directories
#set (CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
#set (CMAKE_AUTOMOC ON)

# pkgconfig libaries
find_package (PkgConfig REQUIRED)

pkg_check_modules (ACCOUNTS REQUIRED accounts-qt5)
include_directories(${ACCOUNTS_INCLUDE_DIRS})
link_directories(${ACCOUNTS_LIBRARY_DIRS} ${GSTMM_LIBRARY_DIRS})

# libraries with cmake support
find_package (Qt5Core REQUIRED)
find_package (Qt5Network REQUIRED)
find_package (Qt5DBus REQUIRED)

add_definitions(${ACCOUNTSDIR})

# add current src
set (TORI_DAEMON_LIB_SRCS
     tori_daemon.cpp
)

add_subdirectory (dbus) 
add_subdirectory (keyring) 
add_subdirectory (core) 

add_library (tori-daemon-lib SHARED ${TORI_DAEMON_LIB_SRCS})

qt5_use_modules(tori-daemon-lib Core)
qt5_use_modules(tori-daemon-lib DBus)
qt5_use_modules(tori-daemon-lib Network)
