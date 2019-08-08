import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    id : createRM
    anchors.fill: parent
    padding: 20
    title: qsTr("Buat Rekam Medis Baru")
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
                    text: qsTr("Nama :")
                }
                TextField{
                    id : nama
                    width: parent.width
                }
                Label {
                    text: qsTr("NIK :")
                }
                TextField{
                    id : nik
                    width: parent.width
                }
                Label {
                    text: qsTr("Umur :")
                }
                TextField{
                    id : umur
                    width: parent.width
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: IntValidator{}
                }
                Label {
                    text: qsTr("Jenis Kelamin :")
                }
                ComboBox{
                    id : jk
                    textRole: "jk"
                    displayText: (currentText == 0) ? "Pria" : "Wanita"
                    width: parent.width
                    model: ListModel{
                        ListElement{
                            name : "Pria"
                            jk : 0
                        }
                        ListElement{
                            name : "Wanita"
                            jk : 1
                        }
                    }

                    delegate: ItemDelegate{
                        width: parent.width
                        text: model.name
                    }
                }
                Label {
                    text: qsTr("Alamat :")
                }
                TextField{
                    id : alamat
                    width: parent.width
                }
                Label {
                    text: qsTr("Tegangan :")
                }
                TextField{
                    id : tegangan
                    width: parent.width
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: IntValidator{}
                }
                Label {
                    text: qsTr("mAs :")
                }
                TextField{
                    id : mAs
                    width: parent.width
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: IntValidator{}
                }
                Label {
                    text: qsTr("mGy :")
                }
                TextField{
                    id : mGy
                    width: parent.width
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: IntValidator{}
                }
                Label {
                    text: qsTr("Output Radias :")
                }
                TextField{
                    id : outputRadiasi
                    width: parent.width
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: IntValidator{}
                }
                Label {
                    text: qsTr("ESAK :")
                }
                TextField{
                    id : esak
                    width: parent.width
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: IntValidator{}
                }
                Label {
                    text: qsTr("DAP :")
                }
                TextField{
                    id : dap
                    width: parent.width
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: IntValidator{}
                }
                Label {
                    text: qsTr("Gambar :")
                }
                Button{
                    text: "Pilih gambar"
                    onClicked: {
                        stackView.push("SelectFile.qml")
                    }
                }
                Label {
                    id : gambar
                    text: window.uploadImageURL
                }

                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Button{
                        id: buatButton
                        text: "Buat"
                        onClicked: {
                            alert.open()
                        }
                    }
                    Button{
                        id : kembali
                        text: "Kembali"
                        onClicked: stackView.pop()
                    }
                }
            }
        }
        Dialog{
            id : alert
            modal: true
            anchors.centerIn: parent
            title: "Alert"
            contentItem: Label{
                id : alertlabel
                text: "Berhasil Dibuat"
            }
            standardButtons: Dialog.Ok
            onAccepted: {
                console.log("berhasil dibuat")
                stackView.pop()
            }
        }
    }
}
