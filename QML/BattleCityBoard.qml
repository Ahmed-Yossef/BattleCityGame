import QtQuick 2.4

Item {
    width: 520
    height: 424
    property alias livesLeft: lives_Text.text
    property alias enemiesLeft: enemies_Text.text
    property alias winLose: loseWin_Text.text

    Rectangle {
        width: 416
        height: 424
        z: 0
        color: "black"
    }

    Text {
        x: 420
        y: 20
        id: lives_Text
        text: qsTr("Lives Left : ")
    }
    Text {
        x: 420
        y: 40
        id: enemies_Text
        text: qsTr("Enemies Left : ")
    }

    Text {
        x: 420
        y: 60
        id: loseWin_Text
        text: qsTr("Playing")
    }
}

