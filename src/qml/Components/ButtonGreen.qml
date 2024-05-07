import QtQuick 2.15


Item {
    id: root

    property alias title: textItem.text
    signal clicked

    property int offsetHorizontal: 35
    property int offsetVertical: 15

    implicitWidth: textItem.implicitWidth + offsetHorizontal*2
    height: textItem.implicitHeight + offsetVertical*2

    opacity: enabled ? 1 : 0.7

    Rectangle {
        id: buttonBackground
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        radius: height/2
        color: 'mistyrose'
    }

    Text {
        id: textItem
        anchors {
            centerIn: parent
        }
        font.pixelSize: 25
    }

    MouseArea {
        id: buttonMouseArea

        anchors.fill: parent
        onClicked: { root.clicked() }
    }

}
