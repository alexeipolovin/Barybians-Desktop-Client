#ifndef USERPAGE_H
#define USERPAGE_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QListView>

class UserPage
{
public:
    UserPage();
    QWidget *mainWidget;

    QVBoxLayout *mainLayout;
    QHBoxLayout *infoLayout;
    QVBoxLayout *postsLayout;
    QListView *posts;

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

    void addPostToView(QListViewItem post);
};


class MyItemModel : QAbstractItemModel
{
public:
    QString Title;
    QString Text;
};


#endif // USERPAGE_H
