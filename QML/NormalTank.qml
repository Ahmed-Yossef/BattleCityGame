import QtQuick 2.0

Item {
    width: 32
    height: 32

    Image {
        width: 32
        height: 32
        id: normal_tank
        source: "Images/Tanks/Normal/normal_enemy_backward_1.png"
    }

    states: [
        State {
            name: "Forward"

            PropertyChanges {
                target: normal_tank
                source: "Images/Tanks/Normal/normal_enemy_forward_1.png" }
        },
        State {
            name: "Backward"

            PropertyChanges {
                target: normal_tank
                source: "Images/Tanks/Normal/normal_enemy_backward_1.png" }
        },
        State {
            name: "Left"

            PropertyChanges {
                target: normal_tank
                source: "Images/Tanks/Normal/normal_enemy_left_1.png" }
        },
        State {
            name: "Right"

            PropertyChanges {
                target: normal_tank
                source: "Images/Tanks/Normal/normal_enemy_right_1.png" }
        }
    ]
}

