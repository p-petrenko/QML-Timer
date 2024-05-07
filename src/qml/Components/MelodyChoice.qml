import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root

    property string title: ""

    width: 200
    height: choiceTxt.height + 10 + melodyTxt.height

    // Melody title
    Text {
        id: melodyTxt

        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }

        text: "мелодия: "
        font.pixelSize: 18
        color: "ghostwhite"
    }

    // Melody Choice
    Button {
        id: melodyButton

        width: 200
        height: choiceTxt.implicitHeight

        anchors {
            top: melodyTxt.bottom
            topMargin: 10
            horizontalCenter: melodyTxt.horizontalCenter
        }

        background: Rectangle {
            anchors.fill: choiceTxt

            radius: 3
            clip: true

            color: "#507070"
        }

        contentItem: Text {
            id: choiceTxt
            anchors.fill: parent

            padding: 5
            leftPadding: 10

            text: root.title
            font.pixelSize: 18
            color: "white"
        }

        onClicked: melodyMenu.open()

        Component {
            id: menuComponent

            MenuItem {
                text: modelData
                onTriggered: {
                    root.title = text
                }
            }
        }

        Menu {
            id: melodyMenu
            y: melodyButton.height

            property var melodyNames: _countdown.melodyNames

            Repeater {
                model: melodyMenu.melodyNames
                delegate: menuComponent
            }
        }
    }
}
