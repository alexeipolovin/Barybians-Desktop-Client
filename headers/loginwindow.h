#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QtCore/QSettings>
#include "webconnector.h"

class LoginWindow : public QMainWindow {
Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);

    void resizeEvent(QResizeEvent *event) override;

    void checkMainWindow();

    QLabel *passwordLabel;
    QLabel *loginLabel;

    QSettings *settings;

    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;

    QPushButton *loginButton;

    QString username;
    QString password;

    WebConnector *webConnector;

    bool tokenStatus;

    bool ifExist{};
public slots:

    void openMainWindow();

signals:
};

#endif // LOGINWINDOW_H
