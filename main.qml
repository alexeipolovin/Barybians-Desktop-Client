import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import com.kernux.controller 1.0

Window {
    id: window
    visible: true
    width: 1280
    height: 720
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
            } else {
                window.title = "WRONG"
            }
        }

    }
}
