//
// Created by rob on 01.11.2020.
//

#ifndef BARYBIANS_DESKTOP_CLIENT_CARD_H
#define BARYBIANS_DESKTOP_CLIENT_CARD_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>

class Card : public QWidget {
Q_OBJECT
public:
    QWidget* getWidget() const;

    QWidget *ui;

    QLabel *postTitle;
    QLabel *postText;

    Card(const QString& title, const QString& text, QWidget *parent = nullptr);

    ~Card();

};
#endif //BARYBIANS_DESKTOP_CLIENT_CARD_H
