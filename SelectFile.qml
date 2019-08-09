import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.3

Page {
    id : rekamMedisDetail
    anchors.fill: parent
    ColumnLayout{
        anchors.fill: parent
//        FileDialog {
//            id: fileDialog
//            Layout.fillHeight: true
//            Layout.fillWidth: true
//            title: "Pilih gambar"
//            folder: "/storage/emulated/0/"
//            nameFilters: ["Image files (*.jpg *jpeg)"]
//            onAccepted: {
//                console.log("You chose: " + fileDialog.fileUrls)
//                window.uploadImageURL = fileDialog.fileUrl
//                stackView.pop()
//            }
//            onRejected: {
//                console.log("Canceled")
//                stackView.pop()
//            }
//            Component.onCompleted: visible = true
//        }
        FilePicker{
            Layout.fillHeight: true
            Layout.fillWidth: true
            showDotAndDotDot: true
            nameFilters: ["*.jpg","*.jpeg"]
            onFileSelected: {
                console.log("User selects file: " + currentFolder() + "/" +fileName)
                window.uploadImageURL = currentFolder()+fileName
            }
        }
    }
}
