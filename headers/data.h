#ifndef DATA_H
#define DATA_H

#include <QPixmap>
#include <QString>
//TODO Разнести в разные файлы или убрать в один класс Data(полная хуйня)

class User {
public:
    QPixmap profilePhoto;
    QString photoName;
    QString name;
    QString lastName;
    QString status;
    QString birthDate;
    QString lastVisit;
    int sex;
    int age;
    int id;

    explicit User();

    ~User();

    void printUserData();

    QString getPhotoName();
};

class Post {
public:
    QString title;
    QPixmap photo;
    QString photoPath;
    QString name;
    QString text;
    QString date;
    QString time;
    int userId;
    int edited;
    int id;

    QString firstName;
    QString lastName;

    //Ээээ наверное лишнее, я могу прямо с Jsona получить это всё
    int likesCount;

    Post();

    ~Post();

    void printData();
};


class Message {
public:
    int id;
    QString text;
};

#endif // DATA_H
