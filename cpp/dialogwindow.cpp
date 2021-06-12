//
// Created by Kernux on 13.06.2021.
//

#include <headers/messagecard.h>
#include <QVBoxLayout>
#include "headers/dialogwindow.h"

DialogWindow::DialogWindow(WebConnector *webConnector, int id) {
    auto mainLayout = new QVBoxLayout();
    QNetworkRequest request = webConnector->createRequest("https://barybians.ru/api/dialogs/" + QString::number(id), WebConnector::DIALOG_WITH);
    webConnector->sendRequest(request, WebConnector::DIALOG_WITH);
    connect(webConnector, &WebConnector::messageListReceived, this, [this, webConnector, mainLayout, id](){
       for(auto i: *webConnector->getMessagesList())
       {
           MessageCard *messageCard = nullptr;
           if(webConnector->mainUser->id == id) {
               qDebug() << "User id:" << i->id;
               qDebug() << "Self id:" << id;
               messageCard = new MessageCard(webConnector->mainUser->photoName, i->text, true);
           }
           else {
               qDebug() << false;
               new MessageCard(webConnector->mainUser->photoName, i->text, false);
           }
           mainLayout->addWidget(messageCard);
       }
        setLayout(mainLayout);
       show();
    });
}

DialogWindow::~DialogWindow() = default;