import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
//import RekamMedis 1.0

Page {
    anchors.fill: parent
    topPadding: 10
    title: qsTr("Rekam Medis")
    Timer{
        interval: 1000
        running: true
        repeat: false
        onTriggered: {
            userLists.getUserList()
            user.getUserInfo()
        }
    }

    ColumnLayout{
        anchors.fill: parent
        spacing: 40
        ListView{
            id:listViewElement
            //anchors.fill: parent
            Layout.fillHeight: true
            Layout.fillWidth: true
            currentIndex: 0
            model: userFilter

            header: ItemDelegate{
                id : sortFilter
                width: parent.width
                rightPadding: 0
                contentItem: Row {
                    width: parent.width
                    TextField{
                        id : searchField
                        width: parent.width - sortOption.width
                        anchors.verticalCenter: parent.verticalCenter
                        placeholderText: "Filter"
                        onTextEdited: userFilter.setFilterString(searchField.text)
                    }
                    ToolButton{
                        id : sortOption
                        icon.name: userFilter.isDescending ? "sort-descending" : "sort-ascending"
                        icon.color: "teal"
                        onClicked: userFilter.isDescending ? userFilter.isDescending = false : userFilter.isDescending = true
                    }
                }
            }

            delegate: ItemDelegate {
                width: parent.width
                contentItem: Column{
                    width: parent.width
                    spacing: 2
                    Label{
                        text: model.Nama
                        font.bold: true
                    }
                    Label{
                        font.bold: false
                        font.pointSize: 10
                        text : "Alamat : "+model.Alamat
                        enabled: false
                    }
                }

                onClicked: {
                    if(listViewElement.currentIndex != index){
                        listViewElement.currentIndex = index
                    }
                    console.log(model.NIK)
                    stackView.push("rekamMedisList.qml",{userID:model.ID,nik:model.NIK,nama:model.Nama,umur:model.Umur,jk:model.JK,alamat:model.Alamat})
                }
            }
        }
    }
}
