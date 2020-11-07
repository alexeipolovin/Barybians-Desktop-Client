#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include "headers/webconnector.h"

#include <QObject>



class LoginController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString login READ getLogin WRITE setLogin NOTIFY loginChanged)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)
public:
    LoginController();
    ~LoginController();

    WebConnector *webConnector;

    QString getLogin() const;
    QString getPassword() const;

    void setLogin(const QString &login);
    void setPassword(const QString &password);

public slots:
    void sendRequest();

    void checkReply();

signals:
    void passwordChanged();
    void loginChanged();
    void loginSucces(bool succes);
private:
    QString _login;
    QString _password;
};

#endif // LOGINCONTROLLER_H
