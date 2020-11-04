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
    for(int i = 0; i < 10; i++) {
        Card *myCard = new Card("Hello", "Lorem ipsum dolor sit amet, consectetur adipiscing elit. In quis enim luctus, ornare arcu non, cursus sem. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Vivamus vel ultrices neque. Morbi accumsan libero lobortis porta convallis. Donec euismod purus sem, ac consequat ante venenatis eu. Vivamus rhoncus fermentum tellus eget ullamcorper. Maecenas nec aliquam mi. Integer convallis enim sit amet rutrum auctor. Curabitur lacus elit, aliquam sit amet odio at, consequat finibus lacus. Praesent pulvinar sollicitudin ante, ut vulputate nunc sollicitudin eu. Nunc sagittis mi dui, ut imperdiet erat maximus sed. Etiam elementum tincidunt ex ut tristique. Integer vel mauris pharetra erat ultrices mollis ut et sem. Sed cursus interdum purus id rhoncus. Nam eu odio porttitor tortor fermentum vulputate. Donec vel dignissim enim, nec luctus elit.\
        Maecenas sollicitudin pretium nisl, id fermentum tortor rhoncus at. Sed blandit elit id libero fermentum scelerisque. Suspendisse gravida turpis nibh, vel consectetur metus facilisis ac. Nunc commodo bibendum orci et finibus. Sed nec lacus in velit accumsan dictum. Aliquam semper, turpis et fermentum tristique, mauris neque rhoncus nibh, ut ornare turpis nunc id odio. Phasellus justo dolor, imperdiet ac arcu sit amet, consequat malesuada arcu. Pellentesque in ipsum rutrum eros commodo lacinia nec non urna. Maecenas ex metus, porttitor ut commodo at, suscipit vel ex. Phasellus ante magna, aliquet sit amet commodo ac, consectetur eget purus. Phasellus dapibus arcu sapien, quis ultricies lacus volutpat nec. Phasellus convallis bibendum dolor, at tempor est faucibus nec. Nunc et nunc mattis, finibus enim eu, dignissim sem. \
                Quisque pellentesque neque sit amet massa ullamcorper convallis. Nam sit amet venenatis erat, nec bibendum erat. Fusce id dictum erat, a consectetur neque. Phasellus molestie ultricies ante. Mauris tempus imperdiet elit, a tempor nibh dignissim at. Integer euismod arcu a justo ornare vulputate. Pellentesque et dui faucibus, bibendum ex vel, efficitur metus. Donec dolor quam, aliquam id ultricies vel, cursus nec risus. \
                Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia curae; Pellentesque vitae tempus lacus. Donec congue a purus eu dictum. Donec dictum, metus pellentesque aliquam viverra, purus arcu gravida dui, id ultrices massa tortor eu velit. Nullam blandit orci a elementum maximus. Cras sed erat in lacus faucibus eleifend. Nunc non lorem porttitor, blandit massa sit amet, efficitur mauris. Proin volutpat purus purus, eu convallis sapien lobortis nec. Nulla aliquet dictum facilisis.\
                Ut gravida ante nec faucibus imperdiet. Mauris dapibus, urna sed interdum hendrerit, turpis ante cursus mauris, ac blandit diam tortor vel est. Morbi interdum, neque a ultricies euismod, turpis dolor convallis urna, id accumsan ex metus elementum ipsum. Vestibulum molestie quis arcu ac cursus. Morbi at ultrices nisl. Phasellus ac dictum risus. In porttitor, eros sed malesuada ornare, urna velit tristique orci, facilisis egestas eros odio lacinia metus. Cras sollicitudin auctor lacus, at convallis libero. Sed ultricies sapien nec enim varius, id bibendum erat accumsan. Pellentesque et accumsan nisi.");
        mainVLayout->addWidget(myCard->getWidget());
    }
//    auto *secondCard = new Card("Hello, world","Privet");
//    mainVLayout->addWidget(secondCard->getWidget());

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

    QPixmap background(":/static/images/profile-background.jpg");

    QPalette pallete;

    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    pallete.setBrush(QPalette::Background, background);
    setPalette(pallete);

    QMainWindow::resizeEvent(event);
}


