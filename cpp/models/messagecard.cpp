//
// Created by Kernux on 13.06.2021.
//

#include <QFile>
#include <QPixmap>
#include <QHBoxLayout>
#include <QLabel>
#include "headers/models/messagecard.h"

MessageCard::MessageCard(QString photoPath, QString text, bool isSelf) : QWidget() {
    QFile file(photoPath);
    QPixmap pm;
    if (file.open(QFile::ReadOnly)) {
        pm.loadFromData(file.readAll());
    }
    auto layout = new QHBoxLayout();

    auto label = new QLabel(text);

    auto photo = new QLabel();
    pm = pm.scaled(64, 64);
    photo->setPixmap(pm);


    if (!isSelf) {
        layout->addWidget(photo);
        layout->addWidget(label);
        layout->setAlignment(Qt::AlignLeft);
    } else {
        layout->addWidget(label);
        layout->addWidget(photo);
        layout->setAlignment(Qt::AlignRight);
    }
    setLayout(layout);
}
