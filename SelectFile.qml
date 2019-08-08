import QtQuick 2.12
import QtQuick.Dialogs 1.0

FileDialog {
    id: fileDialog
    title: "Pilih gambar"
    folder: shortcuts.home
    onAccepted: {
        console.log("You chose: " + fileDialog.fileUrls)
        window.uploadImageURL = fileDialog.fileUrl
        stackView.pop()
    }
    onRejected: {
        console.log("Canceled")
        stackView.pop()
    }
    Component.onCompleted: visible = true
}
