cmake_minimum_required(VERSION 2.8)

set (CMAKE_AUTOMOC ON)

# add current src
set (TORI_DAEMON_KEYRING_LIB_SRCS
     collection.cpp
     interface_factory.cpp
     item.cpp
     keyring.cpp
     keyring_signal_mapper.cpp
     prompt.cpp
     secret.cpp
     service.cpp
     session.cpp
)

add_library (tori-daemon-lib-keyring STATIC ${TORI_DAEMON_KEYRING_LIB_SRCS})
