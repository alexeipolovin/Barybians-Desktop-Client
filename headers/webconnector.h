#ifndef WEBCONNECTOR_H
#define WEBCONNECTOR_H

#include "data.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QSettings>


class WebConnector : public QObject {

Q_OBJECT

public:

    enum REQUEST_TYPE {
        AUTH,
        CURRENT_USER,
        ALL_USERS,
        WRITE_POST,
        GET_DIALOGS,
        DOWNLOAD_PHOTO,
        GET_FEED,
        ALL_MESSAGES,
        DIALOG_WITH,
        SEND_MESSAGE,
    };

    User *mainUser;
    User &getMainUser() const;

    QString token;

    QSettings *settings;

    QNetworkAccessManager *manager;



    QNetworkRequest createRequest(const QString &url, WebConnector::REQUEST_TYPE type);

    void sendRequest(QNetworkRequest &request, WebConnector::REQUEST_TYPE type);
    void standartHeader(QNetworkRequest &request);
    void makeAuth();
    void setLoginAndPassword(QString login, QString password);
    void cachePhoto(QNetworkReply *reply_photo, const QNetworkRequest &request);
    void clearMessageList();

    QString getToken() const;


    QJsonObject parseReply(QNetworkReply &reply, WebConnector::REQUEST_TYPE type, const QNetworkRequest &request);


    explicit WebConnector(bool showDebug = false);
    ~WebConnector();

    bool checkAuth();


    QVector<Post *> *getFeed();

    QVector<User *> *getUsersList();



    QMap<int, QVector<Message *>> getMessagesList();

    QNetworkRequest createPostRequest(const QString &url, WebConnector::REQUEST_TYPE type, QByteArray data);

private:
    QByteArray sendingData;


    QMap<QString, QString> userPhotoMap;

    QMap<int, QVector<Message *>> *messagesList;

    QVector<Post *> *feed;
    QVector<User *> *userList;

    QString photoUrl;
    QString LOGIN;
    QString PASSWORD;

    QByteArray bearerToken;

    bool tokenState = false;
    bool userState = false;
    bool showDebug;
signals:
    void usersList();
    void feedOk();
    void valueChanged(QString &token);
    void messageListReceived();
};

#endif // WEBCONNECTOR_H
