import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: "Rekam Medis"
    property bool isKeyValid: user.isLoggedIn
    property string uploadImageURL: ""
    property string notify: user.notify

    function logOut(){
        drawer.close()
        user.logOut()
        stackView.replace("login.qml")
    }

    Dialog{
        id : notifyDialog
        modal: true
        anchors.centerIn: parent
        title: "Notifikasi"
        contentItem: Label{
            id : alertlabel
            text: window.notify
        }
        standardButtons: Dialog.Ok
        onAccepted: {
            console.log("berhasil dibuat")
            stackView.pop()
        }
    }

    onNotifyChanged: {
        if(user.enableNotify){
            notifyDialog.open()
        }
    }

    Shortcut {
        sequences: ["Esc", "Back"]
        onActivated: {
            if(stackView.depth > 1){
                stackView.pop()
            }
        }
    }

    onIsKeyValidChanged:{
        if(!isKeyValid){
            logOut()
        }
    }

    header: ToolBar {
        visible: isKeyValid
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            icon.name: (stackView.depth > 1) ? "chevron_left" : "menu"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: stackView.currentItem.title
            anchors.centerIn: parent
            font.bold: true
        }

        ToolButton {
            id: menuButton
            icon.name: "refresh"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            anchors.right: parent.right
            onClicked: {
                rekamMedisLists.getRekamMedisList()
            }
        }
    }

    Drawer {
        id: drawer
        interactive: isKeyValid
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: user.username
                width: parent.width
            }
            ItemDelegate {
                text: qsTr("Masukkan Rekam Medis")
                width: parent.width
                onClicked: {
                    stackView.push("createRM.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Hitung Dosis")
                width: parent.width
                onClicked: {
                    stackView.push("hitung.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Pengaturan")
                width: parent.width
                onClicked: {
                    stackView.push("settings.qml")
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Log Out")
                width: parent.width
                onClicked: {
                    window.logOut()
                }
            }
            ItemDelegate {
                text: qsTr("Keluar")
                width: parent.width
                onClicked: {
                    Qt.quit()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "login.qml"
        anchors.fill: parent
    }
}
