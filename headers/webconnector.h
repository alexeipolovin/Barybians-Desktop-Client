#ifndef WEBCONNECTOR_H
#define WEBCONNECTOR_H

#include "Data.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QSettings>


class WebConnector : public QObject
{
    Q_OBJECT
public:
    User *mainUser;
    QString token;

    QSettings *settings;

    QNetworkAccessManager *manager;

    enum REQUEST_TYPE {
        AUTH,
        CURRENT_USER,
//        ALL_POSTS,
        ALL_USERS,
        WRITE_POST,
        GET_DIALOGS,
        DOWNLOAD_PHOTO,
        GET_FEED,
    };

    QNetworkRequest createRequest(const QString &url, WebConnector::REQUEST_TYPE type);

    void sendRequest(QNetworkRequest &request, WebConnector::REQUEST_TYPE type);
    void setStandartHeader(QNetworkRequest &request);

    QString getToken() const;

    User *getMainUser() const;

    QJsonObject parseReply(QNetworkReply &reply, WebConnector::REQUEST_TYPE type, QNetworkRequest request);
    void makeAuth();
    bool isTokenExist();
    void setLoginAndPassword(QString login, QString password);

    explicit WebConnector();
    bool authIfExist();
    bool checkAuth();


    QVector<Post*>* getFeed();
    QVector<User*>* getUsersList();
    QPixmap lastPixmap;

    void cachePhoto(QNetworkReply *reply_photo, QNetworkRequest request);
private:
    QMap<QString,QString>  userPhotoMap;
    QVector<User*> *userList;

    QVector<Post*> *feed;

    QString photoUrl;
    QString LOGIN;
    QString PASSWORD;

    QByteArray bearerToken;
    bool tokenState = false;
    bool userState = false;
signals:
    void usersList();
    void pixmapUpdated();

    void feedOk();

    void valueChanged(QString &token);
};

#endif // WEBCONNECTOR_H
