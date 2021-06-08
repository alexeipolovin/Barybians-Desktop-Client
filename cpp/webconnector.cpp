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
#include <QSettings>
#include <utility>


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
    feed = new QVector<Post*>;
    userList = new QVector<User*>;
    settings = new QSettings("login.ini", QSettings::IniFormat);

    this->token = "";

    manager = new QNetworkAccessManager();
}

bool WebConnector::checkAuth()
{
    QString login = settings->value("login").toString();
    QString password = settings->value("password").toString();

    if(login != "" && password != "")
    {
        LOGIN = login;
        PASSWORD = password;
        token = settings->value("token").toString();
        bearerToken = ("Bearer  " + token).toUtf8();
        return true;
    } else {
        return false;
    }
}

void WebConnector::setLoginAndPassword(QString login, QString password)
{
    this->LOGIN = qMove(login);
    this->PASSWORD = qMove(password);
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
    case GET_FEED: {
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

void WebConnector::makeAuth()
{
    QNetworkRequest request = this->createRequest("https://barybians.ru/api/auth", WebConnector::AUTH);
    this->sendRequest(request, WebConnector::AUTH);
}


void WebConnector::cachePhoto()
{
    if(this->userState)
    {
        for(auto i:*userList)
        {
            if(!QFile::exists(i->photoName)) {
                QNetworkRequest request = createRequest("https://barybians.ru/avatars/" + i->photoName,
                                                        WebConnector::DOWNLOAD_PHOTO);
                sendRequest(request, WebConnector::DOWNLOAD_PHOTO);
            }
        }
    }
}

QJsonObject WebConnector::parseReply(QNetworkReply &reply, WebConnector::REQUEST_TYPE type)
{
    //TODO: Вынести это в отдельный класс
    QJsonObject root;
//    qDebug() << reply.readAll();
    switch (type) {
    // Неверный запрос?
    case ALL_USERS: {
        QByteArray array = reply.readAll();
//        qDebug() << array;
//        qDebug () << array;
        QJsonDocument document = QJsonDocument::fromJson(array);
//        qDebug() << document;
        QJsonArray jsonArray = document.array();
//        qDebug() << jsonArray;

        QJsonObject firstObject = jsonArray.takeAt(1).toObject();
//        qDebug() << firstObject;

        QString val = firstObject.find("title").value().toString();

        for(auto i : jsonArray)
        {
            qDebug() << i;
            User *user = new User();
            QJsonObject obj = i.toObject();
            user->name = obj.find("firstName").value().toString();
            qDebug() << user->name;
            user->lastName = obj.find("lastName").value().toString();
            user->photoName = obj.find("photo").value().toString();
            qDebug() << "Photo name:" << user->photoName;
            user->id = obj.find("id").value().toInt();
            QNetworkRequest request = createRequest("https://barybians.ru/avatars/" + user->photoName, WebConnector::DOWNLOAD_PHOTO);
            this->photoUrl = user->photoName;
            sendRequest(request, WebConnector::DOWNLOAD_PHOTO);
            userList->push_back(user);
        }
        emit usersList();
        this->userState = true;
        break;
    }
    case AUTH: {
        QJsonDocument document = QJsonDocument::fromJson(reply.readAll());
        root = document.object();

        QJsonObject user =  root.find("user").value().toObject();

        qDebug() << root;
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
        } else {
            settings->setValue("login", this->LOGIN);
            settings->setValue("password", this->PASSWORD);
            settings->setValue("token", this->token);
            bearerToken = ("Bearer " + token).toUtf8();
        }
        emit valueChanged(this->token);
        break;
    }
    case GET_FEED: {
        QByteArray array = reply.readAll();
//        qDebug () << array;
        QJsonDocument document = QJsonDocument::fromJson(array);
//        qDebug() << document;
        QJsonArray jsonArray = document.array();
//        qDebug() << jsonArray;

        QJsonObject firstObject = jsonArray.takeAt(1).toObject();
//        qDebug() << firstObject;

        QString val = firstObject.find("title").value().toString();
        qDebug () << val;
        int n = 0;
        for (auto i:jsonArray)
        {
//            qDebug () << i;
            qDebug () << n;
            n++;
            Post *post = new Post();

            post->name = i.toObject().find("author").value().toObject().find("firstName")->toString() + "\n" + i.toObject().find("author").value().toObject().find("lastName")->toString();
            post->photoPath = "https://barybians.ru/avatars/" + i.toObject().find("author").value().toObject().find("photo")->toString();
            this->photoUrl = i.toObject().find("author").value().toObject().find("photo")->toString();
            post->userId = i.toObject().find("author").value().toObject().find("id")->toInt();
            QNetworkRequest request = this->createRequest(post->photoPath, WebConnector::DOWNLOAD_PHOTO);
            this->sendRequest(request, WebConnector::DOWNLOAD_PHOTO);
            post->title = i.toObject().find("title")->toString();
            post->text = i.toObject().find("text")->toString();

            feed->push_back(post);

//            qDebug() << i.toObject().find("title").value().toString();
        }

        emit feedOk();
//        qDebug() << array;

        break;
    }
    case DOWNLOAD_PHOTO: {
        QByteArray imageData = reply.readAll();

        QFile *newDoc;

        try {
            newDoc = new QFile(this->photoUrl);
            if(newDoc->open(QIODevice::WriteOnly))
                newDoc->write(imageData);
        } catch (const QException &e) {

            qDebug() << e.what();
        }
        qDebug() << QString(imageData);

        QPixmap pm;
        pm.loadFromData(imageData);

        this->lastPixmap = pm;
        emit pixmapUpdated();
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

QVector<Post*>* WebConnector::getFeed()
{
    return this->feed;
}

QVector<User*>* WebConnector::getUsersList()
{
    return this->userList;
}

QString WebConnector::getToken() const
{
    return this->token;
}


User* WebConnector::getMainUser() const
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
        auto *params = new QUrlQuery();
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
        auto *params = new QUrlQuery();
        params->addQueryItem("title", "Title");
        params->addQueryItem("text", "Text");

        reply = manager->post(request, params->toString().toUtf8());

        break;
    }
    case DOWNLOAD_PHOTO: {
        reply = manager->get(request);

        break;
    }
    case GET_FEED: {
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
