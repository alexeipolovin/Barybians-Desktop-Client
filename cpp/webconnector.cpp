#include "headers/webconnector.h"
#include "headers/Data.h"
#include <QHttpMultiPart>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QFile>
#include <QException>
#include <QPixmap>
#include <QJsonDocument>
#include <QString>
#include <QThread>


#define HEADER_APP_TYPE "application/x-www-form-urlencoded"
#define AUTHORIZATION "Authorization"

/**
  * @brief WebConnector::WebConnector
  *
  * @author Polovin Alexei (alexeipolovin@gmail.com)
  *
  * Класс, отвечающий за взаиомдействие с REST API https://barybians.ru/api/
*/

WebConnector::WebConnector()
{
    this->token = "";

    manager = new QNetworkAccessManager();
}


void WebConnector::setLoginAndPassword(QString login, QString password)
{
    this->LOGIN = login;
    this->PASSWORD = password;

    QFile tempName("tempName.brb");
    QFile tempLastName("tempLastName.brb");

    if(tempName.open(QFile::ReadWrite) && tempLastName.open(QFile::ReadWrite)) {
        tempName.write(this->LOGIN.toUtf8());
        tempLastName.write(this->PASSWORD.toUtf8());
    }
}


void WebConnector::setStandartHeader(QNetworkRequest &request)
{
    request.setRawHeader(AUTHORIZATION, this->bearerToken);
}

/**
 * @brief WebConnector::createRequest
 *
 * @param url
 * @param type
 *
 * @author Polovin Alexei (alexeipolovin@gmail.com)
 * @returns QNetworkRequest reply
 *
 * Подгатавливает и возвращает запрос
*/

QNetworkRequest WebConnector::createRequest(const QString &url, WebConnector::REQUEST_TYPE type)
{
    QNetworkRequest request;

    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, HEADER_APP_TYPE);

    switch (type)
    {
    case AUTH: {
        request.setRawHeader(("username:" + this->LOGIN).toUtf8(), ("password:" + this->PASSWORD).toUtf8());
        //Придумать зачем я создал сигнал?
//        emit valueChanged(this->token);
        break;
        }
    case ALL_USERS: {
//        request.setRawHeader(AUTHORIZATION, this->bearerToken);
        setStandartHeader(request);
        break;
    }
    case ALL_POSTS: {
//        request.setRawHeader(AUTHORIZATION, this->bearerToken);
        setStandartHeader(request);
        break;
    }
    case CURRENT_USER: {
//        request.setRawHeader(AUTHORIZATION, this->bearerToken);
//        goto set_standart_header;
        setStandartHeader(request);
        break;
    }
    case WRITE_POST: {
//        request.setRawHeader(AUTHORIZATION, this->bearerToken);
//        goto set_standart_header;
        setStandartHeader(request);
        break;
    }
    case GET_DIALOGS: {
//        request.setRawHeader(AUTHORIZATION, this->bearerToken);
//        goto set_standart_header;
        setStandartHeader(request);
        break;
    }
    case DOWNLOAD_PHOTO: {
//        goto set_standart_header;
        setStandartHeader(request);
        break;
    }
    };
    return request;
}

bool WebConnector::isTokenExist()
{
    QFile file("temp.brb");

    QFile fileName("tempName.brb");

    QFile fileLastName("tempLastName.brb");

    if(file.open(QFile::ReadWrite) && fileName.open(QFile::ReadWrite) && fileLastName.open(QFile::ReadWrite))
    {
        this->token = QString(file.readAll());
        this->LOGIN = QString(fileName.readAll());
        this->PASSWORD = QString(fileLastName.readAll());

        return true;
    }

    return false;

}


bool WebConnector::authIfExist()
{
    if(this->isTokenExist())
    {
        this->makeAuth();
        return true;
    } else {
        return false;
    }
}

void WebConnector::makeAuth()
{
    QNetworkRequest request = this->createRequest("https://barybians.ru/api/auth", WebConnector::AUTH);
    this->sendRequest(request, WebConnector::AUTH);
}

