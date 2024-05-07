import QtQuick 2.15
import QtQuick.Controls 2.15

TabBar {
    id: topView

    property string brightColor: "cyan"
    property string paleColor: "silver"

    width: implicitWidth
    height: 50

    state: topView.currentIndex == 0 ? "timerState" : "stopwatchState"

    background: Rectangle {
        color: paleColor
        radius: 10
    }

    // MARK: - Tab Buttons

    TabButton {
        id: timerBtn

        text: "Таймер"
        font.pixelSize: 20

        width: implicitWidth; height: parent.height
        anchors.verticalCenter: parent.verticalCenter

        background: Rectangle {
            id: timerBtnBackground
            color: brightColor
            radius: 10
        }
    }

    TabButton {
        id: stopwatchBtn

        text: "Секундомер"
        font.pixelSize: 20

        width: implicitWidth; height: parent.height
        anchors.verticalCenter: parent.verticalCenter

        background: Rectangle {
            id: stopwatchBtnBackground
            color: brightColor
            radius: 10
        }
    }

    // MARK: - Signals

    onCurrentIndexChanged: {
        switch (currentIndex) {
        case 0: console.log("Timer clicked"); break
        case 1: console.log("Stopwatch clicked"); break
        }
    }

    // MARK: - States and Transitions

    states: [
        State {
            name: "timerState"
            PropertyChanges { target: timerBtnBackground; color: brightColor }
            PropertyChanges { target: stopwatchBtnBackground; color: paleColor }
        },
        State {
            name: "stopwatchState"
            PropertyChanges { target: stopwatchBtnBackground; color: brightColor }
            PropertyChanges { target: timerBtnBackground; color: paleColor }
        }
    ]

    transitions: [
        Transition {
            from: "*"; to: "*"
            PropertyAnimation {
                targets: [timerBtnBackground, stopwatchBtnBackground]
                property: "color"; duration: 500
            }
        }
    ]
}




