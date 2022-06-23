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
                onClicked: mainModelTest.doBinning()
            }

            ToolButton {
                text: qsTr("Export images")
                icon.name: "export-images"
                onClicked: exportFolderDialog.open()
            }

            ToolButton {
                text: qsTr("Remove images")
                icon.name: "remove-images"
                onClicked: mainModelTest.removeImages()
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
            mainModelTest.importImages(importFileDialog.selectedFiles)

            //image.source = importFileDialog.file
        }
    }

    FolderDialog {
        id: exportFolderDialog
        title: "Select folder to export images"
        onAccepted: {

            mainModelTest.exportImages(exportFolderDialog.selectedFolder)

            //mainModel.userName = exportFolderDialog.selectedFolder
            //console.log("Selected:" + exportFolderDialog.folder)
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
            mainModel: mainModelTest
        }

        orientation: ListView.Horizontal

        //delegate: RowLayout {
        //    width: parent.width

        //    CheckBox {
        //        checked: model.selected
        //        onClicked: model.selected = checked
        //    }

        //    TextField {
        //        text: model.url
        //        Layout.fillWidth: true
        //    }

        //    Image {
        //        id: thumbnailImage
        //        width: 100
        //        height: 100
        //        //fillMode: Image.PreserveAspectFit
        //        source: "image://colors/" + model.id
        //    }
        //}

        //orientation: ListView.Horizontal
        //delegate: ImageThumbnail {
        //    required property int index
        //    //required property QImage source
        //    width: 150
        //    //height: 100
        //    text: index
        //    function reload() {
        //        var oldSource = source;
        //        source = "";
        //        source = oldSource;
        //    }
        //}
        delegate: Rectangle {
            id: item
            width: 150
            height: 100

            Image {
                id: thumbnailImage
                fillMode: Image.PreserveAspectFit
                source: "image://colors/" + model.id
            }

            CheckBox {
                checked: true
            }
        }
    }
}
