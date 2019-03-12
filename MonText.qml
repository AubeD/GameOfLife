import QtQuick 2.0


Item {
    property alias texteAEditer: text1.text
    id:monText
    width: 30
    height: 60

    MouseArea {
        id: mouseArea
        x: 0
        y: 0
        width: 30
        height: 60
    }

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 30
        height: 60
        color: "#d70d0d"

        Text {
            id: text1
            x: -15
            y: 15
            width: 60
            height: 30
            text: qsTr("Text")
            rotation: -90
            font.pixelSize: 12
        }
    }
    onClicked: rectangle.color="#331451"
    onDoubleClicked: text1.rotation=90

}
