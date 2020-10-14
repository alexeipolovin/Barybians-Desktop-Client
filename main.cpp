#include "mainwindow.h"

#include <QApplication>
#include <QWindow>
#include <QWidget>

/**
  * @brief main
  *
  * @param argc
  * @param *argv
  *
  * @author Polovin Alexei
  * Типичная точка старта программы
*/

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *window = new MainWindow();
    window->show();
    return app.exec();
}

//TODO: Оптимизировать потребление памяти
