#include "mainwindow.h"
#include "userpage.h"
#include "webconnector.h"

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

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
    webConnector = new WebConnector();
    QNetworkRequest request = this->webConnector->createRequest("https://barybians.ru/api/auth", WebConnector::AUTH);
    QPushButton *button = new QPushButton("CreateGraz");
    setCentralWidget(button);
    webConnector->sendRequest(request, WebConnector::AUTH);
    connect(button, SIGNAL(clicked()), SLOT(createGraz()));
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
    UserPage *userPage = new UserPage();
    userPage->setInfoLayout(this->mainUser->profilePhoto ,this->mainUser->name,this->mainUser->lastName, this->mainUser->birthDate, this->mainUser->status, this->mainUser->lastVisit);
    userPage->build();
    QWidget *lay = userPage->getMainWidget();
    setCentralWidget(lay);
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
