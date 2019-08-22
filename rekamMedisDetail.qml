import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    id : rekamMedisDetail
    anchors.fill: parent
    verticalPadding: 20
    title: qsTr("Detail Rekam Medis")
    property int itemID: 0
    property string nik: ""
    property string nama: ""
    property int umur: 0
    property bool jk: false
    property string alamat: ""
    property string jenisKelamin: (!rekamMedisDetail.jk) ? "Pria" : "Wanita"
    Timer{
        interval: 1000
        repeat: false
        running: true
        triggeredOnStart: {
            rekamMedisLists.getRekamMedis(rekamMedisDetail.itemID)
        }
    }

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
                //data pribadi pengguna, ditampilkan jika admin
                Column{
                    width: parent.width
                    spacing: 10
                    visible: user.amIAdmin
                    Label {
                        text: "Profil Pasien"
                        font.bold: true
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    ItemDelegate {
                        width: parent.width
                        contentItem: Column{
                            width: parent.width
                            spacing: 2
                            Label{
                                font.bold: false
                                font.pointSize: 10
                                text : "Nama"
                                enabled: false
                            }
                            Label{
                                text: rekamMedisDetail.nama
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
                                text : "NIK"
                                enabled: false
                            }
                            Label{
                                text: rekamMedisDetail.nik
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
                                text : "Umur"
                                enabled: false
                            }
                            Label{
                                text: rekamMedisDetail.umur
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
                                text : "Jenis Kelamin"
                                enabled: false
                            }
                            Label{
                                text: rekamMedisDetail.jenisKelamin
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
                                text : "Alamat"
                                enabled: false
                            }
                            Label{
                                text: rekamMedisDetail.alamat
                                font.bold: true
                            }
                        }
                    }
                    Label{
                        width: parent.width
                        text: " "
                    }
                }

                //data pemerikasaan
                Label {
                    text: "Data Pemeriksaan"
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                ItemDelegate {
                    width: parent.width
                    contentItem: Column{
                        width: parent.width
                        spacing: 2
                        Label{
                            font.bold: false
                            font.pointSize: 10
                            text : "Nama"
                            enabled: false
                        }
                        Label{
                            text: rekamMedisLists.Nama
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
                            text : "Dibuat"
                            enabled: false
                        }
                        Label{
                            text: Qt.formatDateTime(Date.fromLocaleString(locale,rekamMedisLists.datecreated,"yyyy-MM-dd"),"dddd, d MMMM yyyy")
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
                            text : "Tegangan"
                            enabled: false
                        }
                        Label{
                            text: rekamMedisLists.Tegangan
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
                            text : "Arus Waktu (mAs)"
                            enabled: false
                        }
                        Label{
                            text: rekamMedisLists.mAs
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
                            text : "INAK (mGy)"
                            enabled: false
                        }
                        Label{
                            text: rekamMedisLists.mGy
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
                            text : "Output Radiasi (mGy/mAs)"
                            enabled: false
                        }
                        Label{
                            text: rekamMedisLists.OutputRadiasi
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
                            text: rekamMedisLists.ESAK
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
                            text : "DAP"
                            enabled: false
                        }
                        Label{
                            text: rekamMedisLists.DAP
                            font.bold: true
                        }
                    }
                }
                Label {
                    text: " "
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Label {
                    text: "Foto Pemeriksaan"
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                ItemDelegate{
                    width: parent.width
                    height: parent.width
                    contentItem: Image{
                        asynchronous: true
                        fillMode: Image.PreserveAspectFit
                        width: parent.width
                        height: parent.width
                        source: user.domain+"/rmimage/"+rekamMedisLists.imageFile
                    }
                }
            }
        }
    }
}
