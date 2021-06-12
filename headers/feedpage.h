//
// Created by Kernux on 05.06.2021.
//

#ifndef BARYBIANS_DESKTOP_CLIENT_FEEDPAGE_H
#define BARYBIANS_DESKTOP_CLIENT_FEEDPAGE_H

#include <QWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include "webconnector.h"

class FeedPage : public QWidget {
public:
    FeedPage(WebConnector *webConnector);

    ~FeedPage();

    QToolBar *toolBar;

    QVBoxLayout *mainLayout;
};


#endif //BARYBIANS_DESKTOP_CLIENT_FEEDPAGE_H
