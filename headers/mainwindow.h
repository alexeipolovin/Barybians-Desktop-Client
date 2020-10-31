#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "webconnector.h"

#include <QLineEdit>
#include <QMainWindow>
#include <QStackedWidget>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    User *mainUser;
    QTextEdit *textEdit;
    WebConnector *webConnector;
    QStackedWidget *maincontent;
public slots:
//    void writePost();
    void writePost();
    void writeMe();
    void getAllUsers();
    void getAllPosts();
    void getAllDialogs();
    void createGraz();
};
#endif // MAINWINDOW_H
