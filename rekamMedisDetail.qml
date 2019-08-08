import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    id : rekamMedisDetail
    anchors.fill: parent
    padding: 20
    title: qsTr("Detail Rekam Medis")
    property int itemID: 0
    ColumnLayout{
        anchors.fill: parent
        spacing: 40
        ScrollView{
            Layout.fillHeight: true
            Layout.fillWidth: true
            contentWidth: width
            Column{
                spacing: 10
                width: parent.width
                Label {
                    text: "Rekam Medis ID : " + rekamMedisDetail.itemID
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Label {
                    text: qsTr("  ")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Label {
                    text: qsTr("Nama \t\tA")
                }
                Label {
                    text: qsTr("Password\t\tB")
                }
            }
        }
    }
}
