//
// Created by Kernux on 05.06.2021.
//

#ifndef BARYBIANS_DESKTOP_CLIENT_FEEDCARD_H
#define BARYBIANS_DESKTOP_CLIENT_FEEDCARD_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>

class FeedCard : public QWidget {
public:
    FeedCard(QString name=nullptr, QString title=nullptr, QString text=nullptr, QPixmap *photoLogo=nullptr, QString photoLogoFile=nullptr);
    ~FeedCard();

    QVBoxLayout *mainLayout;
    QHBoxLayout *titleLayout;
};


#endif //BARYBIANS_DESKTOP_CLIENT_FEEDCARD_H
