import QtQuick 2.0
import QtQuick.Layouts 1.0
ColumnLayout {
    id: infoColumn

    Image {
        Layout.alignment: Qt.AlignHCenter
        source: "qrc:/static/images/flex.png"
        width: anchors.fill
    }
    Text {
        Layout.alignment: Qt.AlignHCenter
        text: "Hello "+ " World"
    }

}

NameController {

}
