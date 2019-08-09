import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    anchors.fill: parent
    padding: 20
    title: qsTr("Rekam Medis")
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
                TextField{
                    id : domain
                    text: user.domain
                    width: parent.width
                    onTextEdited: {
                        user.domain = domain.text
                    }
                }
                Label {
                    text: qsTr("  ")
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
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Button{
                        id: loginButton
                        text: "Login"
                        onClicked: {
                            user.createKey(username.text,password.text)
                        }
                    }
                    Button{
                        id : register
                        text: "Register"
                        onClicked: stackView.replace("register.qml")
                    }
                }
            }
        }
        Timer{
            interval: 1000
            repeat: false
            running: true
            triggeredOnStart: {
                window.isKeyValid ? stackView.replace("rekamMedisList.qml") : none
            }
        }
    }
}