//#include <QHttpMultiPart>
//#include <QUrlQuery>
//#include <QNetworkReply>
//#include <QString>
//#include <QJsonDocument>
//#include <QJsonObject>
//#include <QJsonArray>
#include <QWidget>
#include <QNetworkAccessManager>
#include "Data.h"
#define END_LINE "\n"


User::User()
{

}

void User::printUserData()
{
    qDebug() << "name" << this->name << END_LINE << "lastName" << this->lastName << END_LINE << "id" << this->id << END_LINE << "status" << this->status;
}



Post::Post()
{

}
void Post::printData()
{
    qDebug() << "Title" << this->title << END_LINE << "Text" << this->text << END_LINE << "Date" << this->date << "Edited" << this->edited;
}

