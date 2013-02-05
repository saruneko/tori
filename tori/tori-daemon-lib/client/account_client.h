/**
 *
 * Copyright (c) 2013 Diego Sarmentero <diego.sarmentero@ninja-ide.org>
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

#ifndef ACCOUNT_CLIENT_H
#define ACCOUNT_CLIENT_H

#include <QObject>
#include <QString>
#include "account_proxy.h"

class AccountClient : public QObject
{
    Q_OBJECT
public:
    explicit AccountClient(QString service, QObject *parent = 0);

    void authenticate();
    void update(QString& status);
    void destroy(qlonglong twit_id);
    void retweet(qlonglong twit_id);
    void retweets(qlonglong twit_id);
    void show(qlonglong twit_id);


signals:

private slots:
    void userAuthenticated();
    void authenticationError(uint, QString);

private:
    AccountProxy* _proxy;

};

#endif // ACCOUNT_CLIENT_H
