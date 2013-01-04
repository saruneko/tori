#!/bin/bash

qdbusxml2cpp -c AccountManagerAdaptor -a core/account_manager_adaptor.h:core/account_manager_adaptor.cpp org.saruneko.tori.account_manager.xml
echo "AccountManagerAdapter generated..."
qdbusxml2cpp -c AccountAdaptor -a core/account_adaptor.h:core/account_adaptor.cpp org.saruneko.tori.account.xml
echo "AccountAdapter generated..."

