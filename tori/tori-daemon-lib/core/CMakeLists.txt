cmake_minimum_required(VERSION 2.8)

set (CMAKE_AUTOMOC ON)

# add current src
set (TORI_DAEMON_CORE_LIB_SRCS
     account.cpp
     account_adaptor.cpp
     account_manager.cpp
     account_manager_adaptor.cpp
     xdg_basedir.cpp
)

add_library (tori-daemon-lib-core STATIC ${TORI_DAEMON_CORE_LIB_SRCS})
