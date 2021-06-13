/*
 * Copyright (c) 2021 Alexei Polovin (alexeipolovin@gmail.com)
 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

//
// Created by Kernux on 03.06.2021.
//

#ifndef BARYBIANS_DESKTOP_CLIENT_USERPAGE_H
#define BARYBIANS_DESKTOP_CLIENT_USERPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "webconnector.h"

class UserPage : public QWidget {

    ~UserPage();

    QVBoxLayout *mainLayout;

    QHBoxLayout *titleLayout;


    //TODO: Сделать посты
public:
    explicit UserPage(QString *profilePhotoName = nullptr, QString name = nullptr, QString lastVisited = nullptr,
                      QString status = nullptr, WebConnector *webConnector = nullptr, QPixmap *profilePhoto = nullptr,
                      int id = 0);
};

#endif //BARYBIANS_DESKTOP_CLIENT_USERPAGE_H
