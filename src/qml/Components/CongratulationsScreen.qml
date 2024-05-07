import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    signal pressed()

    Image {
        anchors.fill: parent
        source: "../images/blurbg2"
    }

    AnimatedImage {
        id: animation
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -100
        source: "../images/fireworks.gif"
    }

    Button {
        width: 200

        anchors {
            bottom: parent.bottom
            bottomMargin: 50
            horizontalCenter: parent.horizontalCenter
        }

        text: "OK"
        onClicked: {
            console.log("Clicked")
            /* emit */ root.pressed()
        }
    }
}
