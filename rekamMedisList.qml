import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import RekamMedis 1.0

Page {
    anchors.fill: parent
    topPadding: 10
    title: qsTr("Rekam Medis")
    Timer{
        interval: 1000
        running: true
        repeat: false
        onTriggered: {
            rekamMedisLists.getRekamMedisList()
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
            model: RekamMedisModel{
                list: rekamMedisLists
            }

            footer: Label{
                height: 90
                width: parent.width
                text: ""
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
                    stackView.push("./rekamMedisDetail.qml",{itemID:model.ID})
                }
            }
        }
    }
}
