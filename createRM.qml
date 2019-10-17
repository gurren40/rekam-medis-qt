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
                    text: qsTr("Pasien :")
                }
                ComboBox{
                    property string displayName: "Pilih Pasien"
                    id : userID
                    textRole: "ID"
                    displayText: displayName
                    width: parent.width
                    model: userFilter
                    delegate: ItemDelegate{
                        width: parent.width
                        text: model.Nama
                        onClicked: userID.displayName = model.Nama
                    }
                }
                Label {
                    text: qsTr("Nama Rekam Medis :")
                }
                TextField{
                    id : nama
                    width: parent.width
                }
                Label {
                    text: qsTr("Tegangan :")
                }
                TextField{
                    id : tegangan
                    width: parent.width
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: DoubleValidator{}
                }
                Label {
                    text: qsTr("mAs :")
                }
                TextField{
                    id : mAs
                    width: parent.width
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: DoubleValidator{}
                }
                Label {
                    text: qsTr("mGy :")
                }
                TextField{
                    id : mGy
                    width: parent.width
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: DoubleValidator{}
                }
                Label {
                    text: qsTr("Output Radiasi :")
                }
                TextField{
                    id : outputRadiasi
                    width: parent.width
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: DoubleValidator{}
                }
                Label {
                    text: qsTr("ESAK :")
                }
                TextField{
                    id : esak
                    width: parent.width
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: DoubleValidator{}
                }
                Label {
                    text: qsTr("DAP :")
                }
                TextField{
                    id : dap
                    width: parent.width
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    validator: DoubleValidator{}
                }
                Label {
                    text: qsTr("Gambar :")
                }
                Button{
                    text: "Pilih Gambar"
                    onClicked: {
                        stackView.push("SelectFile.qml")
                        //window.uploadImageURL = rekamMedisLists.getFileUrl()
                    }
                }
                Label {
                    visible: false
                    id : gambar
                    text: window.uploadImageURL
                }

                Image {
                    visible: (window.uploadImageURL === "") ? false : true
                    anchors.horizontalCenter: parent.horizontalCenter
                    id: gambarpreview
                    width: parent.width
                    height: parent.width
                    asynchronous: true
                    fillMode: Image.PreserveAspectFit
                    source: window.uploadImageURL
                }

                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Button{
                        id: buatButton
                        text: "Buat"
                        onClicked: {
                            rekamMedisLists.createNewRekamMedis(userID.currentText,nama.text,tegangan.text,mAs.text,mGy.text,outputRadiasi.text,esak.text,dap.text,gambar.text)
                            stackView.pop()
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
    }
}
