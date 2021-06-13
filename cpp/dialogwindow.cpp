//
// Created by Kernux on 13.06.2021.
//

#include <headers/messagecard.h>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLineEdit>
#include <QPushButton>
#include "headers/dialogwindow.h"

DialogWindow::DialogWindow(WebConnector *webConnector, int id) {
    auto scrollArea = new QScrollArea(this);
//    auto scrollAreaWidgetContest = new QWidget(scrollArea);
    auto widget = new QWidget();
    auto mainLayout = new QVBoxLayout(scrollArea);
    QNetworkRequest request = webConnector->createRequest("https://barybians.ru/api/dialogs/" + QString::number(id), WebConnector::DIALOG_WITH);
    webConnector->sendRequest(request, WebConnector::DIALOG_WITH);
    connect(webConnector, &WebConnector::messageListReceived, this, [this, webConnector, mainLayout, id, scrollArea, widget](){
       for(auto i: *webConnector->getMessagesList())
       {
           MessageCard *messageCard = nullptr;
           if(i->id == id)
           {
               qDebug() << "User id:" << i->id;
               qDebug() << "Self id:" << id;
               messageCard = new MessageCard(webConnector->mainUser->photoName, i->text, true);
           }
           else
           {
               qDebug() << "User id:" << i->id;
               qDebug() << "Self id:" << id;
               qDebug() << false;
               messageCard = new MessageCard(webConnector->mainUser->photoName, i->text, false);
           }
           mainLayout->addWidget(messageCard);
           widget->setLayout(mainLayout);
       }
        scrollArea->setWidget(widget);
        auto mainLay = new QVBoxLayout();
        mainLay->addWidget(scrollArea);
        auto textInput = new QLineEdit();
        auto sendMessageLay = new QHBoxLayout();
        auto sendMessageButton = new QPushButton("Send");
        sendMessageLay->addWidget(textInput);
        sendMessageLay->addWidget(sendMessageButton);
        mainLay->addLayout(sendMessageLay);
        setLayout(mainLay);
        show();
        connect(sendMessageButton, &QPushButton::clicked, this, [this, webConnector, id, textInput](){
            QNetworkRequest request1 = webConnector->createPostRequest("https://barybians.ru/api/dialogs/" + QString::number(id), WebConnector::SEND_MESSAGE, textInput->text().toUtf8());
            webConnector->sendRequest(request1, WebConnector::SEND_MESSAGE);
        });
    });
}

DialogWindow::~DialogWindow() = default;