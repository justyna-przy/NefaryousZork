

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.5
import QtQuick.Controls 6.5
import NefaryousGame

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height
    color: "#36122a"

    TextArea {
        id: textArea
        x: 0
        y: 0
        width: 1000
        height: 544
        color: "#f5f4d1"
        wrapMode: Text.WordWrap
        activeFocusOnPress: false
        cursorVisible: true
        readOnly: true
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

        Button {
            id: button
            width: 375
            height: 80
            text: qsTr("Option")
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

        Button {
            id: button1
            width: 375
            height: 80
            text: qsTr("Option")
            scale: 1
            icon.color: "#590c4c"
            highlighted: false
            font.pointSize: 16
            font.family: "Verdana"
            flat: false
            background: Rectangle {
                color: "#9e1266"
                radius: 10
            }
        }

        Button {
            id: button2
            width: 375
            height: 80
            text: qsTr("Option")
            scale: 1
            icon.color: "#590c4c"
            highlighted: false
            font.pointSize: 16
            font.family: "Verdana"
            flat: false
            background: Rectangle {
                color: "#9e1266"
                radius: 10
            }
        }

        Button {
            id: button3
            width: 375
            height: 80
            text: qsTr("Option")
            scale: 1
            icon.color: "#590c4c"
            highlighted: false
            font.pointSize: 16
            font.family: "Verdana"
            flat: false
            background: Rectangle {
                color: "#9e1266"
                radius: 10
            }
        }
    }
    states: [
        State {
            name: "clicked"
        }
    ]
}
