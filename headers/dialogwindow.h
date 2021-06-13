//
// Created by Kernux on 13.06.2021.
//

#ifndef BARYBIANS_DESKTOP_CLIENT_DIALOGWINDOW_H
#define BARYBIANS_DESKTOP_CLIENT_DIALOGWINDOW_H


#include <QWidget>
#include <QMainWindow>
#include "webconnector.h"

class DialogWindow : public QWidget{

    ~DialogWindow();

public:
    DialogWindow(WebConnector *webConnector, int id);
};


#endif //BARYBIANS_DESKTOP_CLIENT_DIALOGWINDOW_H
