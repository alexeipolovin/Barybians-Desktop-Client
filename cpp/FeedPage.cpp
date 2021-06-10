//
// Created by Kernux on 05.06.2021.
//

#include "headers/FeedCard.h"
#include "headers/FeedPage.h"
#include <QtWidgets/QListView>
#include <QStandardItemModel>
#include <QtCore/QFile>
#include <QPainter>

FeedPage::FeedPage(WebConnector *webConnector)
{
    setWindowIcon(QIcon(":/static/images/flex.png"));
    mainLayout = new QVBoxLayout();
    auto *listView = new QListView();
    auto *model = new QStandardItemModel(this);
    auto vector = webConnector->getUsersList();
    connect(webConnector, &WebConnector::feedOk, this, [this, webConnector, model, listView, vector](){
        qDebug() << "Data downloading...";
        for(auto i: *webConnector->getFeed()) {
            QStandardItem *item = nullptr;
//            connect(webConnector, &WebConnector::pixmapUpdated, this, [this, i, item, model]() mutable
//            {
                int photoIndex = 0;
                for(auto j : *vector) {
                    if (j->id == i->userId) {
                        photoIndex = vector->indexOf(j);
                    }
                }
                QPixmap pm;
//                qDebug() << "User id:" << i->userId;
//                qDebug() << "Length:" << vector->indexOf(i->userId);
                if(vector->at(photoIndex)->photoName != "") {
//                    qDebug() << "File name:" << vector->at(photoIndex)->photoName;
                    QFile file(vector->at(photoIndex)->photoName);
                    if(file.open(QFile::ReadOnly))
                    {
                        pm.loadFromData(file.readAll());
                        item = new QStandardItem(pm, i->title + "\n" + i->text);
//                        auto *brush = new QBrush(pm);
//                        item->setBackground(*brush);
//                        delete brush;
                        item->setEditable(false);
                    } else {
//                        qDebug() << "Free File";
                        item = new QStandardItem(webConnector->lastPixmap, i->title + "\n" + i->text);
                        item->setEditable(false);
                    }
                    file.deleteLater();
                }

            model->appendRow(item);
//            });
//            FeedCard *feedCard = new FeedCard(i->name, i->title, i->text, nullptr, i->photoPath);
        }
        listView->setModel(model);
        mainLayout->addWidget(listView);
        setLayout(mainLayout);
    });

    webConnector->getFeed();

}

FeedPage::~FeedPage()
{
    delete mainLayout;
}