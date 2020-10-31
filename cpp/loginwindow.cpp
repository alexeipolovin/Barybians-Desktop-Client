#include "headers/loginwindow.h"
#include "headers/mainwindow.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QGraphicsColorizeEffect>
#include <QPropertyAnimation>
#include <QDir>
#include <QMessageBox>

//Может пора перейти на плюсовые константы?
#define FONT_SIZE "font-size: 15px;"
#define STANDART_ANIMATION_DURATION 1500
#define STANDART_START_ANIMATION_VALUE 0.0
#define STANDART_END_ANIMATION_VALUE 1.0
#define DB_NAME "sqlite.db"

/**
  * @brief LoginWindow::LoginWindow
  *
  * @param *parent
  *
  * Класс, который выполняет все основные действия для построения разметки окна входа и реализующий все функции входа, в том числе и автоподключение к бд;
  *
  * @author Polovin Alexei (alexeipolovin@gmail.com)
  *
*/

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent)
{
    webConnector = new WebConnector();
    QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);

    if(settings->value("email").toString().length() > 4)
    {

    }

    setWindowIcon(QIcon(":/static/flex.png"));

    QFrame *centerContainer = new QFrame();

    QPixmap logo(":/static/flex.png");

    QWidget *ui = new QWidget;
    setCentralWidget(ui);

    QHBoxLayout *mainHLayout = new QHBoxLayout();
    QHBoxLayout *buttonContainer = new QHBoxLayout();

    QVBoxLayout *mainLayout = new QVBoxLayout();
    QVBoxLayout *centerLayout = new QVBoxLayout();

    loginEdit = new QLineEdit();
    passwordEdit = new QLineEdit();

    QLabel *logoIcon = new QLabel();
    QLabel *loginTextLabel = new QLabel("<span style = 'font-size: 20px; color: black;'>LOGIN</span>");
    passwordLabel = new QLabel("<span style='font-size:15px; color: black;'>Password</span>");
    loginLabel = new QLabel("<span style='font-size:15px; color: black;'>Username</span>");

    loginButton = new QPushButton("Login");

    QString centerQSS = "QFrame "
                        "{"
                        "background-color: white;"
                        "border-radius: 30px;"
                        "height: 1000px;"
                        "width: 1000px;"
                        "}";

    QString editTextStyle = "QLineEdit "
                            "{"
                            "border: 1px solid #282830;"
                            "color: black;"
//                            "background-color:#282830;"
                            FONT_SIZE
                            "height:17px;"
                            "width:400px;"
                            "margin-left:20px;"
                            "margin-right:20px;"
                            "border-radius:10px;"
                            "padding:5px;"
                            "}";

    QString buttonStyle = "QPushButton "
                          "{"
                          "color: white;"
//                          "color: #282830;"
//                          FONT_SIZE
                          "background-color: black;"
                          "margin-bottom:20px;"
                          "margin-top:20px;"
                          "border:none;"
                          "height:20px;"
                          "width:100px;"
                          "padding:5px;"
                          "border-radius: 10px;"
                          "}"
                          "QPushButton:hover"
                          "{"
                          "background-color:#47B0D0;"
                          "}";

    QString labelStyle = "QLabel "
                         "{"
                         "color: black;"
//                         "color: rgb(255, 255, 255);"
                         "margin-left:20px;"
                         "margin-right:20px;"
                         "}";

    logoIcon->setPixmap(logo);
    logoIcon->setAlignment(Qt::AlignCenter);

    loginTextLabel->setAlignment(Qt::AlignCenter);
    loginTextLabel->setStyleSheet(labelStyle + "margin-top: 20px");

    loginEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    loginEdit->setFont(QFont("Arial"));
    passwordEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    loginLabel->setStyleSheet(labelStyle + "margin-top: 20px");
    loginLabel->setAlignment(Qt::AlignCenter);
    loginLabel->setFont(QFont("Arial", 12));

    passwordLabel->setStyleSheet(labelStyle + "margin-top: 20px");
    passwordLabel->setAlignment(Qt::AlignCenter);
    passwordLabel->setFont(QFont("Arial", 12));

    loginEdit->setStyleSheet(editTextStyle);
    passwordEdit->setStyleSheet(editTextStyle);
    passwordEdit->setEchoMode(QLineEdit::Password);

    buttonContainer->addWidget(loginButton);
    buttonContainer->setAlignment(Qt::AlignCenter);

    loginButton->setStyleSheet(buttonStyle);
    loginButton->setFont(QFont("Arial", 12));

    centerLayout->addWidget(logoIcon);
