#include "mainwindow.h"
#include "userpage.h"
#include "webconnector.h"

#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
      webConnector = new WebConnector();
//    QWidget *widget = new QWidget();
//    auto *layout = new QVBoxLayout();
//    auto *getDialogs = new QPushButton("Dialogs");
//    layout->addWidget(getDialogs);
//    textEdit = new QTextEdit();
//    auto *postsButton = new QPushButton("Posts");
//    layout->addWidget(textEdit);
//    auto *allUsers = new QPushButton("All Users");
//    auto *writePost = new QPushButton("Click Me");
//    auto *writeMe = new QPushButton("Write Post");
//    layout->addWidget(writePost);
//    layout->addWidget(allUsers);
//    layout->addWidget(writeMe);
//    layout->addWidget(postsButton);
//    connect(writePost, SIGNAL(clicked()), SLOT(writePost()));
//    connect(writeMe, SIGNAL(clicked()), SLOT(writeMe()));
//    connect(postsButton, SIGNAL(clicked()), SLOT(getAllPosts()));
//    connect(getDialogs, SIGNAL(clicked()), SLOT(getAllDialogs()));
//    connect(allUsers, SIGNAL(clicked()), SLOT(getAllUsers()));
//    widget->setLayout(layout);
//    setCentralWidget(widget);
//    this->textEdit->insertHtml("<img src=\"https://sun9-74.userapi.com/l_dtPBrBz91LcQlRjaiy5KVhPBxBv2-s5Gf3Hg/n8YlAqplsmM.jpg\"></img>");
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
    qDebug() << "Юхууу";
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
    QNetworkRequest request = this->webConnector->createRequest("https://barybians.ru/api/users", WebConnector::ALL_USERS);
    //TODO: Переписать под отдельный класс, содержащий внутри себя request и тип запроса !!
    this->webConnector->sendRequest(request, WebConnector::ALL_USERS);
}

void MainWindow::getAllPosts()
{
    QNetworkRequest request = this->webConnector->createRequest("https://barybians.ru/api/posts", WebConnector::ALL_POSTS);
    this->webConnector->sendRequest(request, WebConnector::ALL_POSTS);
}
