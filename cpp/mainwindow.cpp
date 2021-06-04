#include "headers/mainwindow.h"
#include "headers/webconnector.h"

#include <QGuiApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QtQml/QQmlApplicationEngine>

#include <QtCore/QSettings>
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

MainWindow::MainWindow(QWidget *parent, WebConnector *webConnector) : QMainWindow(parent)
{
    setWindowTitle("Барыбинцы");
    User *mainUser = webConnector->getMainUser();

    UserPage *page = new UserPage(&mainUser->photoName, mainUser->name + mainUser->lastName, mainUser->lastVisit, mainUser->status, webConnector);

    page->show();
};

MainWindow::~MainWindow()
{
}
