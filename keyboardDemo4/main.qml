import QtQuick 2.6
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

Window {
    id: root
    visible: true
    width: 1024
    height: 90
    title: qsTr("Hello World")
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
//    color: "transparent"

    property int keyBoardHeight: 90

    Rectangle{
        id: keyboard
        width: parent.width
        height: parent.height
        color: "#e0e0e0"
        border.color: "#d1c6c6"
        state: kbConfig.kbState ? "kbOpen" : "kbClose"

        Row{
            anchors{
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
                bottomMargin: 10
                left:parent.left
                leftMargin: 10
            }
            spacing: 6
            Button{text:"1"}
            Button{text:"2"}
            Button{text:"3"}
            Button{text:"4"}
            Button{text:"5"}
            Button{text:"6"}
            Button{text:"7"}
            Button{text:"8"}
            Button{text:"9"}
            Button{text:"0"}
            Button{text:"."}
            Button{text:"*"}
            Button{text:"#"}
        }

        states: [
            State {
                name: "kbOpen"
                PropertyChanges {
                    target: root
                    y: Screen.height-90
                }
            },
            State {
                name: "kbClose"
                PropertyChanges {
                    target: root
                    y: Screen.desktopAvailableHeight+200
                }
            }
        ]
        transitions: [
            Transition {
                from: "kbOpen"
                to: "kbClose"
                PropertyAnimation{
                    target: root
                    property: "y"
                    easing.type: Easing.OutExpo
                    duration: 2000
                }
            },
            Transition {
                from: "kbClose"
                to: "kbOpen"
                PropertyAnimation{
                    target: root
                    property: "y"
                    easing.type: Easing.InExpo
                    duration: 2000
                }
            }
        ]
    }

    Rectangle{
        id: kbCtr
        width: 20
        height: 20
        color: "#c6c5c5"
        anchors{
            top: parent.top
            topMargin: 1
            right: parent.right
            rightMargin: 1
        }
        radius: 100
        layer.enabled: true
        layer.effect: DropShadow {
            transparentBorder: false
            horizontalOffset: 1
            verticalOffset: 1
            radius: 0.1
        }

        Text {
            id: ctrText
            text: "×"
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 15
            color: "black"
        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                kbConfig.kbState = false
            }
            onPressed: {
                kbCtr.color = "#ffffff"
            }
            onReleased: {
                kbCtr.color = "#c6c5c5"
            }
        }
    }

//    MouseArea{
//        anchors.fill: parent
//        onClicked: {
//                var sta = keyboard.state
//                keyboard.state = sta == "kbOpen" ? "kbClose" : "kbOpen"
//        }
//        onPressed: {
//           mouse.accepted = false;
//        }
//    }

}
