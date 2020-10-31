#include "headers/mainwindow.h"
#include "headers/webconnector.h"

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <headers/userpage.h>

/**
  * @brief MainWindow::MainWindow
  *
  * @param *parent
  *
  * @author Polovin Alexei (alexeipolovin@gmail.com)
  *
  * Класс отвечающий за главное окно, основная цель отрисовать базовый интерфейс и дополнить его одной из страниц
*/

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Барыбинцы");
    webConnector = new WebConnector();
    webConnector->setLoginAndPassword("Test", "TEST");
    QNetworkRequest request = this->webConnector->createRequest("https://barybians.ru/api/auth", WebConnector::AUTH);
    QVBoxLayout *layout = new QVBoxLayout();
    QPushButton *dialogsButton = new QPushButton("Dialogi");
    QPushButton *button = new QPushButton("CreateGraz");
    QWidget *widget = new QWidget();
    layout->addWidget(dialogsButton);
    layout->addWidget(button);
    widget->setLayout(layout);
    setCentralWidget(widget);
    webConnector->sendRequest(request, WebConnector::AUTH);
    connect(button, SIGNAL(clicked()), SLOT(createGraz()));
    connect(dialogsButton, SIGNAL(clicked()), SLOT(getAllPosts()));
};

MainWindow::~MainWindow()
{
}

void MainWindow::getAllDialogs()
{
    QNetworkRequest request = this->webConnector->createRequest("https://barybians.ru/api/dialogs", WebConnector::GET_DIALOGS);
    this->webConnector->sendRequest(request, WebConnector::GET_DIALOGS);
}

void MainWindow::createGraz()
{
    mainUser = this->webConnector->getMainUser();
    UserPage *userPage = new UserPage(this->webConnector);
    userPage->setInfoLayout(this->mainUser->profilePhoto ,this->mainUser->name,this->mainUser->lastName, this->mainUser->birthDate, this->mainUser->status, this->mainUser->lastVisit);
//    userPage->build();
    hide();
    userPage->show();
}

void MainWindow::writeMe()
{
    QNetworkRequest request = this->webConnector->createRequest("https://barybians.ru/api/posts", WebConnector::WRITE_POST);
    this->webConnector->sendRequest(request, WebConnector::WRITE_POST);
}

void MainWindow::writePost()
{
    QNetworkRequest request = this->webConnector->createRequest("https://barybians.ru/api/auth", WebConnector::AUTH);
    this->webConnector->sendRequest(request, WebConnector::AUTH);
    this->textEdit->setText(this->webConnector->getToken());
}

void MainWindow::getAllUsers()
{
    //TODO: Переписать под отдельный класс, содержащий внутри себя request и тип запроса !!
    QNetworkRequest request = this->webConnector->createRequest("https://barybians.ru/api/users", WebConnector::ALL_USERS);
    this->webConnector->sendRequest(request, WebConnector::ALL_USERS);
}

void MainWindow::getAllPosts()
{
    QNetworkRequest request = this->webConnector->createRequest("https://barybians.ru/api/posts", WebConnector::ALL_POSTS);
    this->webConnector->sendRequest(request, WebConnector::ALL_POSTS);
}
