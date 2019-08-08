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
                    text: qsTr("Username :")
                }
                TextField{
                    id : username
                    width: parent.width
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
                            if(username.text == ""){
                                alertlabel.text = "Isian username kosong"
                                alert.open()
                            }
                            else if(!(password.text == "")){
                                if(password.text != repeatPassword.text){
                                    alertlabel.text = "Isian password tidak sesuai"
                                    alert.open()
                                }
                                else{
                                    //alertlabel.text = "Register Berhasil.\nSilahkan Login"
                                    user.createUser(username.text,password.text)
                                    stackView.pop()
                                }
                            }
                            else{
                                alertlabel.text = "Password Field is empty"
                                alert.open()
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

        Dialog{
            id : alert
            modal: true
            anchors.centerIn: parent
            title: "Alert"
            contentItem: Label{
                id : alertlabel
                text: "Password Mismatch"
            }
            standardButtons: Dialog.Ok
            onAccepted: {
                console.log("password mismatch")
            }
        }
    }
}
