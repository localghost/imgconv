import QtQuick 2.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3

Dialog {
    title: "Resize"

    standardButtons: StandardButton.Ok | StandardButton.Cancel

    property alias aspectRatio: aspectRatio.checked
    property alias imageHeight: height.text
    property alias imageWidth: width.text

    GridLayout {
        implicitWidth: parent.width
        columns: 2

        Text {
            text: "width"
        }
        TextField {
            id: width
            validator: IntValidator {bottom: 0}
            placeholderText: "0"
            maximumLength: 5
        }

        Text {
            text: "height"
        }
        TextField {
            id: height
            validator: IntValidator {bottom: 0}
            placeholderText: "0"
            maximumLength: 5
        }

        Text {
            text: "keep aspect ratio"
        }
        CheckBox {
            id: aspectRatio
            checked: true
        }
    }
}

