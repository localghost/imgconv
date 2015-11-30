import QtQuick 2.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

Window {
    title: "Pipeline Editor"

    width: 300
    height: 200

    minimumHeight: 300
    minimumWidth: 320

    GridLayout {
        columns: 2
        anchors.fill: parent
        anchors.margins: 10

        ComboBox {
            id: action
            model: ListModel {
                ListElement { text: "ExportAction"; color: "red" }
                ListElement { text: "ResizeAction"; color: "red" }
            }
        }

        Button {
            id: addAction
            text: "Add"
        }

        TextArea {
            id: pipeline
        }

        ColumnLayout {
            Button {
                id: actionUp
                text: "Up"
            }

            Button {
                id: actionDown
                text: "Down"
            }
        }
    }
}

