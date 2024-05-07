import QtQuick 2.15
import QtGraphicalEffects 1.0


Rectangle {
    color: "white"
    radius: 10

    layer.enabled: true
    layer.effect: Glow {
        id: glowEffect
        samples: 25
        color: "mintcream"
        transparentBorder: true
    }

    Behavior on opacity { PropertyAnimation {} }
}
