import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls.Material 2.0
import XRayImageEnhancer;

ApplicationWindow {
    id: mainWindow
    width: 800
    height: 600
    minimumWidth: 300
    minimumHeight: 100
    visible: true
    title: qsTr("X-ray Image Enhancer")

    Material.theme: Material.Dark

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
               width: 55
               height: 55
               color: "#333232"
               Image {
                   id: logoImage
                   source: "img/x.png"
                   anchors.centerIn: parent
               }
            }

            ToolButton {
                text: qsTr("Import")
                icon.name: "import"
                icon.source: "img/import.png"
                onClicked: importFileDialog.open()
                display: AbstractButton.TextUnderIcon
            }

            ToolButton {
                text: qsTr("Export")
                icon.name: "export"
                icon.source: "img/export.png"
                onClicked: exportFolderDialog.open()
                display: AbstractButton.TextUnderIcon
            }

            ToolButton {
                text: qsTr("Remove")
                icon.name: "remove"
                icon.source: "img/remove.png"
                onClicked: mainModelContext.removeImages()
                display: AbstractButton.TextUnderIcon
            }

            ToolButton {
                text: qsTr("Reset")
                icon.name: "reset"
                icon.source: "img/reset.png"
                onClicked: mainModelContext.resetChanges()
                display: AbstractButton.TextUnderIcon
            }
        }
    }

    Rectangle {
        id: leftButtonPanel
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 55
        color: "#303030"
        Material.foreground: "white"
        Material.background: "#444343"
        Material.accent: "#303030"

        ToolButton {
            id: binningButton
            text: qsTr("Binning")
            icon.source: "img/binning.png"
            onClicked: mainModelContext.doBinning()
            display: AbstractButton.TextUnderIcon
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

    GridView {
        id: imageGridView
        width: 500
        height: 500

        clip: true

        anchors {
            top: parent.top
            left: leftButtonPanel.right
            right: parent.right
            bottom: thumbnailImageListView.top
            margins: 5
        }

        model: imageFilterProxyModelContext

        property int rowCount: count > 1 ? 2 : 1
        property int columnCount: count > 2 ? 2 : 1

        cellWidth: imageGridView.width / rowCount
        cellHeight: imageGridView.height / columnCount

        delegate: Rectangle {
            id: imageItem

            color: "#262626"

            property int margin: 5

            x: margin
            y: margin
            width: imageGridView.cellWidth - margin
            height: imageGridView.cellHeight - margin

            Image {
                id: image
                fillMode: Image.PreserveAspectFit
                source: "image://images/" + model.id
                anchors.centerIn: parent
                width: parent.width
                height: parent.height

                Connections {
                    target: mainModelContext
                    function onUpdateImage(id) {
                        if (model.id === id) {
                            image.source = "image://images/" + model.id + Date.now()
                        }
                    }
                }
            }
        }
    }

    ListView {
        id: thumbnailImageListView
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

        model: imageListModelContext
        orientation: ListView.Horizontal
        spacing: 5

        delegate: Rectangle {
            id: imageThumbnailItem
            width: 150
            height: 100

            color: "#262626"

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
                visible: model.selected

                indicator: Rectangle {
                  implicitWidth: 16
                  implicitHeight: 16
                  x: 2
                  y: 2
                  radius: 4

                  color: selectedCheckBox.down ? selectedCheckBox.palette.light : selectedCheckBox.palette.base
                  border.width: selectedCheckBox.visualFocus ? 2 : 1
                  border.color: selectedCheckBox.visualFocus ? selectedCheckBox.palette.highlight : selectedCheckBox.palette.mid

                  ColorImage {
                      x: 2
                      y: 2
                      defaultColor: "#353637"
                      color: "black"
                      source: "img/check.png"
                      visible: selectedCheckBox.checkState === Qt.Checked
                  }
                  Rectangle {
                      x: 2
                      y: 2
                      width: 16
                      height: 3
                      color: selectedCheckBox.palette.text
                      visible: selectedCheckBox.checkState === Qt.PartiallyChecked
                  }
              }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    model.selected = !selectedCheckBox.checked
                }
            }
        }
    }
}
