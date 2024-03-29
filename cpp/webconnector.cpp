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
  * @author Polovin Alexei
  *
  * @param bool showDebug
  *
  * @description Класс, отвечающий за взаимодействие с REST API https://barybians.ru/api/
*/

WebConnector::WebConnector(bool showDebug) {
    messagesList = new QMap<int, QVector<Message *>>;
    mainUser = new User();
    this->showDebug = showDebug;
    feed = new QVector<Post *>;
    userList = new QVector<User *>;
    settings = new QSettings("login.ini", QSettings::IniFormat);

    this->token = "";

    manager = new QNetworkAccessManager();
}


/**
 * @brief WebConnector::checkAuth
 *
 * @author Polovin Alexei
 *
 * @param none
 *
 * Проверка наличия сохранённого логина и пароля в настройках
 * */
bool WebConnector::checkAuth() {
    QString login = settings->value("login").toString();
    QString password = settings->value("password").toString();

    if (login != "" && password != "") {
        LOGIN = login;
        PASSWORD = password;
        token = settings->value("token").toString();
        bearerToken = ("Bearer  " + token).toUtf8();
        return true;
    } else {
        return false;
    }
}

/**
 * @brief WebConnector::checkAuth
 *
 * @author Polovin Alexei
 *
 * @param QString login
 * @param QString password
 *
 * Проверка наличия сохранённого логина и пароля в настройках
 * */

void WebConnector::setLoginAndPassword(QString login, QString password) {
    this->LOGIN = qMove(login);
    this->PASSWORD = qMove(password);
}


inline void WebConnector::standartHeader(QNetworkRequest &request) {
    request.setRawHeader(AUTHORIZATION, this->bearerToken);
}

void WebConnector::writePost(QString title, QString text) {
    QNetworkRequest request = this->createRequest("https://barybians.ru/api/posts&title=" + title + "&text=" + text, WRITE_POST);
    sendPostRequest(request, WRITE_POST);
}

void WebConnector::sendPostRequest(QNetworkRequest request, WebConnector::REQUEST_TYPE type) {
    QByteArray array;
    QNetworkReply *reply;
    switch (type) {
    case WebConnector::AUTH:
        break;
    case WebConnector::CURRENT_USER:
        break;
    case WebConnector::ALL_USERS:
        break;
    case WebConnector::GET_DIALOGS:
        break;
    case WebConnector::DOWNLOAD_PHOTO:
        break;
    case WebConnector::GET_FEED:
        break;
    case WebConnector::ALL_MESSAGES:
        break;
    case WebConnector::DIALOG_WITH:
        break;
    case WebConnector::SEND_MESSAGE:
        break;
    case WRITE_POST:
            reply = manager->post(request, array);
            break;
    }

    connect(reply, &QNetworkReply::finished, this, [reply]() {
       qDebug() << reply->readAll();
    });
}

/**
 * @brief WebConnector::createRequest
 *
 * @param const QString url
 * @param WebConnector::REQUEST_TYPE type
 *
 * @author Polovin Alexei
 *
 * @returns QNetworkRequest reply
 *
 * Подготавливает и возвращает запрос
*/

QNetworkRequest WebConnector::createRequest(const QString &url, WebConnector::REQUEST_TYPE type) {
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
            if (showDebug)
                qDebug() << "Unknown request";
            break;
        }
    }
    return request;
}

/**
 * @brief WebConnector::makeAuth
 *
 * @author Polovin Alexei
 *
 * @param none
 *
 * Произвести аутентификацию
 * */

void WebConnector::makeAuth() {
    QNetworkRequest request = this->createRequest("https://barybians.ru/api/auth", WebConnector::AUTH);
    this->sendRequest(request, WebConnector::AUTH);
}

/**
 * @brief WebConnector::cachePhoto
 *
 * @author Polovin Alexei
 *
 * @param QNetworkReply *reply_photo
 * @param  const QNetworkRequest &request
 *
 * Проверка наличия сохранённого логина и пароля в настройках
 * */

void WebConnector::cachePhoto(QNetworkReply *reply_photo, const QNetworkRequest &request) {
    QByteArray array = reply_photo->readAll();
    QString string = request.url().toString();
    QString photoName = string.split("/").last();
    if (showDebug)
        qDebug() << photoName;
    if (!QFile::exists(photoName)) {
        QFile file(photoName);
        if (file.open(QFile::ReadWrite)) {
            file.write(array);
        }
    }
}

