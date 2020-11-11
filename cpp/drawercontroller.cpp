#include <QString>

#include <headers/drawercontroller.h>
#include <headers/webconnector.h>

DrawerController::DrawerController()
{
    webConnector = new WebConnector();
    if(webConnector->checkAuth()) {
        webConnector->makeAuth();
    }

    connect(webConnector, &WebConnector::valueChanged, this, &DrawerController::checkName);
}
DrawerController::~DrawerController(){}

void DrawerController::checkName()
{
    setName(webConnector->mainUser->name + " " + webConnector->mainUser->lastName);
    setStatus(webConnector->mainUser->status);
    setPhoto(webConnector->mainUser->getPhotoName());
    emit nameChanged();
    emit statusChanged();
    emit photoChanged();
}

QString DrawerController::getPhoto() const
{
    return photo;
}

void DrawerController::setPhoto(const QString &value)
{
    photo = value;
}

QString DrawerController::getStatus() const
{
    return status;
}

void DrawerController::setStatus(const QString &value)
{
    status = value;
}

QString DrawerController::getName() const
{
    return name;
}

void DrawerController::setName(const QString &value)
{
    name = value;
}

void anoterRandomFuncWithoutConf()
{
    printf("%d", 10);
    for(int i = 0; i < 100; i++) {
        qDebug() << "Hello, World";

    }
}
