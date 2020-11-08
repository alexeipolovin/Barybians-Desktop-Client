import QtQuick 2.0
import QtQuick.Layouts 1.0
import com.kernux.drawer 1.0
ColumnLayout {
    id: infoColumn

    Image {
        id: profileImage
        Layout.alignment: Qt.AlignHCenter
        source: "file:test"
        width: anchors.fill
    }
    Text {
        id:nameLabel
        text: "lol"
        font.pointSize: 20
        Layout.alignment: Qt.AlignHCenter
    }
    Text {
        id: statusLabel
        text: "kek"
        font.pointSize: 15
        Layout.alignment: Qt.AlignHCenter
    }

    DrawerController {
        id: drawerController

        onNameChanged: {
            nameLabel.text = name
        }
        onStatusChanged: {
            statusLabel.text = status
        }
        onPhotoChanged: {
            profileImage.source ="file:" + photo
        }
    }
}



