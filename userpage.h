#ifndef USERPAGE_H
#define USERPAGE_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QListView>
#include <QTextEdit>
#include <webconnector.h>

class UserPage
{
public:
    UserPage(WebConnector *webconnector);
    QWidget *mainWidget;

    QVBoxLayout *mainLayout;
    QHBoxLayout *infoLayout;
    QVBoxLayout *postsLayout;
    QListView *posts;
    QTextEdit *postsField;

    QLabel *userPhoto;
    QLabel *userName;
    QLabel *lastName;
    QLabel *birthDate;
    QLabel *userStatus;
    QLabel *lastSeen;

    QWidget* getMainWidget();

    QVBoxLayout *getMainLayout();
    QHBoxLayout getInfoLayout();
    QVBoxLayout getPostsLayout();

    void setInfoLayout(QPixmap &photo, QString &name, QString &lastName, QString &birthDate, QString &status, QString &lastSeen);
    void build();

    //    void addPostToView(QListViewItem post);
    void setPostsLayout();
};


class MyItemModel : QAbstractItemModel
{
public:
    QString Title;
    QString Text;
};


#endif // USERPAGE_H
