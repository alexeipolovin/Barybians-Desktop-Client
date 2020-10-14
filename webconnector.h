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
    WebConnector();
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
//    QJsonObject parseReply(QNetworkReply reply, REQUEST_TYPE type);
    void sendRequest(QNetworkRequest &request, WebConnector::REQUEST_TYPE type);
    QString token;
    QString getToken();
    User *getMainUser();
    void setStandartHeader(QNetworkRequest &request);
    QJsonObject parseReply(QNetworkReply &reply, WebConnector::REQUEST_TYPE type);
private:
    bool tokenState = false;
    QByteArray bearerToken;
signals:
    void valueChanged(QString &token);
};

#endif // WEBCONNECTOR_H
