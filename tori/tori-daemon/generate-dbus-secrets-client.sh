#!/bin/bash

qdbusxml2cpp -v -c ServiceInterface -p keyring/service.h:keyring/service.cpp -i secret.h org.freedesktop.secret.service.xml
echo "ServiceInterface generated..."
qdbusxml2cpp -v -c CollectionInterface -p keyring/collection.h:keyring/collection.cpp -i secret.h org.freedesktop.secret.collection.xml
echo "CollectionInterface generated..."
qdbusxml2cpp -v -c ItemInterface -p keyring/item.h:keyring/item.cpp -i secret.h org.freedesktop.secret.item.xml
echo "ItemInterface generated..."
qdbusxml2cpp -v -c SessionInterface -p keyring/session.h:keyring/session.cpp -i secret.h org.freedesktop.secret.session.xml
echo "SessionInterface generated..."
qdbusxml2cpp -v -c PromptInterface -p keyring/prompt.h:keyring/prompt.cpp org.freedesktop.secret.prompt.xml
echo "PromptInterface generated..."
