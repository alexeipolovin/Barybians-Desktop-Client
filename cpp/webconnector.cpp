#include "headers/webconnector.h"
#include <QHttpMultiPart>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QFile>
#include <QException>
#include <QPixmap>
#include <QThread>
#include <QSettings>
#include <utility>


const QByteArray HEADER_APP_TYPE = "application/x-www-form-urlencoded";
const QByteArray AUTHORIZATION = "Authorization";

/**
  * @brief WebConnector::WebConnector
  *
  * @author Polovin Alexei (alexeipolovin@gmail.com)
  *
  * Класс, отвечающий за взаимодействие с REST API https://barybians.ru/api/
*/

WebConnector::WebConnector(bool showDebug)
{
    messagesList = new QVector<Message*>;
    mainUser = new User();
    this->showDebug = showDebug;
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


void WebConnector::standartHeader(QNetworkRequest &request)
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
 * Подготавливает и возвращает запрос
*/

QNetworkRequest WebConnector::createRequest(const QString &url, WebConnector::REQUEST_TYPE type)
{
    QNetworkRequest request;

    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, HEADER_APP_TYPE);

    switch (type) {
        case AUTH: {
            this->userState = (bool) "12";
            request.setRawHeader(("username:" + this->LOGIN).toUtf8(), ("password:" + this->PASSWORD).toUtf8());
            break;
        }
        case ALL_USERS: {
            standartHeader(request);
            break;
        }
        case ALL_MESSAGES: {
            standartHeader(request);
            break;

        }
        case GET_FEED: {
            standartHeader(request);
            break;
        }
        case CURRENT_USER: {
            standartHeader(request);
            break;
        }
        case WRITE_POST: {
            standartHeader(request);
            break;
        }
        case GET_DIALOGS: {
            standartHeader(request);
            break;
        }
        case DOWNLOAD_PHOTO: {
            standartHeader(request);
            break;
        }
        case DIALOG_WITH: {
            standartHeader(request);
            break;
        }
        default: {
            if(showDebug)
                qDebug() << "Unknown request";
            break;
        }
    }
    return request;
}

void WebConnector::makeAuth()
{
    QNetworkRequest request = this->createRequest("https://barybians.ru/api/auth", WebConnector::AUTH);
    this->sendRequest(request, WebConnector::AUTH);
}


void WebConnector::cachePhoto(QNetworkReply *reply_photo, const QNetworkRequest& request)
{
    QByteArray array = reply_photo->readAll();
    QString string = request.url().toString();
    QString photoName = string.split("/").last();
    if(showDebug)
        qDebug() << photoName;
    if(!QFile::exists(photoName)) {
        QFile file(photoName);
        if (file.open(QFile::ReadWrite)) {
            file.write(array);
        }
    }
}

