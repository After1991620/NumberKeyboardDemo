import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id:button
    property alias text: buttonText.text
    width: 70
    height: 70
    color: mouseArea.pressed ? "#c6c5c5" : "#ffffff"
    radius: 10
    layer.enabled: true
    layer.effect: DropShadow {
        transparentBorder: false
        horizontalOffset: 2
        verticalOffset: 2
        radius: 0.1
    }

    Text {
        id: buttonText
        anchors{centerIn: parent}
        font.family: "微软雅黑"
        font.pixelSize: parent.width > parent.height ? parent.height * .6 : parent.width * .6
//        style:Text.Sunken;
        color: mouseArea.pressed ?  "#ffffff" : "#000000";
    }

    MouseArea{
        id: mouseArea
        anchors.fill: parent
//        acceptedButtons: Qt.LeftButton

//        onPressed: {
//            buttonText.color =
//            parent.color = "#c6c5c5"
//            button.state = "press"
//        }
//        onReleased: {
//            buttonText.color = "#000000"
//            parent.color = "#ffffff"
//            button.state = "release"
//        }
//        onClicked: {
//           console.info(text)
//        }
    }

//    states: [
//        State {
//            name: "press"
//            PropertyChanges {
//                target: button
//                y: y-20
//            }
//        }
//    ]

//    transitions: [
//        Transition {
//            to: "*"
//            PropertyAnimation{
//                target: button
//                property: "y"
//                duration: 200
//            }

//        }
//    ]



}



