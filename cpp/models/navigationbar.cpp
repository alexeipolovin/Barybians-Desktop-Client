//
// Created by Kernux on 13.06.2021.
//

#include <QHBoxLayout>
#include <QPushButton>
#include "headers/models/navigationbar.h"

NavigationBar::NavigationBar() : QWidget() {
    auto mainLayout = new QHBoxLayout();

    auto homeButton = new QPushButton("Home");
    auto newsButton = new QPushButton("News");
    auto settingsButton = new QPushButton("Settings");
    auto dialogsButton = new QPushButton("Dialogs");

    mainLayout->addWidget(homeButton);
    mainLayout->addWidget(dialogsButton);
    mainLayout->addWidget(newsButton);
    mainLayout->addWidget(settingsButton);

    setStyleSheet("QHBoxLayout {background-color:white; margin:0;} QPushButton {background-color:white; margin:0;}");
    mainLayout->setAlignment(Qt::AlignBottom);

    setLayout(mainLayout);

}

NavigationBar::~NavigationBar() = default;