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

#include <QLabel>
#include <QFile>
#include <QtWidgets/QPushButton>
#include "headers/userpage.h"
#include <QPushButton>



UserPage::~UserPage() =default;

UserPage::UserPage(QString *profilePhotoName, QString name, QString lastVisited, QString status,
                   WebConnector *webConnector, QPixmap *profilePhoto) {
    this->setFixedSize(300, 300);

    mainLayout = new QVBoxLayout();
    titleLayout = new QHBoxLayout();

    auto profilePhotoLabel = new QLabel();
    auto nameLabel = new QLabel(name);
    auto lastVisitedLabel = new QLabel(lastVisited);
    auto statusLabel = new QLabel(status);

    auto dialogButton = new QPushButton("Open Dialog");

    if(profilePhoto != nullptr)
    {
        profilePhotoLabel->setPixmap(*profilePhoto);
    } else {
        QPixmap photo;
        QFile file(*profilePhotoName);
        if(file.open(QFile::ReadOnly)) {
            photo.loadFromData(file.readAll());
            profilePhotoLabel->setPixmap(photo.scaled(128,128));
        }
    }

    titleLayout->addWidget(profilePhotoLabel);
    titleLayout->addWidget(nameLabel);
    titleLayout->addWidget(lastVisitedLabel);

    titleLayout->setAlignment(Qt::AlignTop);

    mainLayout->addLayout(titleLayout);
    mainLayout->addWidget(dialogButton);

    setLayout(mainLayout);
}
