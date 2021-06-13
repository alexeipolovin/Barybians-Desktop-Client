#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "webconnector.h"

#include <QLineEdit>
#include <QMainWindow>
#include <QStackedWidget>
#include <QTextEdit>

class MainWindow : public QMainWindow {
Q_OBJECT

    MainWindow(QWidget *parent, WebConnector &webConnector);


public:
    MainWindow(QWidget *parent = nullptr, WebConnector *webConnector = nullptr);

    ~MainWindow();

};

#endif // MAINWINDOW_H
