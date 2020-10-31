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
    QApplication app(argc, argv);
//    MainWindow *window = new MainWindow();
//    window->show();
//    window->showMaximized();
    LoginWindow *window = new LoginWindow();

    window->show();
    return app.exec();
}

//TODO: Оптимизировать потребление памяти
