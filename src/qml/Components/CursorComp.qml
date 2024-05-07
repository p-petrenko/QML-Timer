import QtQuick 2.15


Component {
    Rectangle {
        id: cursorRect
        height: parent.cursorRectangle.height
        width: 5
        visible: parent.cursorVisible
        color: "khaki"

        // TODO: uncomment before archiving
//                PropertyAnimation {
//                    id: animOne
//                    target: cursorRect
//                    property: "color"
//                    to: paleBgColor
//                    duration: 2000
//                    onStopped: animTwo.start()
//                }
//                PropertyAnimation {
//                    id: animTwo
//                    target: cursorRect
//                    property: "color"
//                    to: "khaki"
//                    duration: 2000
//                    onStopped: animOne.start()
//                }
//        Component.onCompleted: { animTwo.start() }
    }
}
