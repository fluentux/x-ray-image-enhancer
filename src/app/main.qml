import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls.Material 2.0
import XRayImageEnhancer;

import ImageList 1.0;

ApplicationWindow {
    id: mainWindow
    width: 800
    height: 600
    visible: true
    title: qsTr("X-ray Image Enhancer")

    background: Rectangle {
        color: "#444343"
    }

    header: ToolBar {
        id: toolbar
        Material.foreground: "white"
        Material.background: "#444343"
        Material.accent: "#303030"

        Flow {
            anchors.fill: parent

            Rectangle {
               id: logo
               width: 50
               height: 50
               color: "#444343"
            }

            ToolButton {
                text: qsTr("Import images")
                icon.name: "import-images"
                onClicked: importFileDialog.open()
            }

            ToolButton {
                text: qsTr("Export images")
                icon.name: "export-images"
                onClicked: exportFolderDialog.open()
            }

            ToolButton {
                text: qsTr("Remove images")
                icon.name: "remove-images"
                onClicked: mainModelContext.removeImages()
            }
        }
    }

    Rectangle {
        id: leftButtonPanel
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 55
        color: "#303030"

        ToolButton {
            x: 0
            y: 30
            text: qsTr("Binning")
            icon.name: "binning"
            onClicked: mainModelContext.doBinning()
        }
    }

    FileDialog {
        id: importFileDialog
        title: "Select image files"
        fileMode: FileDialog.OpenFiles
        nameFilters: [
            "Bitmap image files (*.bmp)"
        ]
        onAccepted: {
            mainModelContext.importImages(importFileDialog.selectedFiles)
        }
    }

    FolderDialog {
        id: exportFolderDialog
        title: "Select folder to export images"
        onAccepted: {
            mainModelContext.exportImages(exportFolderDialog.selectedFolder)
        }
    }

    Image {
        id: mainImage
        anchors {
            top: parent.top
            left: leftButtonPanel.right
            right: parent.right
            bottom: thumbnailListView.top
            bottomMargin: 5
            topMargin: 5
        }
        fillMode: Image.PreserveAspectFit
        asynchronous: true
        source: ""
    }

    ListView {
        id: thumbnailListView
        height: 100
        clip: true

        anchors {
            left: leftButtonPanel.right
            right: parent.right
            bottom: parent.bottom
            bottomMargin: 5
            leftMargin: 5
            rightMargin: 5
        }

        model: ImageListModel {
            mainModel: mainModelContext
        }

        orientation: ListView.Horizontal

        spacing: 5

        delegate: Rectangle {
            id: item
            width: 150
            height: 100

            Image {
                id: thumbnailImage
                fillMode: Image.PreserveAspectFit
                source: "image://images/" + model.id
                anchors.centerIn: parent
                width: 100
                height: 100

                Connections {
                    target: mainModelContext
                    function onUpdateImage(id) {
                        if (model.id === id) {
                            thumbnailImage.source = "image://images/" + model.id + Date.now()
                        }
                    }
                }
            }

            CheckBox {
                id: selectedCheckBox
                checked: model.selected
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    model.selected = !selectedCheckBox.checked

                    mainImage.source = thumbnailImage.source + Date.now()
                }
            }
        }
    }
}
