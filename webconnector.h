#ifndef WEBCONNECTOR_H
#define WEBCONNECTOR_H

#include "Data.h"

#include <QtNetwork/QNetworkAccessManager>


class WebConnector : public QObject
{
    Q_OBJECT
public:
    //Вынести вообще в отдельную хрень
    User *mainUser;
//    WebConnector(QString LOGIN, QString PASSWORD);

    QString LOGIN;
    QString PASSWORD;
    QString token;

    QNetworkAccessManager *manager;

    enum REQUEST_TYPE {
        AUTH,
        CURRENT_USER,
        ALL_POSTS,
        ALL_USERS,
        WRITE_POST,
        GET_DIALOGS,
        DOWNLOAD_PHOTO,
    };

    enum TYPE {
        GET,
        POST,
        DELETE,
    };

    QNetworkRequest createRequest(const QString &url, WebConnector::REQUEST_TYPE type);

    void sendRequest(QNetworkRequest &request, WebConnector::REQUEST_TYPE type);
    void setStandartHeader(QNetworkRequest &request);

    QString getToken();

    User *getMainUser();

    QJsonObject parseReply(QNetworkReply &reply, WebConnector::REQUEST_TYPE type);
    void makeAuth();
    bool isTokenExist();
    void setLoginAndPassword(QString login, QString password);

    WebConnector();
    bool authIfExist();
private:
    bool tokenState = false;
    QByteArray bearerToken;
signals:
    void valueChanged(QString &token);
};

#endif // WEBCONNECTOR_H
