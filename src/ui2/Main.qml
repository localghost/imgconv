import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import Qt.extension 1.0

ApplicationWindow {
    width: 400
    height: 500
    visible: true

    title: qsTr("Image Converter")

    FileDialog {
        id: addFilesDialog
        title: "Add File(s)"
        selectMultiple: true
        onAccepted: {
            console.log("Accepted")
            mainForm.addFiles(fileUrls)
        }
    }

    MessageBox {
        id: messageBox
    }

    ResizeAction {
        id: resizeActionDialog
        onAccepted: {
            console.log("aspectRatio: " + aspectRatio)
            console.log("height: " + imageHeight)
            console.log("wdith: " + imageWidth)
            if ((imageWidth == 0) || (imageHeight == 0)) {
                messageBox.error(qsTr("Neither image width nor height can be zero."))
            }
        }
    }

//    PipelineEditor {
//        id: pipelineEditor
//    }

    Loader { id: pipelineEditorLoader }

    Action {
        id: addFilesAction
        text: "&Add"
        onTriggered: {
            addFilesDialog.open()
        }
    }

    Action {
        id: removeFilesAction
        text: "&Remove"
        onTriggered: mainForm.removeSelected()
    }

    Action {
        id: removeAllAction
        text: "Remove A&ll"
        onTriggered: mainForm.removeAll()
    }

    Action {
        id: resizeAction
        text: "Re&size"
        onTriggered: {
            resizeActionDialog.open()
        }
    }

    Action {
        id: pieplineEditor
        text: "&Editor"
        onTriggered: {
            if (pipelineEditorLoader.status == Loader.Null)
            {
                pipelineEditorLoader.source = "PipelineEditor.qml"
            }
            pipelineEditorLoader.item.open()
        }
        shortcut: "Ctrl+E"
    }

    menuBar: MenuBar {
        Menu {
            title: "&File"
            MenuSeparator {}
            MenuItem { text: "&Quit"; onTriggered: Qt.quit(); shortcut: "Ctrl+Q" }
        }
        Menu {
            title: "&Pipeline"
            MenuItem { action: pieplineEditor }
        }
    }

    toolBar: ToolBar {
        RowLayout {
            ToolButton { action: addFilesAction }
            ToolButton { action: removeFilesAction }
            ToolButton { action: removeAllAction }
            ToolButton { action: resizeAction }
        }
    }

    MainForm {
        id: mainForm
        anchors.fill: parent

        function addFiles(files) {
            for (var i = 0; i < files.length; ++i) {
                console.log("inserting " + files[i])
                // TODO make the list unique
                mainForm.listView.model.append({path: Helpers.urlToPath(files[i])})
            }
        }

        function removeAll() {
            mainForm.listView.model.clear()
        }

        function removeSelected() {
            var count = 0
            mainForm.listView.selection.forEach(
                function (index) { mainForm.listView.model.remove(index - count, 1); ++count; }
            )
            mainForm.listView.selection.clear()
        }
    }
}

