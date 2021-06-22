#ifndef WEBCONNECTOR_H
#define WEBCONNECTOR_H

#include "data.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QSettings>


class WebConnector : public QObject {
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
        ALL_MESSAGES,
        DIALOG_WITH,
        SEND_MESSAGE,
    };

    QNetworkRequest createRequest(const QString &url, WebConnector::REQUEST_TYPE type);

    void sendRequest(QNetworkRequest &request, WebConnector::REQUEST_TYPE type);

    void standartHeader(QNetworkRequest &request);

    QString getToken() const;

    User &getMainUser() const;

    QJsonObject parseReply(QNetworkReply &reply, WebConnector::REQUEST_TYPE type, const QNetworkRequest &request);

    void makeAuth();

    void setLoginAndPassword(QString login, QString password);

    explicit WebConnector(bool showDebug = false);
    ~WebConnector();

    bool checkAuth();


    QVector<Post *> *getFeed();

    QVector<User *> *getUsersList();

    void cachePhoto(QNetworkReply *reply_photo, const QNetworkRequest &request);


    void clearMessageList();


    QMap<int, QVector<Message *>> getMessagesList();

    QNetworkRequest createPostRequest(const QString &url, WebConnector::REQUEST_TYPE type, QByteArray data);

private:
    QByteArray sendingData;

    bool showDebug;

    QMap<QString, QString> userPhotoMap;
    QVector<User *> *userList;

    QMap<int, QVector<Message *>> *messagesList;

    QVector<Post *> *feed;

    QString photoUrl;
    QString LOGIN;
    QString PASSWORD;

    QByteArray bearerToken;
    bool tokenState = false;
    bool userState = false;
signals:

    void usersList();

    void feedOk();

    void valueChanged(QString &token);

    void messageListReceived();
};

#endif // WEBCONNECTOR_H
