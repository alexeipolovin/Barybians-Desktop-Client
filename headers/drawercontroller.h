#ifndef DRAWERCONTROLLER_H
#define DRAWERCONTROLLER_H

#include "webconnector.h"

#include <QObject>

class DrawerController : public QObject {
Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString status READ getStatus WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QString photo READ getPhoto WRITE setPhoto NOTIFY photoChanged)
public:
    DrawerController();

    ~DrawerController();

    WebConnector *webConnector;

    void setName(const QString &value);

    void setStatus(const QString &value);

    void setPhoto(const QString &value);

    QString getStatus() const;

    QString getName() const;

    QString getPhoto() const;

public slots:

    //    void getName();
    void checkName();

signals:

    void nameReady(QString name);

    void nameChanged();

    void statusChanged();

    void photoChanged();

private:
    QString photo;
    QString name;
    QString status;
};

#endif // DRAWERCONTROLLER_H
