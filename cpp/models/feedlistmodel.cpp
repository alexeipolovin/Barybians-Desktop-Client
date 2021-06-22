//
// Created by Kernux on 15.06.2021.FPF{P
//

#include "headers/models/feedlistmodel.h"
#include <QFile>

FeedListModel::FeedListModel(WebConnector *webConnector) : QAbstractListModel() {
    this->webConnector = webConnector;
}

int FeedListModel::rowCount(const QModelIndex &parent) const {
    return rows;
}

QVariant FeedListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        qDebug() << "Nothing to index";
        return QVariant();
    }
    if (index.row() > webConnector->getFeed()->length()) {
        qDebug() << "Overflow";
        return QVariant();
    }
    if (role == Qt::DisplayRole) {
        qDebug() << "Display role";
        return QVariant(webConnector->getFeed()->at(index.row())->title + "\n" +
                        webConnector->getFeed()->at(index.row())->text);
    }
    if (role == Qt::DecorationRole) {
        qDebug() << "Decoration role";
        QFile file(webConnector->getFeed()->at(index.row())->photoPath);
        if (file.open(QFile::ReadOnly))
            return QVariant(file.readAll());
    }
    return QVariant();
}

FeedListModel::~FeedListModel() = default;