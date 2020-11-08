import QtQuick 2.0
import QtQuick.Controls 2.0

Page {
    id: secondPage
    Button {
        id:secondOpenDrawer
        text: "secondPage"
        onClicked: {mainDrawer.open();}
    }
}
