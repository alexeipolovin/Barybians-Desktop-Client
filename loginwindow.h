#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#pragma once
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QtSql/QSqlDatabase>
#include "webconnector.h"

class LoginWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);

    void resizeEvent(QResizeEvent *event);
    void checkMainWindow();

    QLabel *passwordLabel;
    QLabel *loginLabel;

    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;

    QPushButton *loginButton;

    QSqlDatabase db;

    WebConnector *webConnector;

    bool ifExist;

public slots:
    void openMainWindow();
signals:

};

#endif // LOGINWINDOW_H
