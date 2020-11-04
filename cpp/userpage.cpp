#include "headers/userpage.h"

#include <QFile>
#include <QGraphicsColorizeEffect>
#include <QPropertyAnimation>
#include <headers/card.h>

#define STANDART_ANIMATION_DURATION 3000

#define STANDART_START_ANIMATION_VALUE 0.0

#define STANDART_END_ANIMATION_VALUE 1.0

UserPage::UserPage(WebConnector *webConnector, QWidget *parent) : QMainWindow(parent)
{
    qDebug() << "Main User"; webConnector->mainUser->printUserData();
    ui = new QWidget();

    dialogButton = new QPushButton("Dialogs");

    mainInfoFrame = new QFrame();

    mainVLayout = new QVBoxLayout();
    nameLastNameLayout = new QVBoxLayout();

    mainInfoLayout = new QHBoxLayout();

    posts = new QTextEdit();

    name = new QLabel("Default");
    lastName = new QLabel("Default");
    profilePhoto = new QLabel("");
    lastSeen = new QLabel("inf");

    name->setText(webConnector->mainUser->name + " " + webConnector->mainUser->lastName);

    lastSeen->setText(webConnector->mainUser->lastVisit);


    QString labelQSS = "QLabel {"
                       "font-size:30px;"
                       "font-family: Arial;"
                       "color: black;"
                       "font-weight:bold;"
                       "}";

    name->setStyleSheet(labelQSS);
    lastName->setStyleSheet(labelQSS);

    QHBoxLayout *getLayout = new QHBoxLayout();

    profilePhoto->setAlignment(Qt::AlignCenter);

    nameLastNameLayout->addWidget(name);
    nameLastNameLayout->addWidget(lastSeen);

    nameLastNameLayout->setSpacing(20);
    nameLastNameLayout->setAlignment(Qt::AlignCenter);

    mainInfoLayout->setSpacing(30);

    QPixmap pm = *new QPixmap();
    QFile file("hello.png");
    if(file.open(QFile::ReadWrite)) {
        pm.loadFromData(file.readAll());
        qDebug() << file.readAll();
    } else {
        qDebug() << "Я не смог открыть файл";
    }
    pm = pm.scaled(200,200);

    profilePhoto->setPixmap(pm);

    mainInfoLayout->addWidget(profilePhoto);
    mainInfoLayout->addWidget(dialogButton);
    mainInfoLayout->addLayout(nameLastNameLayout);

    getLayout->addLayout(mainInfoLayout);

    mainVLayout->addLayout(getLayout);

    Card *myCard = new Card("Hello", "World");
    mainVLayout->addWidget(myCard->getWidget());

    ui->setLayout(mainVLayout);

    setCentralWidget(ui);
};


void UserPage::setInfoLayout(QPixmap &photo, QString &name, QString &lastName, QString &birthDate, QString &status, QString &lastSeen)
{

}

void UserPage::resizeEvent(QResizeEvent *event)
{
//    QGraphicsColorizeEffect *eEffect = new QGraphicsColorizeEffect(loginButton);

    auto *loginFadeEffect = new QGraphicsOpacityEffect(name);
    auto *passwordFadeEffect = new QGraphicsOpacityEffect(lastSeen);
    auto *loginLabelFadeEffect = new QGraphicsOpacityEffect(profilePhoto);

    name->setGraphicsEffect(loginFadeEffect);
    lastSeen->setGraphicsEffect(passwordFadeEffect);
    profilePhoto->setGraphicsEffect(loginLabelFadeEffect);

    auto *loginAnimation = new QPropertyAnimation(loginFadeEffect, "opacity");
    auto *passwordAnimation = new QPropertyAnimation(passwordFadeEffect, "opacity");
    auto *loginLabelAnimation = new QPropertyAnimation(loginLabelFadeEffect, "opacity");


    loginAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    passwordAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    loginLabelAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    loginAnimation->setDuration(STANDART_ANIMATION_DURATION);
    passwordAnimation->setDuration(STANDART_ANIMATION_DURATION);
    loginLabelAnimation->setDuration(STANDART_ANIMATION_DURATION);

    loginAnimation->setStartValue(STANDART_START_ANIMATION_VALUE);
    passwordAnimation->setStartValue(STANDART_START_ANIMATION_VALUE);
    loginLabelAnimation->setStartValue(STANDART_START_ANIMATION_VALUE);;

    loginAnimation->setEndValue(STANDART_END_ANIMATION_VALUE);
    passwordAnimation->setEndValue(STANDART_END_ANIMATION_VALUE);
    loginLabelAnimation->setEndValue(STANDART_END_ANIMATION_VALUE);

    passwordAnimation->start();
    loginAnimation->start();
    loginLabelAnimation->start();

    QPixmap background(":/static/profile-background.jpg");

    QPalette pallete;

    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    pallete.setBrush(QPalette::Background, background);
    setPalette(pallete);

    QMainWindow::resizeEvent(event);
}

