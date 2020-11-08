import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

Page {
    id: firstPage
    Button {
        id: openDrawer
        text: "firstPage"
        onClicked:  {mainDrawer.open();}
    }
}
