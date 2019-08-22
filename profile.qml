import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    id : profil
    anchors.fill: parent
    verticalPadding: 20
    title: qsTr("Profil")
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
                    text: "Profil Pengguna"
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
                            text: user.Nama
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
                            text: user.NIK
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
                            text: user.Umur
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
                            text: user.JK ? "Wanita" : "Pria"
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
                            text: user.Alamat
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
                            text : "Role"
                            enabled: false
                        }
                        Label{
                            text: user.amIAdmin ? "Administrator" : "Pasien"
                            font.bold: true
                        }
                    }
                }
            }
        }
    }
}
