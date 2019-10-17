import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    anchors.fill: parent
    padding: 20
    title: qsTr("Register")
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
                    text: qsTr("Selamat datang di aplikasi rekam medis")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Label {
                    text: user.amIAdmin ? qsTr("Mendaftarkan Admin Baru") : qsTr("Mendaftarkan Pengguna Baru")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                ItemDelegate {
                    width: parent.width
                    contentItem: Column{
                        width: parent.width
                        spacing: 2
                        Label{
                            font.bold: true
                            font.pointSize: 10
                            text : "Nama :"
                        }
                        TextField{
                            id : nama
                            width: parent.width
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
                            text : "Umur :"
                        }
                        TextField{
                            id : umur
                            width: parent.width
                            validator: IntValidator{}
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
                            text : "Jenis Kelamin :"
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
                            text : "Alamat :"
                        }
                        TextField{
                            id : alamat
                            width: parent.width
                        }
                    }
                }
                Label {
                    text: qsTr(" ")
                }
                ItemDelegate {
                    width: parent.width
                    contentItem: Column{
                        width: parent.width
                        spacing: 2
                        Label{
                            font.bold: true
                            font.pointSize: 10
                            text : "NIK :"
                        }
                        TextField{
                            id : nik
                            width: parent.width
                            validator: RegExpValidator { regExp: /[0-9]+/ }
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
                            text : "Sebagai Admin :"
                        }
                        SwitchDelegate{
                            id : role
                            width: parent.width
                            checked: false
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
                            text : "Password :"
                        }
                        TextField{
                            id : password
                            width: parent.width
                            echoMode: TextInput.Password
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
                            text : "Ulangi Password :"
                        }
                        TextField{
                            id : repeatPassword
                            width: parent.width
                            echoMode: TextInput.Password
                        }
                    }
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Button{
                        id: registerButton
                        text: "Register"
                        onClicked: {
                            if(nik.text == ""){
                                window.notify = "NIK tidak valid"
                                notifyDialog.open()
                            }
                            else if(!(password.text == "")){
                                if(password.text != repeatPassword.text){
                                    window.notify = "Isian password tidak sesuai"
                                    notifyDialog.open()
                                }
                                else{
                                    user.createUser(nik.text,password.text,nama.text,umur.text,jk.currentText,alamat.text,role.checked)
                                    stackView.pop()
                                }
                            }
                            else{
                                window.notify = "Password Field is empty"
                                notifyDialog.open()
                            }
                        }
                    }
                    Button{
                        id : cancel
                        text: "Cancel"
                        onClicked: stackView.pop()
                    }
                }
            }
        }
    }
}
