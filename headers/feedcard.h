//
// Created by Kernux on 05.06.2021.
//

#ifndef BARYBIANS_DESKTOP_CLIENT_FEEDCARD_H
#define BARYBIANS_DESKTOP_CLIENT_FEEDCARD_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>

class feedcard : public QWidget {
public:
    feedcard(QString name = nullptr, QString title = nullptr, QString text = nullptr, QPixmap *photoLogo = nullptr,
             QString photoLogoFile = nullptr);

    ~feedcard();

    QVBoxLayout *mainLayout;
    QHBoxLayout *titleLayout;
};


#endif //BARYBIANS_DESKTOP_CLIENT_FEEDCARD_H
