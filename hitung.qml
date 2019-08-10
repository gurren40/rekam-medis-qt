import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    anchors.fill: parent
    verticalPadding: 20
    title: qsTr("Hitung Dosis")
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
                ItemDelegate {
                    width: parent.width
                    contentItem: Column{
                        width: parent.width
                        spacing: 2
                        Label{
                            font.bold: true
                            font.pointSize: 10
                            text : "Tegangan"
                        }
                        TextField {
                            id:tegangan
                            placeholderText: "Tegangan"
                            text: "0"
                            width: parent.width
                            validator: DoubleValidator{}
                        }
                    }
                }
                ItemDelegate {
                    width: parent.width
                    contentItem: Column{
                        width: parent.width
                        spacing: 2
                        Label{
                            font.bold: true
                            font.pointSize: 10
                            text : "Arus Waktu (mAs) : "
                        }
                        TextField {
                            id:mAs
                            placeholderText: "mAs"
                            text: "0"
                            width: parent.width
                            validator: DoubleValidator{}
                        }
                    }
                }
                ItemDelegate {
                    width: parent.width
                    contentItem: Column{
                        width: parent.width
                        spacing: 2
                        Label{
                            font.bold: true
                            font.pointSize: 10
                            text: "BSF : "
                        }
                        TextField {
                            id : bsf
                            placeholderText: "BSF"
                            text: "0"
                            width: parent.width
                            validator: DoubleValidator{}
                        }
                    }
                }
                ItemDelegate {
                    width: parent.width
                    contentItem: Column{
                        width: parent.width
                        spacing: 2
                        Label{
                            font.bold: true
                            font.pointSize: 10
                            text: "DAP : "
                        }
                        TextField {
                            id : dap
                            placeholderText: "DAP"
                            text: "0"
                            width: parent.width
                            validator: DoubleValidator{}
                        }
                    }
                }
                Label{
                    text: " "
                }
                Button{
                    id : hitungData
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Hitung"
                    onClicked: {
                        inak.text = 0.0011 * tegangan.text - 0.0513
                        dosis.text = inak.text * mAs.text
                        esak.text = dosis.text * bsf.text
                    }
                }

                Label{
                    text: " "
                }
                ItemDelegate {
                    width: parent.width
                    contentItem: Column{
                        width: parent.width
                        spacing: 2
                        Label{
                            font.bold: false
                            font.pointSize: 10
                            text : "INAK"
                            enabled: false
                        }
                        Label{
                            id : inak
                            text: "0"
                            font.bold: true
                        }
                    }
                }
                ItemDelegate {
                    width: parent.width
                    contentItem: Column{
                        width: parent.width
                        spacing: 2
                        Label{
                            font.bold: false
                            font.pointSize: 10
                            text : "Output Radiasi"
                            enabled: false
                        }
                        Label{
                            id: dosis
                            text: "0"
                            font.bold: true
                        }
                    }
                }
                ItemDelegate {
                    width: parent.width
                    contentItem: Column{
                        width: parent.width
                        spacing: 2
                        Label{
                            font.bold: false
                            font.pointSize: 10
                            text : "Esak"
                            enabled: false
                        }
                        Label{
                            id : esak
                            text: "0"
                            font.bold: true
                        }
                    }
                }
            }
        }
    }
}
