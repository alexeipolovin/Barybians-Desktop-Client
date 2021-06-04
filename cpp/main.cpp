#include "headers/mainwindow.h"

#include <QApplication>
#include <QWindow>
#include <QWidget>
#include "headers/loginwindow.h"

/**
  * @brief main
  *
  * @param argc
  * @param *argv
  *
  * @author Polovin Alexei (alexeipolovin@gmail.com)
  * Типичная точка старта программы
*/


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    qmlRegisterType<LoginController>("com.kernux.controller", 1, 0, "LoginGenerator");
//    qmlRegisterType<DrawerController>("com.kernux.drawer", 1, 0, "DrawerController");
//    qmlRegisterType<GetDialogController>("com.kernux.getdialog", 1, 0, "GetDialogController");
//    QQuickStyle::setStyle("Imagine");
    QApplication app(argc, argv);
//
//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
//
//
//    if(engine.rootObjects().isEmpty())
//    {
//        return -3;
//    }
    auto *loginWindow = new LoginWindow();
    loginWindow->show();
    return app.exec();
}
//TODO: Оптимизировать потребление памяти
