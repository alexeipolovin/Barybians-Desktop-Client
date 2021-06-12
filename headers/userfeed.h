//
// Created by Kernux on 12.06.2021.
//

#ifndef BARYBIANS_DESKTOP_CLIENT_USERFEED_H
#define BARYBIANS_DESKTOP_CLIENT_USERFEED_H


#include <QWidget>
#include "webconnector.h"

class UserFeed : public QWidget {
public:
    UserFeed(WebConnector *webConnector);
    ~UserFeed();

    void openUserPage(int index = 0);

    void openUserPage(int index, QVector<User *> userList);

    void openUserPage(int index, QVector<User *> userList, WebConnector *webConnector);
};


#endif //BARYBIANS_DESKTOP_CLIENT_USERFEED_H
