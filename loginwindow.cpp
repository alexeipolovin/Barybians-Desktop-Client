#include "loginwindow.h"
#include <mainwindow.h>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent)
{
    QSettings *settings = new QSettings("settings.ini", QSettings::IniFormat);
    db =  QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\Users\\Kernux\\Documents\\Barybians-Desktop-Client\\sqlite.db");
    bool dbOk = db.open();

    if(!dbOk)
    {
        qDebug() << "Error while oppening database";
    } else
    {
    }
    if(settings->value("email").toString().length() > 4)
    {
        this->openMainWindow();
        return;
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
    QLabel *passwordLabel = new QLabel("<span style='font-size:15px; color: black;'>Password</span>");
    QLabel *loginLabel = new QLabel("<span style='font-size:15px; color: black;'>Username</span>");

    QPushButton *loginButton = new QPushButton("Login");

    QString centerQSS = "QFrame "
                        "{"
                        "background-color: white;"
                        "border-radius: 20px;"
                        "height: 1000px;"
                        "width: 1000px;"
                        "}";

    QString editTextStyle = "QLineEdit "
                            "{"
                            "border: 1px solid #282830;"
                            "color: black;"
//                            "background-color:#282830;"
                            "font-size:13px;"
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
                          "font-size: 15px;"
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
    passwordEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    loginLabel->setStyleSheet(labelStyle + "margin-top: 20px");
    loginLabel->setAlignment(Qt::AlignCenter);

    passwordLabel->setStyleSheet(labelStyle + "margin-top: 20px");
    passwordLabel->setAlignment(Qt::AlignCenter);

    loginEdit->setStyleSheet(editTextStyle);
    passwordEdit->setStyleSheet(editTextStyle);
    passwordEdit->setEchoMode(QLineEdit::Password);

    buttonContainer->addWidget(loginButton);
    buttonContainer->setAlignment(Qt::AlignCenter);

    loginButton->setStyleSheet(buttonStyle);

    centerLayout->addWidget(logoIcon);
    centerLayout->addWidget(loginTextLabel);
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

//    this->resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
}

void LoginWindow::resizeEvent(QResizeEvent *event)
{
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
        QSqlQuery query(this->db);
        query.exec("INSERT INTO user (NAME, PASSWORD) "
                   "VALUES ('"+username+"','"+password+"')");
        hide();
        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();
        this->close();
    }
    qDebug() << "Плюнул БАС";
}

void LoginWindow::openMainWindow()
{
    QString username = this->loginEdit->text();
    QString password = this->passwordEdit->text();

    qDebug() << username;
    qDebug() << password;

    webConnector = new WebConnector(username, password);

    webConnector->makeAuth();
    connect(webConnector, &WebConnector::valueChanged, this, &LoginWindow::checkMainWindow);

}
