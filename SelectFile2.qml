import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.3
import Qt.labs.folderlistmodel 2.12

Page {
    id : rekamMedisDetail
    anchors.fill: parent
    title: "Select Image"
    ColumnLayout{
        anchors.fill: parent
        ListView{
            id : folderListView
            FolderListModel {
                id: folderModel
                nameFilters: ["*.jpg","*.jpeg"]
                showDotAndDotDot: true
                showDirs: true
                rootFolder: "."
            }
            Component {
                id: fileDelegate
                Text { text: fileName }
            }
            model: folderModel
            delegate: fileDelegate
        }
    }
}
