#pragma clang diagnostic push
#pragma ide diagnostic ignored "-Wclazy-qt-macros"
#include "headers/mainwindow.h"

#include <QApplication>
#include <QWindow>
#include <QWidget>
#include "headers/loginwindow.h"
#include <QStyleFactory>
#include <qglobal.h>
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
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication app(argc, argv);
#ifdef Q_OS_WIN
    QSettings darkTheme(R"(HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Themes\Personalize)",QSettings::NativeFormat);
    if(darkTheme.value("AppsUseLightTheme")!=0)
    {
        qDebug() << "Dark theme enabled";
        QApplication::setStyle(QStyleFactory::create("Fusion"));
        QPalette darkPalette;
        QColor darkColor = QColor(45,45,45);
        QColor disabledColor = QColor(127, 127, 127);
        darkPalette.setColor(QPalette::Window, darkColor);
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(18,18,18));
        darkPalette.setColor(QPalette::AlternateBase, darkColor);
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
        darkPalette.setColor(QPalette::Button, darkColor);
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
        QApplication::setPalette(darkPalette);
    } else if (darkTheme.value("AppsUseLightTheme") == ""){
        QApplication::setStyle(QStyleFactory::create("Fusion"));
        QPalette darkPalette;
        QColor darkColor = QColor(45,45,45);
        QColor disabledColor = QColor(127, 127, 127);
        darkPalette.setColor(QPalette::Window, darkColor);
        darkPalette.setColor(QPalette::WindowText, Qt::white);
        darkPalette.setColor(QPalette::Base, QColor(18,18,18));
        darkPalette.setColor(QPalette::AlternateBase, darkColor);
        darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
        darkPalette.setColor(QPalette::ToolTipText, Qt::white);
        darkPalette.setColor(QPalette::Text, Qt::white);
        darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
        darkPalette.setColor(QPalette::Button, darkColor);
        darkPalette.setColor(QPalette::ButtonText, Qt::white);
        darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
        darkPalette.setColor(QPalette::BrightText, Qt::red);
        darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    } else {
        qDebug() << "Light theme enabled";
    }
#endif
    auto *loginWindow = new LoginWindow();
    loginWindow->show();
    return QApplication::exec();
}
//TODO: Оптимизировать потребление памяти

#pragma clang diagnostic pop