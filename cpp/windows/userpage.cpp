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
 * FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
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
#include <QLineEdit>
#include <QListView>
#include <QStandardItemModel>
#include <QTextEdit>
#include <qtoolbar.h>
#include <headers/windows/dialogwindow.h>
#include "headers/windows/userpage.h"

UserPage::~UserPage() = default;

UserPage::UserPage(QString *profilePhotoName, QString name, QString lastVisited, QString status,
                   WebConnector *webConnector, QPixmap *profilePhoto, int id) {
    QPixmap icon;
    if (*profilePhotoName != "") {
        QFile file(*profilePhotoName);
        if (file.open(QFile::ReadOnly)) {
            icon.loadFromData(file.readAll());
        }
    }
    setWindowIcon(QIcon(icon));\
    QRegExp *re = new QRegExp("[a-z])([A-Z])");
//    QStringList list = name.split(*re);
    setWindowTitle(name);
    this->resize(300, 300);


    mainLayout = new QVBoxLayout();
    titleLayout = new QHBoxLayout();

    auto view = new QListView();
    auto model = new QStandardItemModel();

    auto profilePhotoLabel = new QLabel();
    auto nameLabel = new QLabel(name);
    auto lastVisitedLabel = new QLabel(lastVisited);
    auto statusLabel = new QLabel(status);
    auto statusLastVisitLayout = new QVBoxLayout();
    statusLastVisitLayout->addWidget(lastVisitedLabel);
    statusLastVisitLayout->addWidget(statusLabel);

    auto dialogButton = new QPushButton("Open Dialog");
    auto writePostButton = new QPushButton("WritePost");
    auto exitButton = new QPushButton("Exit");
    if (profilePhoto != nullptr) {
        profilePhotoLabel->setPixmap(*profilePhoto);
    } else {
        QPixmap photo;
        QFile file(*profilePhotoName);
        if (file.open(QFile::ReadOnly)) {
            photo.loadFromData(file.readAll());
            profilePhotoLabel->setPixmap(photo.scaled(128, 128));
        }
    }

    titleLayout->addWidget(profilePhotoLabel);
    titleLayout->addWidget(nameLabel);
    titleLayout->addLayout(statusLastVisitLayout);

    titleLayout->setAlignment(Qt::AlignTop);

    mainLayout->addLayout(titleLayout);
    if (webConnector->mainUser->id == id)
        mainLayout->addWidget(writePostButton);
    if (webConnector->mainUser->id != id)
        mainLayout->addWidget(dialogButton);
    mainLayout->addWidget(exitButton);

    connect(exitButton, &QPushButton::clicked, this, []() {
       QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
       settings->setValue("login", "");
       settings->setValue("passwd", "");
       delete settings;
    });

    auto vector = webConnector->getUsersList();

    connect(dialogButton, &QPushButton::clicked, this, [webConnector, id]() {
        qDebug() << "New user id:" << id;
        auto dialogWindow = new DialogWindow(webConnector, id);
        dialogWindow->show();
    });

    connect(webConnector, &WebConnector::feedOk, this, [this, webConnector, vector, model, view, icon, id]() {
                qDebug() << "Downloading again...";
                for (auto i : *webConnector->getFeed()) {
                    QStandardItem *item;
                    qDebug() << "User id" << i->userId;
                    qDebug() << "My id" << id;
                    if (i->userId == id) {
                        qDebug() << "user id is" << i->userId;
                        item = new QStandardItem(icon, i->title + "\n" + i->text);
                        if(i->userId != webConnector->mainUser->id)
                            item->setEditable(false);
                        model->appendRow(item);
                    }
                    view->setModel(model);
                }
            }
    );
    for (auto i : *webConnector->getFeed()) {
        QStandardItem *item;
        qDebug() << "User id" << i->userId;
        qDebug() << "My id" << id;
        if (i->userId == id) {
            qDebug() << "user id is" << i->userId;
            item = new QStandardItem(icon, i->title + "\n" + i->text);
            model->appendRow(item);
        }
        view->setModel(model);
    }
    mainLayout->addWidget(view);
    setLayout(mainLayout);
    connect(writePostButton, &QPushButton::clicked, this, [this, webConnector]() {
        QWidget *mainWidg = new QWidget();
        QVBoxLayout *mainLay = new QVBoxLayout();
        QPushButton *sendButton = new QPushButton();
        QLineEdit *lineEdit = new QLineEdit();
        QTextEdit *textEdit = new QTextEdit();

        connect(sendButton, &QPushButton::clicked, this, [webConnector, lineEdit, textEdit]() {
            webConnector->writePost(lineEdit->text(), textEdit->toPlainText());
        });

        mainLay->addWidget(lineEdit);
        mainLay->addWidget(textEdit);
        mainLay->addWidget(sendButton);
        mainWidg->setLayout(mainLay);
        mainWidg->show();

    });
}
