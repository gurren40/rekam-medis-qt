/**
MIT License

Copyright (c) 2017 Andrey Semenov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

import QtQuick 2.12
import QtQuick.Controls 1.4 as OldControls
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import Qt.labs.folderlistmodel 2.12
import QtQuick.Window 2.12
import "utils.js" as Utils
import QtQuick.Dialogs 1.2

Item {
	id:picker
	signal fileSelected(string fileName)
	readonly property real textmargin: Utils.dp(Screen.pixelDensity, 8)
	readonly property real textSize: Utils.dp(Screen.pixelDensity, 10)
	readonly property real headerTextSize: Utils.dp(Screen.pixelDensity, 12)
	readonly property real buttonHeight: Utils.dp(Screen.pixelDensity, 24)
	readonly property real rowHeight: Utils.dp(Screen.pixelDensity, 36)
	readonly property real toolbarHeight: Utils.dp(Screen.pixelDensity, 48)
	property bool showDotAndDotDot: false
	property bool showHidden: true
	property bool showDirsFirst: true
    property string folder: fileDialogUrl.pictures
    property variant nameFilters: ["*.jpg","*.jpeg"]

    FileDialog{
        id : fileDialogUrl
        visible: false
        property string pictures: shortcuts.pictures
    }

	function currentFolder() {
		return folderListModel.folder;
	}

	function isFolder(fileName) {
		return folderListModel.isFolder(folderListModel.indexOf(folderListModel.folder + "/" + fileName));
	}
	function canMoveUp() {
		return folderListModel.folder.toString() !== "file:///";
	}

	function onItemClick(fileName) {
		if(!isFolder(fileName)) {
            fileSelected(fileName)
            window.uploadImageURL = folderListModel.folder += "/" + fileName
            stackView.pop();
			return;
		}
		if(fileName === ".." && canMoveUp()) {
			folderListModel.folder = folderListModel.parentFolder
		} else if(fileName !== ".") {
			if(folderListModel.folder.toString() === "file:///") {
				folderListModel.folder += fileName
			} else {
				folderListModel.folder += "/" + fileName
			}
		}
	}
    RowLayout {
        id: toolbar
        height: toolbarHeight

        ToolButton {
			id: button
            icon.name: "back"
			enabled: canMoveUp()
            clip: true
			onClicked: {
				if(canMoveUp) {
					folderListModel.folder = folderListModel.parentFolder
				}
			}
		}
        Label {
			id: filePath
            text: folderListModel.folder.toString()
		}
	}

	FolderListModel {
		id:  folderListModel
        showDotAndDotDot: false
		showHidden: picker.showHidden
		showDirsFirst: picker.showDirsFirst
		folder: picker.folder
		nameFilters: picker.nameFilters
	}
	OldControls.TableView {
		id: view
		anchors.top: toolbar.bottom
		anchors.right: parent.right
		anchors.bottom: parent.bottom
		anchors.left: parent.left
        model: folderListModel
        headerDelegate: ItemDelegate{
            text: "Select Image"
            width: parent.width
            clip: true
            background: Rectangle{
                anchors.fill: parent
                color: "white"
            }
        }
		rowDelegate: Rectangle {
			height: rowHeight
		}

        OldControls.TableViewColumn {
            role: "fileName"
            resizable: true
            delegate: ItemDelegate{
                icon.name: !isFolder(model.fileName) ? "default" : "chevron_right"
                text: styleData.value !== undefined ? styleData.value : ""
                width: parent.width
                onClicked: onItemClick(text)
            }
        }
	}
}
