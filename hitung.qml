import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    anchors.fill: parent
    padding: 20
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
                Label{
                    text: "Tegangan : "
                }
                TextField {
                    id:tegangan
                    placeholderText: "Tegangan"
                    text: "0"
                    width: parent.width
                    validator: DoubleValidator{}
                    onTextEdited: {
                        inak.text = 0.0011 * tegangan.text - 0.0513
                        dosis.text = inak.text * mAs.text
                        esak.text = dosis.text * bsf.text
                    }
                }
                Label{
                    text: "Arus Waktu (mAs) : "
                }
                TextField {
                    id:mAs
                    placeholderText: "mAs"
                    text: "0"
                    width: parent.width
                    validator: DoubleValidator{}
                    onTextEdited: {
                        inak.text = 0.0011 * tegangan.text - 0.0513
                        dosis.text = inak.text * mAs.text
                        esak.text = dosis.text * bsf.text
                    }
                }
                Label{
                    text: "BSF : "
                }
                TextField {
                    id : bsf
                    placeholderText: "BSF"
                    text: "0"
                    width: parent.width
                    validator: DoubleValidator{}
                    onTextEdited: {
                        inak.text = 0.0011 * tegangan.text - 0.0513
                        dosis.text = inak.text * mAs.text
                        esak.text = dosis.text * bsf.text
                    }
                }
                Label{
                    text: "DAP : "
                }
                TextField {
                    id : dap
                    placeholderText: "DAP"
                    text: "0"
                    width: parent.width
                    validator: DoubleValidator{}
                    onTextEdited: {
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
                            text: 0.0011 * tegangan.text - 0.0513
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
                            text: inak.text * mAs.text
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
                            text: dosis.text * bsf.text
                            font.bold: true
                        }
                    }
                }
            }
        }
    }
}
