#include "headers/mainwindow.h"
#include "headers/webconnector.h"

#include <QGuiApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtQml/QQmlApplicationEngine>

#include <QtCore/QSettings>
#include <headers/userpage.h>
#include <headers/FeedPage.h>

/**
  * @brief MainWindow::MainWindow
  *
  * @param *parent
  *
  * @author Polovin Alexei (alexeipolovin@gmail.com)
  *
  * Класс отвечающий за главное окно, основная цель отрисовать базовый интерфейс и дополнить его одной из страниц
*/

MainWindow::MainWindow(QWidget *parent, WebConnector *webConnector) : QMainWindow(parent)
{
    setWindowTitle("Барыбинцы");
    User *mainUser = webConnector->getMainUser();

    auto *page = new UserPage(&mainUser->photoName, mainUser->name + "\n" + mainUser->lastName, mainUser->lastVisit, mainUser->status, webConnector);

    page->show();

    QNetworkRequest request = webConnector->createRequest("https://barybians.ru/api/posts", WebConnector::GET_FEED);

    webConnector->sendRequest(request, WebConnector::GET_FEED);
    hide();

    QNetworkRequest request1 = webConnector->createRequest("https://barybians.ru/api/users", WebConnector::ALL_USERS);

    webConnector->sendRequest(request1, WebConnector::ALL_USERS);

    connect(webConnector, &WebConnector::usersList, this, [this, webConnector](){
        auto *feedPage = new FeedPage(webConnector);
        feedPage->show();
    });



//    connect(page, &UserPage::windowHidden, this, [this](){
//       show();
//    });
};

MainWindow::~MainWindow()
{
}
