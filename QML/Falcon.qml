import QtQuick 2.0

Item {
    width: 32
    height: 32

    Image {
        width: 32
        height: 32
        id: player_tank
        source: "Images/Falcon/falcon_alive.png"
    }

    states: [
        State {
            name: "Alive"

            PropertyChanges {
                target: player_tank
                source: "Images/Falcon/falcon_alive.png" }
        },
        State {
            name: "Dead"

            PropertyChanges {
                target: player_tank
                source: "Images/Falcon/falcon_dead.png" }
        }
    ]
}