//    centerLayout->addWidget(loginTextLabel);
    centerLayout->addWidget(loginLabel);
    centerLayout->addWidget(loginEdit);
    centerLayout->addWidget(passwordLabel);
    centerLayout->addWidget(passwordEdit);
    centerLayout->addLayout(buttonContainer);
    centerLayout->setAlignment(Qt::AlignCenter);

    centerContainer->setStyleSheet(centerQSS);
    centerContainer->setLayout(centerLayout);
    mainHLayout->addWidget(centerContainer);
    mainHLayout->setAlignment(Qt::AlignCenter);

    mainLayout->addLayout(mainHLayout);
    mainLayout->setAlignment(Qt::AlignCenter);

    ui->setLayout(mainLayout);

    setCentralWidget(ui);

    connect(loginButton, SIGNAL(clicked()), SLOT(openMainWindow()));

    showMaximized();
    }


/**
  * @brief LoginWindow::resizeEvent
  *
  * @param event
  *
  * Функция вызывается каждый раз при изменении размера онка. Создаёт и запускает все анимации
  *
  * @author Polovin Alexei (alexeipolovin@gmail.com)
*/

void LoginWindow::resizeEvent(QResizeEvent *event)
{
    QGraphicsColorizeEffect *eEffect = new QGraphicsColorizeEffect(loginButton);

    QGraphicsOpacityEffect *loginFadeEffect = new QGraphicsOpacityEffect(loginEdit);
    QGraphicsOpacityEffect *passwordFadeEffect = new QGraphicsOpacityEffect(passwordEdit);
    QGraphicsOpacityEffect *loginLabelFadeEffect = new QGraphicsOpacityEffect(loginLabel);
    QGraphicsOpacityEffect *passwordLabelFadeEffect = new QGraphicsOpacityEffect(passwordLabel);

    loginEdit->setGraphicsEffect(loginFadeEffect);
    passwordEdit->setGraphicsEffect(passwordFadeEffect);
    loginLabel->setGraphicsEffect(loginLabelFadeEffect);
    passwordLabel->setGraphicsEffect(passwordLabelFadeEffect);
    loginButton->setGraphicsEffect(eEffect);

    QPropertyAnimation *loginAnimation = new QPropertyAnimation(loginFadeEffect, "opacity");
    QPropertyAnimation *passwordAnimation = new QPropertyAnimation(passwordFadeEffect, "opacity");
    QPropertyAnimation *loginLabelAnimation = new QPropertyAnimation(loginLabelFadeEffect, "opacity");
    QPropertyAnimation *passwordLabelAnimation = new QPropertyAnimation(passwordLabelFadeEffect, "opacity");
    QPropertyAnimation *paAnimation = new QPropertyAnimation(eEffect, "color");


    loginAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    passwordAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    loginLabelAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    passwordLabelAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    loginAnimation->setDuration(STANDART_ANIMATION_DURATION);
    passwordAnimation->setDuration(STANDART_ANIMATION_DURATION);
    loginLabelAnimation->setDuration(STANDART_ANIMATION_DURATION);
    passwordLabelAnimation->setDuration(STANDART_ANIMATION_DURATION);
    paAnimation->setDuration(STANDART_ANIMATION_DURATION);

    loginAnimation->setStartValue(STANDART_START_ANIMATION_VALUE);
    passwordAnimation->setStartValue(STANDART_START_ANIMATION_VALUE);
    loginLabelAnimation->setStartValue(STANDART_START_ANIMATION_VALUE);
    passwordLabelAnimation->setStartValue(STANDART_START_ANIMATION_VALUE);

    paAnimation->setStartValue(QColor(Qt::blue));

    loginAnimation->setEndValue(STANDART_END_ANIMATION_VALUE);
    passwordAnimation->setEndValue(STANDART_END_ANIMATION_VALUE);
    loginLabelAnimation->setEndValue(STANDART_END_ANIMATION_VALUE);
    passwordLabelAnimation->setEndValue(STANDART_END_ANIMATION_VALUE);

    paAnimation->setEndValue(QColor(Qt::black));

    passwordAnimation->start();
    loginAnimation->start();
    loginLabelAnimation->start();
    passwordLabelAnimation->start();
    paAnimation->start();

    QPixmap background(":/static/bg.jpg");

    QPalette pallete;

    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    pallete.setBrush(QPalette::Background, background);
    setPalette(pallete);

    QMainWindow::resizeEvent(event);
}


void LoginWindow::checkMainWindow()
{
    QString username = this->loginEdit->text();
    QString password = this->passwordEdit->text();

    qDebug() << "Ну давай тест";
    if(this->webConnector->token != "false")
    {
        hide();

        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();

        this->close();
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Wrong login or password!. Are you sure?"), QMessageBox::Cancel);
    }

    qDebug() << "Плюнул БАС";
}

void LoginWindow::openMainWindow()
{
    QString username = this->loginEdit->text();
    QString password = this->passwordEdit->text();
    webConnector->setLoginAndPassword(username, password);

    webConnector->makeAuth();

    qDebug() << username;
    qDebug() << password;
    connect(webConnector, &WebConnector::valueChanged, this, &LoginWindow::checkMainWindow);

}
