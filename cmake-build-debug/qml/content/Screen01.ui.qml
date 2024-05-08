

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.5
import QtQuick.Controls 6.5
import NefaryousGame
import com.nefaryous.game 1.0

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height
    color: "#36122a"

    Game {
        id: game
        Component.onCompleted: {
            console.log("Game initialized")
        }
    }

    property var exitsList: game.currentRoom.exits

    TextArea {
        id: textArea
        x: 0
        y: 0
        width: 900
        height: 544
        color: "#f5f4d1"
        text: game.gameLog
        readOnly: true
        wrapMode: Text.WordWrap
        activeFocusOnPress: false
        cursorVisible: true
        padding: 30
        textMargin: 20
        font.family: "Verdana"
        placeholderTextColor: "#f5f4d1"
        font.pointSize: 16
        placeholderText: qsTr("Text Area")

        TextField {
            id: textField
            x: 0
            y: 478
            width: 900
            height: 66
            opacity: 1
            selectionColor: "#000000"
            placeholderText: qsTr("Text Field")
            background: Rectangle {
                color: "#d57cc3" // Change to your desired color
                radius: 0
            }
        }
    }

    Grid {
        id: grid
        x: 49
        y: 598
        width: 802
        height: 253
        spacing: 50
        verticalItemAlignment: Grid.AlignTop
        horizontalItemAlignment: Grid.AlignLeft
        rows: 2
        columns: 2

        Repeater {
            model: exitsList

            Button {
                id: button
                width: 375
                height: 80
                text: modelData.name || "No exit" // Correctly display the name of the exit
                onClicked: {
                    game.moveToRoom(modelData.destination) // Correctly use the destination property
                }
                font.family: "Verdana"
                font.pointSize: 16
                background: Rectangle {
                    color: "#9e1266"
                    radius: 10
                }
                flat: false
                highlighted: false
                scale: 1
            }
        }
    }
    states: [
        State {
            name: "clicked"
        }
    ]
}
