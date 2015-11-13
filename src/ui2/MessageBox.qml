import QtQuick.Dialogs 1.2

MessageDialog {
    id: messageBox

    function info(message)
    {
        show(message, StandardIcon.Information)
    }

    function error(message)
    {
        show(message, StandardIcon.Critical)
    }

    function show(message, icon)
    {
        this.text = message
        this.icon = icon
        open()
    }
}


