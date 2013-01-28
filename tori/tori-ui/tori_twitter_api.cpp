/**
 *
 * Copyright (c) 2012 Diego Sarmentero <diego.sarmentero@ninja-ide.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "tori_twitter_api.h"
#include <QDebug>

ToriTwitterAPI::ToriTwitterAPI(QQuickItem *root, QObject *parent) :
    QObject(parent)
{
    this->_root = root;
    QObject::connect(this->_root, SIGNAL(send_twit(QString, QString)), this, SLOT(update(QString, QString)));
}

void ToriTwitterAPI::getAccounts()
{
    QHash<QString, QDBusObjectPath> reply = _client.getAccounts();

    QHashIterator<QString, QDBusObjectPath> iterator(reply);
    while (iterator.hasNext()) {
        iterator.next();
        AccountClient* proxy = new AccountClient(iterator.value().path());
        proxy->authenticate();
        this->_accountClients[iterator.key()] = proxy;
        qDebug() << "Account:" << iterator.key();
        QMetaObject::invokeMethod(this->_root, "add_account", Q_ARG(QVariant, iterator.key()), Q_ARG(QVariant, ""));
    }
}

void ToriTwitterAPI::update(QString user, QString status)
{
    AccountClient* client = this->_accountClients[user];
    client->update(status);
}

void ToriTwitterAPI::destroy(QString user, qlonglong twit_id)
{
    AccountClient* client = this->_accountClients[user];
    client->destroy(twit_id);
}

void ToriTwitterAPI::retweet(QString user, qlonglong twit_id)
{
    AccountClient* client = this->_accountClients[user];
    client->retweet(twit_id);
}

void ToriTwitterAPI::retweets(QString user, qlonglong twit_id)
{
    AccountClient* client = this->_accountClients[user];
    client->retweets(twit_id);
}

void ToriTwitterAPI::show(QString user, qlonglong twit_id)
{
    AccountClient* client = this->_accountClients[user];
    client->show(twit_id);
}
