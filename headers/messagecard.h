//
// Created by Kernux on 13.06.2021.
//

#ifndef BARYBIANS_DESKTOP_CLIENT_MESSAGECARD_H
#define BARYBIANS_DESKTOP_CLIENT_MESSAGECARD_H


#include <QString>
#include <QWidget>

class MessageCard : public QWidget {
public:
    MessageCard(QString photoPath, QString text, bool isSelf);
};


#endif //BARYBIANS_DESKTOP_CLIENT_MESSAGECARD_H
