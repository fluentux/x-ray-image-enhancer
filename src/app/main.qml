import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import XRayImageEnhancer;

import ImageList 1.0;

ApplicationWindow {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("X-ray Image Enhancer")

    background: Rectangle {
        color: "#444343"
    }

    header: ToolBar {
        Flow {
            anchors.fill: parent

            ToolButton {
                text: qsTr("Import images")
                icon.name: "import-images"
                onClicked: importFileDialog.open()
            }

            ToolButton {
                text: qsTr("Binning")
                icon.name: "binning"
                onClicked: mainModelContext.doBinning()
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
        id: image
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        asynchronous: true
    }

    ListView {
        implicitWidth: 100
        implicitHeight: 100
        clip: true

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        model: ImageListModel {
            mainModel: mainModelContext
        }

        orientation: ListView.Horizontal

        delegate: Rectangle {
            id: item
            width: 150
            height: 100

            Image {
                id: thumbnailImage
                fillMode: Image.PreserveAspectFit
                source: "image://images/" + model.id
            }

            CheckBox {
                checked: true
            }
        }
    }
}
