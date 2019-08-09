import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    anchors.fill: parent
    verticalPadding: 20
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
                SwitchDelegate{
                    id : notifswitch
                    checked: user.enableNotify
                    text: "Notifikasi Di Aplikasi"
                    width: parent.width
                    onCheckedChanged: {
                        user.enableNotify = notifswitch.checked
                    }
                }
            }
        }
    }
}