QJsonObject WebConnector::parseReply(QNetworkReply &reply, WebConnector::REQUEST_TYPE type)
{
    //TODO: Вынести это в отдельный класс
    QJsonObject root;
//    qDebug() << reply.readAll();
    switch (type) {
    // Неверный запрос?
    case ALL_USERS: {
        QJsonDocument document = QJsonDocument::fromJson(reply.readAll());
        QJsonObject user = root.find("user").value().toObject();

        break;
    }
    case AUTH: {
        QFile file("temp.brb");
        QJsonDocument document = QJsonDocument::fromJson(reply.readAll());
        root = document.object();

        QJsonObject user =  root.find("user").value().toObject();

        qDebug() << root;
        QThread *thread = new QThread();
        thread->start();
        mainUser = new User();
        mainUser->name = user.find("firstName").value().toString();
        mainUser->lastName = user.find("lastName").value().toString();
        mainUser->status = user.find("status").value().toString();
        mainUser->id = user.find("userId").value().toInt();
        mainUser->photoName = user.find("photo").value().toString();
        mainUser->lastVisit = user.find("lastVisit").value().toString();
        mainUser->printUserData();

        QNetworkRequest getPhoto = this->createRequest("https://barybians.ru/avatars/" + user.find("photo").value().toString(), WebConnector::DOWNLOAD_PHOTO);

        this->sendRequest(getPhoto, WebConnector::DOWNLOAD_PHOTO);
        this->token = root.find("token").value().toString();

        qDebug() << this->token;

        if(this->token == "")
        {
            this->token = "false";
        }

        if(this->bearerToken.length() < 170)
            this->bearerToken.push_back("Bearer " + this->token.toUtf8());
        file.write(this->token.toUtf8());

        emit valueChanged(this->token);
        break;
    }
    case ALL_POSTS: {
        QByteArray array = reply.readAll();

        QJsonDocument document = QJsonDocument::fromJson(reply.readAll());

        QJsonArray jsonArray = document.array();

        QJsonObject firstObject = jsonArray.takeAt(1).toObject();

        QString val = firstObject.find("title").value().toString();

        qDebug() << array;

        break;
    }
    case DOWNLOAD_PHOTO: {
        QByteArray imageData = reply.readAll();

        QFile *newDoc;

        try {
            newDoc = new QFile("hello.png");
            if(newDoc->open(QIODevice::WriteOnly))
                newDoc->write(imageData);
        } catch (const QException e) {

            qDebug() << e.what();
        }
        qDebug() << QString(imageData);

        QPixmap pm;
        pm.loadFromData(imageData);

        this->mainUser->profilePhoto = pm.scaled(128,128);
        break;
    }
    case WRITE_POST: {
        QJsonDocument document = QJsonDocument::fromJson(reply.readAll());
        root = document.object();

        Post *post = new Post();

        post->id = root.find("id").value().toInt();
        post->title = root.find("title").value().toString();
        post->text = root.find("text").value().toString();
        post->edited = root.find("edited").value().toInt();
        post->date = root.find("date").value().toString();
        post->printData();

        break;
    }
    case CURRENT_USER: {
        QJsonDocument document = QJsonDocument::fromJson(reply.readAll());

        qDebug() << document.object();

        break;
    }
    case GET_DIALOGS: {
        QByteArray array = reply.readAll();

        qDebug() << QString(array);

        array.clear();

        break;
    }
    };
    reply.deleteLater();
    return root;
}

QString WebConnector::getToken()
{
    return this->token;
}


User* WebConnector::getMainUser()
{
    return this->mainUser;
}

/**
  * @brief WebConnector::sendRequest
  *
  * @param request
  * @param type
  *
  * @author Polovin Alexei (alexeipolovin@gmai.com)
  *
  * Делает запрос к серверу
  *
*/


void WebConnector::sendRequest(QNetworkRequest &request, WebConnector::REQUEST_TYPE type)
{
    QNetworkReply *reply;
    switch (type) {
    case AUTH: {
        QUrlQuery *params = new QUrlQuery();
        params->addQueryItem("username", LOGIN);
        params->addQueryItem("password", PASSWORD);

        reply = manager->post(request, params->toString().toUtf8());

        break;
    }
    case ALL_USERS: {
        reply = manager->get(request); //??

        break;
    }
    case WRITE_POST: {
        QUrlQuery *params = new QUrlQuery();
        params->addQueryItem("title", "Title");
        params->addQueryItem("text", "Text");

        reply = manager->post(request, params->toString().toUtf8());

        break;
    }
    case DOWNLOAD_PHOTO: {
        reply = manager->get(request);

        break;
    }
    case ALL_POSTS: {
        reply = manager->get(request);

        break;
    }
    case CURRENT_USER: {
        reply = manager->get(request);

        break;
    }
    case GET_DIALOGS: {
        reply = manager->get(request);

        break;
    }
    };
    connect(reply, &QNetworkReply::finished, this, [this, reply, type]() {
        QJsonObject obj = parseReply(*reply, type);
        reply->deleteLater();
    });
}
