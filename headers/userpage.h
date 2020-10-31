#ifndef USERPAGE_H
#define USERPAGE_H

#include <QFrame>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include "webconnector.h"

class UserPage : public QMainWindow
{
    Q_OBJECT
public:
    explicit UserPage(WebConnector *webConnector, QWidget *parent = nullptr);
public:

    QWidget *ui;

    QFrame *mainInfoFrame;

    QVBoxLayout *mainVLayout;
    QVBoxLayout *nameLastNameLayout;

    QHBoxLayout *mainInfoLayout;

    //Временное решение
    QTextEdit *posts;

    QLabel *name;
    QLabel *lastName;
    QLabel *profilePhoto;
    QLabel *onlineStatus;
    QLabel *lastSeen;

    QPushButton *dialogButton;


    QWidget& getMainWidget();


    void setInfoLayout(QPixmap &photo, QString &name, QString &lastName, QString &birthDate, QString &status, QString &lastSeen);
    void build();
    void resizeEvent(QResizeEvent *event);
signals:

};

#endif // USERPAGE_H
