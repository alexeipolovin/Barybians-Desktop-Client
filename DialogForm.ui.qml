import QtQuick 2.4

Item {
    id: item1
    width: 400
    height: 400

    Rectangle {
        id: rectangle
        x: 109
        width: 182
        height: 173
        color: "#ffffff"
        anchors.top: parent.top
        anchors.topMargin: 80

        Text {
            id: text1
            text: qsTr("Kak dela?")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            font.pixelSize: 12
            anchors.rightMargin: 80
            anchors.leftMargin: 80
            anchors.bottomMargin: 80
            anchors.topMargin: 80
        }
    }
}
