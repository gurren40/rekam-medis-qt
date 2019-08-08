import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    anchors.fill: parent
    padding: 20
    title: qsTr("Pengaturan")
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
                ItemDelegate{
                    text: "Sebuah Pengaturan"
                    width: parent.width
                }
                SwitchDelegate{
                    text: "Mode Gelap"
                    width: parent.width
                }
            }
        }
    }
}
