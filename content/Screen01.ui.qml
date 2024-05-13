
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
    width: 740
    height: 740
    color: "#36122d"

    Game {
        id: game
        Component.onCompleted: {
            console.log("Game initialized")
        }
    }

    property var exitsList: game.currentRoom.exits

    Grid {
        id: grid
        x: 62
        y: 598
        width: 616
        height: 107
        rowSpacing: 15
        columnSpacing: 15

        verticalItemAlignment: Grid.AlignBottom
        horizontalItemAlignment: Grid.AlignLeft
        rows: 2
        columns: 2


        Repeater {
            model: exitsList

            Button {
                id: button
                width: 300
                height: 45
                text: modelData.name || "No exit" // Correctly display the name of the exit
                onClicked: {
                    game.moveToRoom(modelData.destination) // Correctly use the destination property
                }
                font.family: "Verdana"
                font.pointSize: 14
                background: Rectangle {
                    color: "#9e1266"
                    radius: 3
                }

                flat: false
                highlighted: false
                scale: 1
            }
        }
    }

    Image {
        id: image
        x: 0
        y: 0
        width: 740
        height: 381
        source: "qrc:/qt/qml/content/images/pxArt.png"
        fillMode: Image.Stretch

        Rectangle {
            // Main background of the inventory
            width: 264
            height: 53
            color: "#45193d" // Dark gray background
            border.color: "#7a276d"
            border.width: 3
            anchors.verticalCenterOffset: 164
            anchors.horizontalCenterOffset: -238
            anchors.centerIn: parent

            Grid{
                columns: 5
                width: parent.width
                height: parent.height
                anchors.verticalCenterOffset: 0
                anchors.horizontalCenterOffset: 0
                anchors.centerIn: parent


                Repeater {
                    model: 5

                    Rectangle {
                        // Each slot in the inventory
                        width: parent.height
                        height: parent.height
                        color: "#45193d"
                        border.color: "#7a276d"
                        border.width: 3

                        Image {
                            anchors.fill: parent
                            // source: index < inventoryModel.count ? inventoryModel.get(index).icon : ""
                            source: "qrc:/qt/qml/content/images/cat.jpg"
                            // visible: index < inventoryModel.count
                            fillMode: Image.PreserveAspectFit
                        }
                    }
                }
            }
        }

        // ListModel {
        //     id: inventoryModel
        //     ListElement { icon: "sword.png" }
        //     ListElement { icon: "shield.png" }
        // }
    }

    Rectangle {
        id: rectangle1
        x: 0
        y: 382
        width: 740
        height: 199
        color: "#36122d"
        border.width: 0


        // Top border
        Rectangle {
            width: parent.width
            height: 3
            color: "#45193d"
            border.color: "#45193d"  // Adjust the height to change the border thickness
            anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
            }

        ScrollView {
            id: scrollView
            anchors.fill: parent
            ScrollBar.vertical: ScrollBar { }

            TextArea {
                id: textArea
                x: 0
                y: -1
                width: 740
                height: 203
                color: "#f5f4d1"
                text: game.gameLog
                wrapMode: TextEdit.WordWrap
                rightPadding: 60
                bottomPadding: 5
                leftPadding: 60
                topPadding: 30
                activeFocusOnPress: false
                cursorVisible: false
                readOnly: true
                font.family: "Verdana"
                placeholderTextColor: "#f5f4d1"
                font.pointSize: 13
                placeholderText: qsTr("Text Area")
                clip: true
                // Ensures that the initial scroll to the bottom is attempted only after the TextArea component has been fully created.
                Component.onCompleted: {
                    scrollView.contentItem.contentY = scrollView.contentItem.contentHeight - scrollView.height
                }
                onTextChanged: {
                    // Delaying the execution to ensure flickableItem is available and layout is updated
                    Qt.callLater(function() {
                        scrollView.contentItem.contentY = scrollView.contentItem.contentHeight - scrollView.height;
                    });
                }
            }
        }
    }
    states: [
        State {
            name: "clicked"
        }
    ]
}
