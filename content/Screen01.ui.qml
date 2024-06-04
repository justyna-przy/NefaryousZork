import QtQuick 6.5
import QtQuick.Controls 6.5
import com.nefaryous.game 1.0



Rectangle {
    id: rectangle
    width: 740
    height: 740
    color: "#36122d"

    property string actionState: "main"

    function resetStateToMain() {
        console.log("Resetting state to main");
        actionState = "main";
    }

    Game {
        id: game
        Component.onCompleted: {
            console.log("Game initialized");
            game.resetUIState.connect(resetStateToMain)
        }
    }



    property var exitsList: game.currentRoom.exits
    property var inventory: game.inventory
    property var player: game.player

    function calculateHealthWidth() {
        return 240 * (game.player.currentHealth / 40);
    }

    FontLoader {
        id: gothic
        source: "qrc:/qt/qml/content/fonts/gothic.ttf"
    }


    Grid {
        id: placeholderGrid
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
            model: 4
            delegate: Rectangle {
                width: 300
                height: 45
                color: "#45163a"
                radius: 3
            }
        }
    }
    Grid {
        id: actionGrid
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
            model:  actionState === "main" ? ["Leave Room", "Pick up Item", "Interact with Room", "Use Item"] :
                    actionState === "exits" ? ["Back"].concat(exitsList) :
                        actionState === "items" ? ["Back"].concat(game.currentRoom.roomItems) :
                            actionState === "useItems" ? ["Back"].concat(game.potions) : []

            delegate: Button {
                text: modelData === "Back" ? "Back" :
                        actionState === "main" ? modelData :
                            actionState === "exits" ? modelData.name :
                                actionState === "interact" ? modelData.name :
                                    actionState === "items" ? modelData.name :
                                        actionState === "useItems" ? modelData.name : "Undefined"

                onClicked: {
                    if (modelData === "Back") {
                        actionState = "main";
                    } else if (actionState === "main") {
                        if (modelData === "Leave Room") {
                            actionState = "exits";
                        } else if (modelData === "Pick up Item") {
                            game.checkRoomForItems();
                            actionState = "items";
                        } else if (modelData === "Use Item") {
                            actionState = "useItems";
                        } else if (modelData === "Interact with Room") {
                            if (game.currentRoom.interactable) {
                                game.currentRoom.interactable.interact();
                                game.addToGameLog("Under the eerie moonlight, you place the key on the ancient altar. The shadows around you seem to stir slightly as the key touches the stone surface.");
                                game.addToGameLog("You gently slice the blade across your finger and blood starts dripping out.");
                                game.addToGameLog("You look back up onto the alter an see an exact replica of the key you just placed");
                            } else {
                                game.addToGameLog("There is nothing to interact with here");
                            }
                        }
                    } else if (actionState === "exits") {
                        game.moveToRoom(modelData.destination);
                        actionState = "main";
                    } else if (actionState === "items") {
                        game.pickUpItem(modelData.name);
                        actionState = "main";
                    } else if (actionState === "useItems") {
                        modelData.use();
                        actionState = "main";
                    }
                }
                width: 300
                height: 45
                font.family: gothic.name
                font.pointSize: 20
                background: Rectangle {
                    color: modelData === "Back" ? "#b13e53" : "#9e1266"
                    radius: 3
                }
            }
        }
    }

    Image {
        id: image
        x: 0
        y: 0
        width: 740
        height: 381
        source: game.currentRoom.roomImage
        fillMode: Image.Stretch


        Text {
            id: roomNameText
            text: game.currentRoom.name
            font.family: gothic.name
            font.pointSize: 22
            color: "#f5f4d1"
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: 12
            anchors.leftMargin: 20
        }


        Rectangle {
            width: 240
            height: 60
            color: "#45193d"
            border.color: "#7a276d"
            border.width: 3
            anchors.verticalCenterOffset: 160
            anchors.horizontalCenterOffset: -250
            anchors.centerIn: parent

            Grid {
                columns: 4
                width: parent.width
                height: parent.height
                anchors.verticalCenterOffset: 0
                anchors.horizontalCenterOffset: 0
                anchors.centerIn: parent

                Repeater {
                    model: 4

                    Rectangle {
                        width: parent.height
                        height: parent.height
                        color: "#45193d"
                        border.color: "#7a276d"
                        border.width: 3

                        Image {
                            anchors.fill: parent
                            source: index < game.inventory.count ? game.inventory.getItem(index).imageName : ""
                            visible: index < game.inventory.count
                            fillMode: Image.PreserveAspectFit
                        }
                    }
                }
            }
        }


        Rectangle {
            anchors.verticalCenterOffset: 117
            anchors.horizontalCenterOffset: -250
            anchors.centerIn: parent
            width: 240
            height: 30
            color: "transparent"
            Rectangle {
                anchors.left: parent.left
                id: healthBarContainer
                width: calculateHealthWidth()
                height: 30
                clip: true
                color: "transparent"

                Image {
                    id: heartsImage
                    source: "qrc:/qt/qml/content/images/hearts.png"
                    width: 240
                    height: parent.height
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }




    Rectangle {
        id: rectangle1
        x: 0
        y: 382
        width: 740
        height: 199
        color: "#36122d"
        border.width: 0

        Rectangle {
            width: parent.width
            height: 3
            color: "#45193d"
            border.color: "#45193d"
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
                Component.onCompleted: {
                    scrollView.contentItem.contentY = scrollView.contentItem.contentHeight - scrollView.height
                }
                onTextChanged: {
                    Qt.callLater(function() {
                        scrollView.contentItem.contentY = scrollView.contentItem.contentHeight - scrollView.height;
                    });
                }
            }
        }



    }
}
