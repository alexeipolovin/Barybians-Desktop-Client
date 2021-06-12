//
// Created by Kernux on 13.06.2021.
//

#include <QFile>
#include <QPixmap>
#include <QHBoxLayout>
#include <QLabel>
#include "headers/messagecard.h"

MessageCard::MessageCard(QString photoPath, QString text, bool isSelf): QWidget() {
    QFile file(photoPath);
    QPixmap pm;
    if(file.open(QFile::ReadOnly))
    {
        pm.loadFromData(file.readAll());
    }
    auto layout = new QHBoxLayout();

    auto label = new QLabel(text);

    auto photo = new QLabel();
    pm = pm.scaled(64, 64);
    photo->setPixmap(pm);

    layout->addWidget(photo);
    layout->addWidget(label);
    if(isSelf)
        layout->setAlignment(Qt::AlignLeft);
    else
        layout->setAlignment(Qt::AlignRight);
    setLayout(layout);
}