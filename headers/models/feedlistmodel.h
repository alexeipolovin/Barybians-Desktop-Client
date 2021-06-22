//
// Created by Kernux on 15.06.2021.
//

#ifndef BARYBIANS_DESKTOP_CLIENT_FEEDLISTMODEL_H
#define BARYBIANS_DESKTOP_CLIENT_FEEDLISTMODEL_H


#include <QAbstractListModel>
#include "headers/webconnector.h"

class FeedListModel : public QAbstractListModel {
public:
    FeedListModel(WebConnector *webConnector);
    ~FeedListModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
    int rows = 0;

    WebConnector *webConnector;

};


#endif //BARYBIANS_DESKTOP_CLIENT_FEEDLISTMODEL_H
