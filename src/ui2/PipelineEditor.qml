import QtQuick 2.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1

Dialog {
    title: "Pipeline Editor"

    GridLayout {
        columns: 2
        anchors.fill: parent

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

