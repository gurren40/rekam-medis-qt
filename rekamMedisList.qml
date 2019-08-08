import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    anchors.fill: parent
    padding: 20
    title: qsTr("Rekam Medis")
    ColumnLayout{
        anchors.fill: parent
        spacing: 40
        ListView{
            id:listViewElement
            //anchors.fill: parent
            Layout.fillHeight: true
            Layout.fillWidth: true
            currentIndex: 0
            model: 15
            footer: Label{
                height: 90
                width: parent.width
                text: ""
            }

            delegate: ItemDelegate {
                property int scheduleID : model.scheduleID
                property string scheduleUUID : model.scheduleUUID
                property int userID : model.userID
                property string userName : model.userName
                property int pinID : model.pinID
                property string pinUUID : model.pinUUID
                property string pinName : model.pinName
                property string scheduleName : model.scheduleName
                property string minute : model.minute
                property string hour : model.hour
                property string dayOfMonth : model.dayOfMonth
                property string month : model.month
                property string dayOfWeek : model.dayOfWeek
                property string timeZone : model.timeZone
                property string value : model.value
                property string description : model.description

                width: parent.width
                //text : model.scheduleName + " ("+model.minute+" "+model.hour+" "+model.dayOfMonth+" "+model.month+" "+model.dayOfWeek+") : "+model.value
                contentItem: Column{
                    width: parent.width
                    spacing: 2
                    Label{
                        text: "Rekam Data"
                        font.bold: true
                    }
                    Label{
                        font.bold: false
                        font.pointSize: 10
                        text : "Sedikit Detail"
                        enabled: false
                    }
                }

                onClicked: {
                    if(listViewElement.currentIndex != index){
                        listViewElement.currentIndex = index
                    }
                    stackView.push("./rekamMedisDetail.qml",{itemID:2})
                }
            }
        }
    }
}
