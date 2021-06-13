#include <headers/logincontroller.h>
#include <headers/webconnector.h>

LoginController::LoginController() {
    webConnector = new WebConnector();
}

LoginController::~LoginController() {}


void LoginController::checkReply() {
    if (this->webConnector->getToken() != "false") {
        qDebug() << "LOGIN SUCCES!!!!";
        QSettings *settings = new QSettings("login.ini", QSettings::IniFormat);
        settings->setValue("login", _login);
        settings->setValue("password", _password);
        settings->setValue("token", webConnector->getToken());
        emit loginSucces(true);
    } else {

        qDebug() << "LOGIN FAILES";
        emit loginSucces(false);
    }
}


void LoginController::setPassword(const QString &password) {
    _password = password;
}

void LoginController::setLogin(const QString &login) {
    _login = login;
}

QString LoginController::getLogin() const {
    return _login;
}

QString LoginController::getPassword() const {
    return _password;
}

void LoginController::sendRequest() {
    webConnector->setLoginAndPassword(_login, _password);

    webConnector->makeAuth();

    connect(webConnector, &WebConnector::valueChanged, this, &LoginController::checkReply);
}
