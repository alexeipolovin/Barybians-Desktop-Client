//
// Created by Kernux on 05.06.2021.
//
#include "headers/feedpage.h"
#include <QtWidgets/QListView>
#include <QStandardItemModel>
#include <QtCore/QFile>
#include <QPainter>
#include <QTableView>
#include <QTableWidget>
#include <headers/feedlistmodel.h>

//TODO: Оптимизировать это
FeedPage::FeedPage(WebConnector *webConnector) : QWidget(nullptr) {
    m_list = new QVector<QStandardItem *>;
    setWindowIcon(QIcon(":/static/images/flex.png"));
    mainLayout = new QVBoxLayout();
    auto *listView = new QListView();
    auto *model = new FeedListModel(webConnector);
    auto vector = webConnector->getUsersList();

    connect(webConnector, &WebConnector::feedOk, this, [this, webConnector, model, listView, vector]() {
        qDebug() << "Data downloading...";
        QPixmap pm;
        for (auto i: *webConnector->getFeed()) {
            QStandardItem *item = nullptr;
            int photoIndex = 0;
            for (auto j : *vector) {
                if (j->id == i->userId) {
                    photoIndex = vector->indexOf(j);
                }
            }
            if (vector->at(photoIndex)->photoName != "") {
                QFile file(vector->at(photoIndex)->photoName);
                if (file.open(QFile::ReadOnly)) {
                    pm.loadFromData(file.readAll());
                    item = new QStandardItem(pm, i->title + "\n" + i->text);
                } else {
                }
                file.deleteLater();
            }
            m_list->push_back(item);
            model->insertRow(0);
        }
        listView->setModel(model);
        connect(listView, &QListView::clicked, this, [listView]() {
            qDebug() << "ListView current index:" << listView->currentIndex();
        });
        mainLayout->addWidget(listView);
        setLayout(mainLayout);
    });

    webConnector->getFeed();

}

FeedPage::~FeedPage() {
    qDebug() << "Feed Page destruction";
    qDeleteAll(*m_list);
    delete m_list;
    delete mainLayout;
}