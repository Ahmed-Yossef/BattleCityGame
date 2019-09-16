import QtQuick 2.0

Item {
    width: 32
    height: 32

    Image {
        width: 32
        height: 32
        id: player_tank
        source: "Images/Tanks/Player/forward_1.png"
    }
    states: [
        State {
            name: "Forward"

            PropertyChanges {
                target: player_tank
                source: "Images/Tanks/Player/forward_1.png" }
        },
        State {
            name: "Backward"

            PropertyChanges {
                target: player_tank
                source: "Images/Tanks/Player/backward_1.png" }
        },
        State {
            name: "Left"

            PropertyChanges {
                target: player_tank
                source: "Images/Tanks/Player/left_1.png" }
        },
        State {
            name: "Right"

            PropertyChanges {
                target: player_tank
                source: "Images/Tanks/Player/right_1.png" }
        }
    ]
}

