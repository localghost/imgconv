import QtQuick 2.4
import QtQuick.Controls 1.2

Item {
    id: item1
    width: 400
    height: 400

    property alias listView: listView1

    TableView {
        id: listView1
        anchors.fill: parent
        headerVisible: false
        selectionMode: SelectionMode.MultiSelection
        TableViewColumn { role: "path"; title: "Path" }
        model: ListModel { }
    }
}