QJsonObject WebConnector::parseReply(QNetworkReply &reply, WebConnector::REQUEST_TYPE type, const QNetworkRequest& request)
{
    //TODO: Вынести это в отдельный класс
    QJsonObject root;
    switch (type) {
    case ALL_USERS: {
        QByteArray array = reply.readAll();
        QJsonDocument document = QJsonDocument::fromJson(array);
        QJsonArray jsonArray = document.array();
        QJsonObject firstObject = jsonArray.takeAt(1).toObject();
        for(auto i : jsonArray)
        {
            if(showDebug)
            qDebug() << i;
            User *user = new User();
            QJsonObject obj = i.toObject();
            user->name = obj.find("firstName").value().toString();
            if(showDebug)
            qDebug() << user->name;
            user->lastName = obj.find("lastName").value().toString();
            user->photoName = obj.find("photo").value().toString();
            if(showDebug)
            qDebug() << "Photo name:" << user->photoName;
            user->id = obj.find("id").value().toInt();
            user->lastVisit = obj.find("lastVisit").value().toString();
            if(showDebug)
                qDebug() << "Last Visit:" << user->lastVisit;
            QNetworkRequest networkRequest = createRequest("https://barybians.ru/avatars/" + user->photoName, WebConnector::DOWNLOAD_PHOTO);
            this->photoUrl = user->photoName;
            sendRequest(networkRequest, WebConnector::DOWNLOAD_PHOTO);
            userList->push_back(user);
            userPhotoMap.insert(user->photoName, user->photoName);
        }
        emit usersList();
        this->userState = true;
        break;
    }


    //TODO: придумать как реализовать сортировку кто отправил кто получил для выравнивания в окне диалога
    case DIALOG_WITH: {
        QByteArray array = reply.readAll();
        QJsonDocument document = QJsonDocument::fromJson(array);
        QJsonArray jsonArray = document.object().find("messages")->toArray();
        qDebug() << document;
        for(auto i: jsonArray)
        {
            if(showDebug)
                qDebug() << i;
            auto message = new Message();
            QJsonObject obj = i.toObject();
//            obj.find("secondUser").value().toObject().find("id");
            message->id = document.object().find("secondUser").value().toObject().find("id")->toInt();
            if(showDebug)
                qDebug() << "Message User Id:" << message->id;
            message->text = obj.find("text").value().toString();
            if(showDebug)
                qDebug() << "Message text:" << message->text;
            messagesList->push_back(message);
        }
        emit messageListReceived();
        break;
    }

    case AUTH: {
        QJsonDocument document = QJsonDocument::fromJson(reply.readAll());
        root = document.object();
        QJsonObject user =  root.find("user").value().toObject();
        if(showDebug)
            qDebug() << root;

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

        if(showDebug)
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

        QJsonDocument document = QJsonDocument::fromJson(array);

        QJsonArray jsonArray = document.array();

        QJsonObject firstObject = jsonArray.takeAt(1).toObject();
        QString val = firstObject.find("title").value().toString();
        if(showDebug)
        qDebug () << val;
        int n = 0;
        for (auto i:jsonArray)
        {
            if(showDebug)
            qDebug () << n;
            n++;
            Post *post = new Post();

            post->name = i.toObject().find("author").value().toObject().find("firstName")->toString() + "\n" + i.toObject().find("author").value().toObject().find("lastName")->toString();
            post->photoPath = "https://barybians.ru/avatars/" + i.toObject().find("author").value().toObject().find("photo")->toString();
            this->photoUrl = i.toObject().find("author").value().toObject().find("photo")->toString();
            post->userId = i.toObject().find("author").value().toObject().find("id")->toInt();
            QNetworkRequest networkRequest = this->createRequest(post->photoPath, WebConnector::DOWNLOAD_PHOTO);
            this->sendRequest(networkRequest, WebConnector::DOWNLOAD_PHOTO);
            post->title = i.toObject().find("title")->toString();
            post->text = i.toObject().find("text")->toString();

            feed->push_back(post);
        }

        emit feedOk();

        break;
    }
    case DOWNLOAD_PHOTO: {
        QByteArray imageData = reply.readAll();

        QFile *newDoc;
            QString photoName = request.url().toString().split("/").last();
            newDoc = new QFile(photoName);
            if(!QFile::exists(photoName)) {
                if (newDoc->open(QIODevice::WriteOnly))
                    newDoc->write(imageData);
            }
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

        if(showDebug)
        qDebug() << document.object();

        break;
    }
    case GET_DIALOGS: {
        QByteArray array = reply.readAll();
        if(showDebug)
        qDebug() << QString(array);

        array.clear();

        break;
    }
        case ALL_MESSAGES:
            break;
    }
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

QVector<Message*>* WebConnector::getMessagesList() {
    return this->messagesList;
}

QString WebConnector::getToken() const
{
    return this->token;
}


User& WebConnector::getMainUser() const
{
    return *this->mainUser;
}


/**
  * @brief WebConnector::sendRequest
  *
  * @param request
  * @param type
  *
  * @author Polovin Alexei (alexeipolovin@gmail.com)
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
    case ALL_MESSAGES:
        reply = manager->get(request);
        break;
    case DIALOG_WITH:
        reply = manager->get(request);
        break;
    }
    connect(reply, &QNetworkReply::finished, this, [this, reply, type, request]() {
        QJsonObject obj = parseReply(*reply, type, request);
        reply->deleteLater();
    });

}
