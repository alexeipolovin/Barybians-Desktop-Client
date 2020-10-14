#include "userpage.h"

UserPage::UserPage()
{
    mainWidget = new QWidget();
    mainLayout = new QVBoxLayout();
    infoLayout = new QHBoxLayout();
    postsLayout = new QVBoxLayout();


    userName = new QLabel();
    lastName = new QLabel();
    userStatus = new QLabel();
    userPhoto = new QLabel();
    userStatus = new QLabel();


};


void UserPage::setInfoLayout(QPixmap &photo, QString &name, QString &lastName, QString &birthDate, QString &status, QString &lastSeen)
{
//    QVector<QLabel> *vector = new QVector<QLabel>();
    this->userName->setText(name);
    this->lastName->setText(lastName);
    this->userPhoto->setPixmap(photo);
    this->userStatus->setText(status);

    this->infoLayout->addWidget(this->userName);
    this->infoLayout->addWidget(this->lastName);
    this->infoLayout->addWidget(this->userPhoto);
    this->infoLayout->addWidget(this->userStatus);
}

void UserPage::build() {
    this->mainLayout->addLayout(infoLayout);
    this->mainLayout->addLayout(postsLayout);
    this->mainWidget->setLayout(mainLayout);
}

QWidget *UserPage::getMainWidget() {
    return this->mainWidget;
}


QVBoxLayout* UserPage::getMainLayout() {
    return mainLayout;
}
