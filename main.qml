import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.1

Window {
    visible: true
    width: 320
    height: 536
    title: qsTr("2048")

    Rectangle {
        id: page
        anchors.fill: parent
        Text {
            id: text1
            text: vueObjectCpt.cptQML + "  /  " + vueObjectCpt.stQML
            y: 30
            anchors.horizontalCenter: page.horizontalCenter
            font.pointSize: 24; font.bold: true
            focus: true
            Keys.onPressed: {
                switch(event.key){
                case Qt.Key_Up:
                    vueObjectCpt.savePrecedent();
                    vueObjectCpt.up();
                    vueObjectCpt.nouvelle_case();
                    break;
                case Qt.Key_Down:
                    vueObjectCpt.savePrecedent();
                    vueObjectCpt.down();
                    vueObjectCpt.nouvelle_case();
                    break;
                case Qt.Key_Left:
                    vueObjectCpt.savePrecedent();
                    vueObjectCpt.left();
                    vueObjectCpt.nouvelle_case();
                    break;
                case Qt.Key_Right:
                    vueObjectCpt.savePrecedent();
                    vueObjectCpt.right();
                    vueObjectCpt.nouvelle_case();
                    break;
                }
            }
        }

        MessageDialog {
            id: messageDialog
            title: "Game over"
            text: "Vous avez perdu."
            onAccepted: {
                vueObjectCpt.nouvelle_partie();
            }
            visible: vueObjectCpt.dialog_visibleQML
        }


        Grid {
            id: colorPicker
            x: 4; y: 127; anchors.bottom: page.bottom; anchors.bottomMargin: 127
            rows: 4; columns: 4; spacing: 4

            Case { name: "11" ; cellColor: vueObjectCpt.couleurQML[0] ; valeur : vueObjectCpt.casesQML[0] }
            Case { name: "12" ; cellColor: vueObjectCpt.couleurQML[1]; valeur : vueObjectCpt.casesQML[1] }
            Case { name: "13" ; cellColor: vueObjectCpt.couleurQML[2]; valeur : vueObjectCpt.casesQML[2] }
            Case { name: "14" ; cellColor: vueObjectCpt.couleurQML[3]; valeur : vueObjectCpt.casesQML[3] }
            Case { name: "21" ; cellColor: vueObjectCpt.couleurQML[4]; valeur : vueObjectCpt.casesQML[4] }
            Case { name: "22" ; cellColor: vueObjectCpt.couleurQML[5]; valeur : vueObjectCpt.casesQML[5] }
            Case { name: "23" ; cellColor: vueObjectCpt.couleurQML[6]; valeur : vueObjectCpt.casesQML[6] }
            Case { name: "24" ; cellColor: vueObjectCpt.couleurQML[7]; valeur : vueObjectCpt.casesQML[7] }
            Case { name: "31" ; cellColor: vueObjectCpt.couleurQML[8]; valeur : vueObjectCpt.casesQML[8] }
            Case { name: "32" ; cellColor: vueObjectCpt.couleurQML[9]; valeur : vueObjectCpt.casesQML[9] }
            Case { name: "33" ; cellColor: vueObjectCpt.couleurQML[10]; valeur : vueObjectCpt.casesQML[10] }
            Case { name: "34" ; cellColor: vueObjectCpt.couleurQML[11]; valeur : vueObjectCpt.casesQML[11] }
            Case { name: "41" ; cellColor: vueObjectCpt.couleurQML[12]; valeur : vueObjectCpt.casesQML[12] }
            Case { name: "42" ; cellColor: vueObjectCpt.couleurQML[13]; valeur : vueObjectCpt.casesQML[13] }
            Case { name: "43" ; cellColor: vueObjectCpt.couleurQML[14]; valeur : vueObjectCpt.casesQML[14] }
            Case { name: "44" ; cellColor: vueObjectCpt.couleurQML[15]; valeur : vueObjectCpt.casesQML[15] }
        }

        Rectangle {
            id: rectangle
            x: 64
            y: 481
            width: 192
            height: 36
            color: "#2ccebc"

            Text {
                id: text2
                color: "#ffffff"
                text: qsTr("Nouvelle Partie")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 12
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: vueObjectCpt.nouvelle_partie();
            }
        }

        Text {
            id: text3
            x: 0
            y: 10
            width: 320
            height: 14
            text: qsTr("Score :    /    Record :")
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 12
        }
    }

    Rectangle {
        id: rectangle1
        x: 64
        y: 434
        width: 192
        height: 36
        color: "#2ccebc"
        Text {
            id: text4
            color: "#ffffff"
            text: qsTr("Retour")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.pixelSize: 12
        }

        Image {
            id: image
            x: 8
            y: 4
            width: 40
            height: 28
            source: "qrc:fleche.png"
        }

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
            onClicked: vueObjectCpt.retour();
        }

    }





}
