//
// Created by rob on 01.11.2020.
//

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include "headers/card.h"

Card::Card(const QString& title, const QString& text, QWidget *parent) {

    ui = new QWidget();

    this->postTitle = new QLabel(title);
    this->postText = new QLabel(text);

    auto mainLayout = new QVBoxLayout();

    auto mainInfoLayout = new QVBoxLayout();

    auto *container = new QFrame();

    QString centerQSS = "QFrame "
                        "{"
                        "background-color: white;"
                        "border-radius: 30px;"
                        "height: 1000px;"
                        "width: 1000px;"
                        "}";

    container->setStyleSheet(centerQSS);

    mainLayout->addWidget(postTitle);
    mainLayout->addWidget(postText);

    container->setLayout(mainLayout);

    mainInfoLayout->addWidget(container);

    ui->setLayout(mainInfoLayout);
}

QWidget* Card::getWidget() const
{
    return this->ui;
}

Card::~Card() = default;
