//#include <QHttpMultiPart>
//#include <QUrlQuery>
//#include <QNetworkReply>
//#include <QString>
//#include <QJsonDocument>
//#include <QJsonObject>
//#include <QJsonArray>
#include <QWidget>
#include <QNetworkAccessManager>
#include "headers/Data.h"
#define END_LINE "\n"

/**
  * @brief User::User
  *
  * @author Polovin Alexei (alexeipolovin@gmail.com)
  *
  * Класс, который служит чтобы обработать приходящий запрос в json
  *
*/

User::User()
{

}

void User::printUserData()
{
    qDebug() << "name" << this->name << END_LINE << "lastName" << this->lastName << END_LINE << "id" << this->id << END_LINE << "status" << this->status;
}


/**
 * @brief Post::Post
 *
 * @author Polovin Alexei (alexeipolovin@gmail.com)
 *
 * Класс, который служит чтобы обработать приходящий запрос в json
 *
 */
Post::Post()
{

}
void Post::printData()
{
    qDebug() << "Title" << this->title << END_LINE << "Text" << this->text << END_LINE << "Date" << this->date << "Edited" << this->edited;
}

