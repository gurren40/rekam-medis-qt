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
                Label {
                    text: qsTr(" ")
                    anchors.horizontalCenter: parent.horizontalCenter
                }
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
                ItemDelegate{
                    width: parent.width
                    visible: domainSwiper.checked
                    contentItem: CheckBox{
                        width: parent.width
                        checked: user.amIAdmin
                        text: "Login As Admin"
                        onClicked: {
                            user.amIAdmin = checked
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
                            text: qsTr("Password :")
                        }
                        TextField{
                            id : password
                            width: parent.width
                            echoMode: TextInput.Password
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
                            if(nik.length != 16){
                                window.notify = "NIK tidak valid"
                                notifyDialog.open()
                            }
                            else if(password.length < 1){
                                window.notify = "Password tidak valid"
                                notifyDialog.open()
                            }
                            else{
                                rekamMedisLists.clearItemsData()
                                user.NIK = nik.text
                                user.createKey(nik.text,password.text)
                            }
                        }
                    }
                    Button{
                        id : register
                        text: "Register"
                        onClicked: stackView.push("register.qml")
                        visible: false //(user.advancedOption && !user.amIAdmin)
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
                    onClicked: {
                        user.amIAdmin = false
                        user.advancedOption = checked
                    }
                }
            }
        }
        Timer{
            interval: 1000
            repeat: false
            running: true
            triggeredOnStart: {
                if(window.isKeyValid){
                    if(user.amIAdmin){
                        stackView.replace("userList.qml")
                    }
                    else{
                        stackView.replace("rekamMedisList.qml")
                    }
                }
            }
        }
    }
}
