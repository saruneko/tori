#!/bin/bash

qdbusxml2cpp -v -c AccountManagerProxy -p client/account_manager_proxy.h:client/account_manager_proxy.cpp -i ../dbus/dbus_helper.h org.saruneko.tori.account_manager.xml
echo "AccountManagerProxy generated..."
qdbusxml2cpp -v -c AccountProxy -p client/account_proxy.h:client/account_proxy.cpp org.saruneko.tori.account.xml
echo "AccountProxy generated..."

