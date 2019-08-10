import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Page {
    anchors.fill: parent
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
                Image{
                    id : logo
                    source: "/image/logo.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: (window.width < 192) ? window.width : 192
                    height: logo.width
                }
                Label {
                    text: qsTr(" ")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Label {
                    text: qsTr("Selamat datang di Aplikasi Rekam Medis")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                ItemDelegate {
                    width: parent.width
                    visible: domainSwiper.checked
                    contentItem: Column{
                        width: parent.width
                        spacing: 2
                        Label{
                            font.bold: true
                            font.pointSize: 10
                            text : "Domain :"
                        }
                        TextField{
                            id : domain
                            text: user.domain
                            width: parent.width
                            placeholderText: "Domain"
                            onTextEdited: {
                                user.domain = domain.text
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
                            text : "Username :"
                        }
                        TextField{
                            id : username
                            width: parent.width
                            placeholderText: "Username"
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
                            text: qsTr("Password :")
                        }
                        TextField{
                            id : password
                            width: parent.width
                            echoMode: TextInput.Password
                            passwordMaskDelay: 100
                            placeholderText: "Password"
                        }
                    }
                }
                Row{
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20
                    Button{
                        id: loginButton
                        text: "Login"
                        onClicked: {
                            rekamMedisLists.clearItemsData()
                            user.username = username.text
                            user.createKey(username.text,password.text)
                        }
                    }
                    Button{
                        id : register
                        text: "Register"
                        onClicked: stackView.replace("register.qml")
                        visible: user.advancedOption
                    }
                }
                Label{
                    text : ""
                }
                SwitchDelegate{
                    width: parent.width
                    id : domainSwiper
                    text: "Advanced Option"
                    checked: user.advancedOption
                    onClicked: user.advancedOption = checked
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
