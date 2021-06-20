#include "headers/mainwindow.h"

#include <QGuiApplication>
#include <QLineEdit>
#include <QtQml/QQmlApplicationEngine>
#include "headers/userpage.h"
#include <headers/feedpage.h>
#include <headers/userfeed.h>
#include <headers/dialogwindow.h>
#include <headers/navigationbar.h>

/**
  * @brief MainWindow::MainWindow
  *
  * @param *parent
  *
  * @author Polovin Alexei (alexeipolovin@gmail.com)
  *
  * Класс отвечающий за главное окно, основная цель отрисовать базовый интерфейс и дополнить его одной из страниц
*/

MainWindow::MainWindow(QWidget *parent, WebConnector *webConnector) : QMainWindow(parent) {
    setWindowTitle("Барыбинцы");
    User *mainUser = &webConnector->getMainUser();

    auto *page = new UserPage(&mainUser->photoName, mainUser->name + " \n" + mainUser->lastName, mainUser->lastVisit,
                              mainUser->status, webConnector, nullptr, mainUser->id);

    page->show();

    QNetworkRequest request = webConnector->createRequest("https://barybians.ru/api/posts", WebConnector::GET_FEED);

    webConnector->sendRequest(request, WebConnector::GET_FEED);
    hide();

    QNetworkRequest request1 = webConnector->createRequest("https://barybians.ru/api/users", WebConnector::ALL_USERS);

    webConnector->sendRequest(request1, WebConnector::ALL_USERS);

//    auto *window = new DialogWindow(webConnector, 4);

    FeedPage *feedPage = nullptr;
    connect(webConnector, &WebConnector::usersList, this, [webConnector, feedPage]() mutable {
        auto *userFeed = new UserFeed(webConnector);
        userFeed->show();
        feedPage = new FeedPage(webConnector);
        feedPage->setAttribute(Qt::WA_DeleteOnClose);
        feedPage->show();
    });
    connect(feedPage, &FeedPage::destroyed, this, [feedPage]() mutable {
        delete feedPage;
    });
    auto mainLayout = new QVBoxLayout();
    auto navBar = new NavigationBar();

    mainLayout->addWidget(navBar);
//    setLayout(mainLayout);
    auto widget = new QWidget();

    widget->setLayout(mainLayout);

    setCentralWidget(widget);



//    connect(page, &UserPage::windowHidden, this, [this](){
//       show();
//    });
}

MainWindow::~MainWindow()
= default;
