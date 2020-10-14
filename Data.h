#ifndef DATA_H
#define DATA_H

#include <QPixmap>
#include <QString>
//TODO Разнести в разные файлы или убрать в один класс Data(полная хуйня)

class User {
public:
    QPixmap profilePhoto;
    QString name;
    QString lastName;
    QString status;
    QString birthDate;
    QString lastVisit;
    int sex;
    int age;
    int id;
    User();
    ~User();
    void printUserData();
};

class Post {
public:
    QString title;
    QString text;
    QString date;
    QString time;
    int userId;
    int edited;
    int id;

    //Ээээ наверное лишнее, я могу прямо с Jsona получить это всё
    int likesCount;
    Post();
    ~Post();
    void printData();
};

#endif // DATA_H