QJsonObject
WebConnector::parseReply(QNetworkReply &reply, WebConnector::REQUEST_TYPE type, const QNetworkRequest &request) {
    //TODO: Вынести это в отдельный класс
    QJsonObject root;
    switch (type) {
        case ALL_USERS: {
            QByteArray array = reply.readAll();
            QJsonDocument document = QJsonDocument::fromJson(array);
            QJsonArray jsonArray = document.array();
            QJsonObject firstObject = jsonArray.takeAt(1).toObject();
            for (const auto &i : qAsConst(jsonArray)) {
                if (showDebug)
                    qDebug() << i;
                User *user = new User();
                QJsonObject obj = i.toObject();
                user->name = obj.find("firstName").value().toString();
                if (showDebug)
                    qDebug() << user->name;
                user->lastName = obj.find("lastName").value().toString();
                user->photoName = obj.find("photo").value().toString();
                if (showDebug)
                    qDebug() << "Photo name:" << user->photoName;
                user->id = obj.find("id").value().toInt();
                user->lastVisit = obj.find("lastVisit").value().toString();
                user->status = obj.find("status").value().toString();
                if (showDebug)
                    qDebug() << "Last Visit:" << user->lastVisit;
                if (!QFile::exists(user->photoName)) {
                    qDebug() << user->photoName;
                    QNetworkRequest networkRequest = createRequest("https://barybians.ru/avatars/" + user->photoName,
                                                                   WebConnector::DOWNLOAD_PHOTO);
                    this->sendRequest(networkRequest, WebConnector::DOWNLOAD_PHOTO);
                }
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
            QVector<Message *> *temp_vector = new QVector<Message *>;
            qDebug() << document;
            int id = 0;
            for (const auto &i: qAsConst(jsonArray)) {
                if (showDebug)
                    qDebug() << i;
                auto message = new Message();
                QJsonObject obj = i.toObject();
                message->id = obj.find("receiverId").value().toInt();
                if (showDebug)
                    qDebug() << "Message User Id:" << message->id;
                message->text = obj.find("text").value().toString();
                if (showDebug)
                    qDebug() << "Message text:" << message->text;
                temp_vector->push_back(message);
                qDebug() << "Temp Vector Length:" << temp_vector->length();
                id = message->id;
            }
            qDebug() << "New Id is:" << id;
            if (!this->messagesList->contains(id))
                this->messagesList->insert(id, *temp_vector);
            emit messageListReceived();
            qDeleteAll((*temp_vector));
            delete temp_vector;
            break;
        }

        case AUTH: {
            QJsonDocument document = QJsonDocument::fromJson(reply.readAll());
            root = document.object();
            QJsonObject user = root.find("user").value().toObject();
            if (showDebug)
                qDebug() << root;

            mainUser->name = user.find("firstName").value().toString();
            mainUser->lastName = user.find("lastName").value().toString();
            mainUser->status = user.find("status").value().toString();
            mainUser->id = user.find("userId").value().toInt();
            mainUser->photoName = user.find("photo").value().toString();
            mainUser->lastVisit = user.find("lastVisit").value().toString();
            mainUser->printUserData();

            QNetworkRequest getPhoto = this->createRequest(
                    "https://barybians.ru/avatars/" + user.find("photo").value().toString(),
                    WebConnector::DOWNLOAD_PHOTO);

            this->sendRequest(getPhoto, WebConnector::DOWNLOAD_PHOTO);
            this->token = root.find("token").value().toString();

            if (showDebug)
                qDebug() << this->token;

            if (this->token == "") {
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
            if (showDebug)
                qDebug() << val;
            int n = 0;
            for (const auto &i:qAsConst(jsonArray)) {
                if (showDebug)
                    qDebug() << n;
                n++;
                Post *post = new Post();

                post->name = i.toObject().find("author").value().toObject().find("firstName")->toString() + "\n" +
                             i.toObject().find("author").value().toObject().find("lastName")->toString();
                post->photoPath = "https://barybians.ru/avatars/" +
                                  i.toObject().find("author").value().toObject().find("photo")->toString();
                this->photoUrl = i.toObject().find("author").value().toObject().find("photo")->toString();
                post->userId = i.toObject().find("author").value().toObject().find("id")->toInt();
                if (!QFile::exists(i.toObject().find("author").value().toObject().find("photo")->toString())) {
                    qDebug() << post->photoPath;
                    QNetworkRequest networkRequest = this->createRequest(post->photoPath, WebConnector::DOWNLOAD_PHOTO);
                    this->sendRequest(networkRequest, WebConnector::DOWNLOAD_PHOTO);
                }
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
            if (!QFile::exists(photoName)) {
                if (newDoc->open(QIODevice::WriteOnly))
                    newDoc->write(imageData);
            }
            delete newDoc;
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

            if (showDebug)
                qDebug() << document.object();

            break;
        }
        case GET_DIALOGS: {
            QByteArray array = reply.readAll();
            if (showDebug)
                qDebug() << QString(array);

            array.clear();

            break;
        }
        case SEND_MESSAGE: {
            qDebug() << "Hello world..";
            QByteArray array = reply.readAll();
            qDebug() << "Sending message ID:" << array;
            break;
        }
        case ALL_MESSAGES: {
            break;
        }
    }
    reply.deleteLater();
    return root;
}

QVector<Post *> *WebConnector::getFeed() {
    return this->feed;
}

QVector<User *> *WebConnector::getUsersList() {
    return this->userList;
}

QMap<int, QVector<Message *>> WebConnector::getMessagesList() {
    return *this->messagesList;
}

QString WebConnector::getToken() const {
    return this->token;
}


User &WebConnector::getMainUser() const {
    return *this->mainUser;
}

void WebConnector::clearMessageList() {
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

QNetworkRequest WebConnector::createPostRequest(const QString &url, WebConnector::REQUEST_TYPE type, QByteArray data) {
    this->sendingData = qMove(data);
    qDebug() << "Data is:" << this->sendingData;
    QNetworkRequest request;

    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, HEADER_APP_TYPE);

    switch (type) {
        case DIALOG_WITH: {
            standartHeader(request);
            break;
        }
        case SEND_MESSAGE:
            standartHeader(request);
            break;
        default: {
            if (showDebug)
                qDebug() << "Unknown request";
            break;
        }
    }
    return request;
}

void WebConnector::sendRequest(QNetworkRequest &request, WebConnector::REQUEST_TYPE type) {
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
        case SEND_MESSAGE:
            auto *params = new QUrlQuery();
            params->addQueryItem("text", sendingData);

            qDebug() << "Sending message...";


            reply = manager->post(request, params->toString().toUtf8());
            break;
    }
    connect(reply, &QNetworkReply::finished, this, [this, reply, type, request]() {
        QJsonObject obj = parseReply(*reply, type, request);
        reply->deleteLater();
    });

}

WebConnector::~WebConnector() {
    delete mainUser;
    qDeleteAll(*userList);
    delete userList;
    qDeleteAll(*feed);
    delete feed;

}
