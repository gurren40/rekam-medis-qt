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
                    text: qsTr("Selamat datang di aplikasi rekam medis versi beta")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Label {
                    text: qsTr("Mendaftarkan Pengguna Baru")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Label {
                    text: qsTr("Nama :")
                }
                TextField{
                    id : nama
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
                    text: qsTr(" ")
                }
                Label {
                    text: qsTr("NIK :")
                }
                TextField{
                    id : nik
                    width: parent.width
                    validator: RegExpValidator { regExp: /[0-9]+/ }
                }
                Label {
                    text: qsTr("Password :")
                }
                TextField{
                    id : password
                    width: parent.width
                    echoMode: TextInput.Password
                    passwordMaskDelay: 100
                }
                Label {
                    text: qsTr("Ulangi Password :")
                }
                TextField{
                    id : repeatPassword
                    width: parent.width
                    echoMode: TextInput.Password
                    passwordMaskDelay: 100
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
                                    user.createUser(nik.text,password.text,nama.text,umur.text,jk.currentText,alamat.text)
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
                        id : login
                        text: "Login"
                        onClicked: stackView.replace("login.qml")
                    }
                }
            }
        }
    }
}
