import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import com.kernux.controller 1.0
ApplicationWindow {
    Label {text: "AAAAAA"}
    header: ToolBar {
        id: toolBar
        contentHeight: toolButton.implicitHeight
        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }
        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
        }
    }
    Window {
        id: window
        visible: true
        width: 1920
        height: 1080
        Rectangle
        {
            anchors.fill: parent
            gradient: Gradient
            {
                GradientStop {position: 0.000;color: "#cc2b5e";}
                GradientStop {position: 1.000;color: "#753a88";}
            }
        }

        Rectangle
        {
            id:loginRect
            anchors.centerIn: parent
            width: window.width / 3.84
            color: "white"
            height: window.height / 2.16
            radius: 15;
            ColumnLayout {
                width: loginRect.width
                spacing: parent.height / 20
                Layout.alignment: Qt.AlignHCenter
                Layout.fillWidth: true
                anchors.horizontalCenter: parent.horizontalCenter
                Image {
                    Layout.alignment: Qt.AlignHCenter
                    source: "/static/images/flex.png"
                }
                TextField {
                    id: loginField
                    font.pointSize: 15
                    Layout.preferredWidth: parent.width/1.2
                    Layout.alignment: Qt.AlignHCenter
                }
                TextField {
                    id: passwordField
                    echoMode: TextInput.Password
                    font.pointSize: 15
                    Layout.preferredWidth: parent.width/1.2
                    Layout.alignment: Qt.AlignHCenter
                }
                Button {
                    font.pointSize: 15
                    Layout.preferredWidth: parent.width/1.2
                    text: "Login"
                    Layout.alignment: Qt.AlignHCenter
                    onClicked: loginGenerator.sendRequest()
                }
                Item {
                    Layout.fillHeight: true
                }
            }
        }
        LoginGenerator {
            id: loginGenerator
            login: loginField.text
            password: passwordField.text
            onLoginSucces: {
                if (succes) {
                    window.title = "COOL"
                    window.hide()
                    dialogsWindow.show()
                } else {
                    window.title = "WRONG"
                }
            }

        }
    }
MainWindow
{
    id: dialogsWindow

        Drawer {
            id: mainDrawer
            width: 0.22 * dialogsWindow.width
            height: dialogsWindow.height
            ColumnLayout {
                spacing: parent.height / 20
                Layout.alignment: Qt.AlignHCenter
                Layout.fillWidth: true
                anchors.horizontalCenter: parent.horizontalCenter
                Header {

                }

                Button {
                    text: "FirstPage"
                    Layout.alignment: Qt.AlignHCenter
                    onClicked: {stackView.push("FirstPage.qml"); mainDrawer.close();}
                }
                Button {
                    text: "SecondPage"
                    Layout.alignment: Qt.AlignHCenter
                    onClicked: {
                        stackView.push("SecondPage.qml"); mainDrawer.close();
                    }
                }
                }
            }



    StackView {
        id:stackView
        initialItem: "FirstPage.qml"
        anchors.fill: parent
    }
}
}
