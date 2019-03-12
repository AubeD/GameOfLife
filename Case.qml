import QtQuick 2.0

Item {
    id: container
    property alias cellColor: rectangle.color
    property alias name: rectangle.coordonee
    property alias valeur: text1.text
    signal clicked(color cellColor)


    width: 75; height: 75

    Rectangle {
        id: rectangle
        property var coordonee: "00"
        border.color: "white"
        anchors.fill: parent



        MouseArea {
            anchors.fill: parent
            onClicked: container.clicked(container.cellColor)

        Text {
            id: text1
            text: qsTr("Text")
            fontSizeMode: Text.Fit
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 12
        }
    }

}
}
