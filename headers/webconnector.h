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
        ALL_POSTS,
        ALL_USERS,
        WRITE_POST,
        GET_DIALOGS,
        DOWNLOAD_PHOTO,
    };

    QNetworkRequest createRequest(const QString &url, WebConnector::REQUEST_TYPE type);

    void sendRequest(QNetworkRequest &request, WebConnector::REQUEST_TYPE type);
    void setStandartHeader(QNetworkRequest &request);

    QString getToken() const;

    User *getMainUser() const;

    QJsonObject parseReply(QNetworkReply &reply, WebConnector::REQUEST_TYPE type);
    void makeAuth();
    bool isTokenExist();
    void setLoginAndPassword(QString login, QString password);

    WebConnector();
    bool authIfExist();
    bool checkAuth();
private:
    QString LOGIN;
    QString PASSWORD;
    bool tokenState = false;
    QByteArray bearerToken;
signals:
    void valueChanged(QString &token);
};

#endif // WEBCONNECTOR_H
