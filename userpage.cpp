#include "userpage.h"

#include <QLayout>
/**
  * @brief UserPage::UserPage
  *
  * @author Polovin Alexei (alexeipolovin@gmail.com)
  *
  * Класс отвечает за создание и взаимодействие со страницей пользователя
*/

UserPage::UserPage(WebConnector webconnector)
{
    mainWidget = new QWidget();
    mainLayout = new QVBoxLayout();
    infoLayout = new QHBoxLayout();
    postsLayout = new QVBoxLayout();
    postsField = new QTextEdit();


    userName = new QLabel();
    lastName = new QLabel();
    userStatus = new QLabel();
    userPhoto = new QLabel();
    userStatus = new QLabel();


};


void UserPage::setInfoLayout(QPixmap &photo, QString &name, QString &lastName, QString &birthDate, QString &status, QString &lastSeen)
{
//    QVector<QLabel> *vector = new QVector<QLabel>();
    QWidget *fixedSizeMain = new QWidget();
    QHBoxLayout *blayout = new QHBoxLayout();
    fixedSizeMain->setFixedHeight(150);
    fixedSizeMain->setLayout(blayout);
    this->userName->setText(name);
    this->lastName->setText(lastName);
    this->userPhoto->setPixmap(photo);
    this->userStatus->setText(status);

   blayout->addWidget(this->userName);
   blayout->addWidget(this->lastName);
   blayout->addWidget(this->userPhoto);
   blayout->addWidget(this->userStatus);

   this->infoLayout->addWidget(fixedSizeMain);
}

void UserPage::build()
{
    this->mainLayout->addLayout(infoLayout);
    this->mainLayout->addLayout(postsLayout);
    this->mainLayout->addLayout(postsLayout);
    this->mainLayout->addWidget(postsField);
    this->mainWidget->setLayout(mainLayout);
}

QWidget *UserPage::getMainWidget()
{
    return this->mainWidget;
}


QVBoxLayout* UserPage::getMainLayout()
{
    return mainLayout;
}

void UserPage::setPostsLayout()
{
    this->postsLayout->addWidget(postsField);
}
