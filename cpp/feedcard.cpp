//
// Created by Kernux on 05.06.2021.
//

#include <QtWidgets/QLabel>
#include <QtCore/QFile>
#include "headers/feedcard.h"
#include <QDebug>

feedcard::feedcard(QString name, QString title, QString text, QPixmap *photoLogo, QString photoLogoFile) : QWidget() {
    mainLayout = new QVBoxLayout();
    titleLayout = new QHBoxLayout();

    auto photoLabel = new QLabel();
    auto nameLabel = new QLabel(name);
    auto titleLabel = new QLabel(title);
    auto textLabel = new QLabel(text);

    if(photoLogo != nullptr)
    {
        QFile file(photoLogoFile);

        if(file.open(QFile::ReadOnly))
        {
            QPixmap pixmap;
            pixmap.loadFromData(file.readAll());
            photoLabel->setPixmap(pixmap);
        } else {
            photoLabel->setPixmap(*photoLogo);
        }
    }

    titleLayout->addWidget(photoLabel);
    titleLayout->addWidget(nameLabel);

    mainLayout->addLayout(titleLayout);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(textLabel);

    qDebug() <<"RABOTAI";

    setLayout(mainLayout);
}


feedcard::~feedcard() = default;