#ifndef NAMECONTROLLER_H
#define NAMECONTROLLER_H
#include <headers/webconnector.h>
#include <QObject>


class NameController : public QObject
{
public:
    NameController(WebConnector *webConnector);
public slots:
    void onNameSurnameChanged();
};

#endif // NAMECONTROLLER_H
