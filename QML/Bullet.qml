import QtQuick 2.0

Item {
    width: 8
    height: 8

    Image {
        width: 8
        height: 8
        id: bullet
        source: "Images/Bullet/bullet_down.png"
    }

    states: [
        State {
            name: "Forward"

            PropertyChanges {
                target: bullet
                source: "Images/Bullet/bullet_up.png" }
        },
        State {
            name: "Backward"

            PropertyChanges {
                target: bullet
                source: "Images/Bullet/bullet_down.png" }
        },
        State {
            name: "Left"

            PropertyChanges {
                target: bullet
                source: "Images/Bullet/bullet_left.png" }
        },
        State {
            name: "Right"

            PropertyChanges {
                target: bullet
                source: "Images/Bullet/bullet_right.png" }
        }
    ]
}


