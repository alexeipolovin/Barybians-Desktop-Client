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
    QNetworkRequest request = webConnector->createRequest("https://barybians.ru/api/dialogs/" + QString::number(id),
                                                          WebConnector::DIALOG_WITH);
//    setWindowTitle(webConnector->getUsersList()->at(id)->name + " " + webConnector->getUsersList()->at(id)->lastName);
    webConnector->sendRequest(request, WebConnector::DIALOG_WITH);
    connect(webConnector, &WebConnector::messageListReceived, this,
            [this, webConnector, mainLayout, id, scrollArea, widget]() {
                qDebug() << "Dialog id:" << id;
                qDebug() << "Vector length:" << webConnector->getMessagesList()[id].length();
                auto mVector = webConnector->getMessagesList()[id];
                for (auto i: mVector) {
                    MessageCard *messageCard;
                    if (i->id == id) {
                        qDebug() << "User id:" << i->id;
                        qDebug() << "Self id:" << id;
                        messageCard = new MessageCard(webConnector->mainUser->photoName, i->text, true);
                    } else {
                        qDebug() << "User id:" << i->id;
                        qDebug() << "Self id:" << id;
                        qDebug() << false;
                        for(auto j : *webConnector->getUsersList()) {
                            if(j->id == id) {
                                messageCard = new MessageCard(j->photoName, i->text, false);
                            }
                        }
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
                connect(sendMessageButton, &QPushButton::clicked, this, [webConnector, id, textInput]() {
                    QNetworkRequest request1 = webConnector->createPostRequest(
                            "https://barybians.ru/api/dialogs/" + QString::number(id), WebConnector::SEND_MESSAGE,
                            textInput->text().toUtf8());
                    webConnector->sendRequest(request1, WebConnector::SEND_MESSAGE);
                });
            });
}

DialogWindow::~DialogWindow() = default;