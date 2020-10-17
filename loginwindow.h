#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#pragma once
#include <QLineEdit>
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include "webconnector.h"

class LoginWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);

    void resizeEvent(QResizeEvent *event);
    void checkMainWindow();

    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;

    WebConnector *webConnector;

    QSqlDatabase db;

public slots:
    void openMainWindow();
signals:

};

#endif // LOGINWINDOW_H
