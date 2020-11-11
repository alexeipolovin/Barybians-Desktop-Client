#include "headers/mainwindow.h"

#include <QApplication>
#include <QWindow>
#include <QWidget>
#include "headers/loginwindow.h"
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QtQml>
#include <QQmlComponent>
#include <QSurfaceFormat>
#include <QQuickWindow>
#include <QQuickStyle>
#include <headers/drawercontroller.h>
#include <headers/logincontroller.h>

/**
  * @brief main
  *
  * @param argc
  * @param *argv
  *
  * @author Polovin Alexei (alexeipolovin@gmail.com)
  * Типичная точка старта программы
*/

//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);
//    LoginWindow *window = new LoginWindow();

//    window->show();
//    return app.exec();
//}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qmlRegisterType<LoginController>("com.kernux.controller", 1, 0, "LoginGenerator");
    qmlRegisterType<DrawerController>("com.kernux.drawer", 1, 0, "DrawerController");
//    qmlRegisterType<GetDialogController>("com.kernux.getdialog", 1, 0, "GetDialogController");
    QQuickStyle::setStyle("Imagine");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));


    if(engine.rootObjects().isEmpty())
    {
        return -3;
    }
    return app.exec();
}
//TODO: Оптимизировать потребление памяти
