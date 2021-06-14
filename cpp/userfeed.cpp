//
// Created by Kernux on 12.06.2021.
//

#include <QListView>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QFile>
#include <headers/userpage.h>
#include "headers/userfeed.h"

void UserFeed::openUserPage(int index, QVector<User *> userList, WebConnector *webConnector) {
    qDebug() << "ADF:" << userList.at(index)->id;
    UserPage *userPage = new UserPage(&userList.at(index)->photoName,
                                      userList.at(index)->name + " \n" + userList.at(index)->lastName,
                                      userList.at(index)->lastVisit, userList.at(index)->status, webConnector, nullptr,
                                      userList.at(index)->id);
    userPage->show();
}

UserFeed::UserFeed(WebConnector *webConnector) {
    auto mainLayout = new QVBoxLayout();
    auto listView = new QListView();

    auto mainModel = new QStandardItemModel();

    for (auto i:*webConnector->getUsersList()) {
        QStandardItem *item;
        if (i->photoName != "") {
            QPixmap pm;
            QFile file(i->photoName);
            if (file.open(QFile::ReadOnly)) {
                pm.loadFromData(file.readAll());
                item = new QStandardItem(pm, i->name + "\n" + i->lastName);
            } else {
                item = new QStandardItem(pm, i->name + "\n" + i->lastName);
            }
            file.deleteLater();
            mainModel->appendRow(item);
        }
    }
    listView->setModel(mainModel);
    mainLayout->addWidget(listView);

    setLayout(mainLayout);

    connect(listView, &QListView::doubleClicked, this, [listView, webConnector, this]() {
        qDebug() << "Current selected index:" << listView->currentIndex().row();
        int current_index = listView->currentIndex().row();
        openUserPage(current_index, *webConnector->getUsersList(), webConnector);
    });
}

UserFeed::~UserFeed() = default;