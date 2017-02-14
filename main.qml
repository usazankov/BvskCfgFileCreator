import QtQuick 2.7
import QtQuick.Controls 2.1
import Qt.labs.platform 1.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0
import io.qt.BvskCfgCreatorGUI 1.0
import "./qml"
ApplicationWindow {
    id:appWindow;
    visible: true
    width: 640
    height: 480
    title: qsTr("BvskCfgCreator")
    Component.onCompleted: {
        x = Screen.width / 2 - width / 2
        y = Screen.height / 2 - height / 2
    }
    Shortcut {
        sequence: StandardKey.Open
        onActivated: openDialog.open()
    }
    Shortcut {
        sequence: StandardKey.Quit
        onActivated: Qt.quit()
    }
    Shortcut {
        sequence: StandardKey.Copy
        onActivated: textArea.copy()
    }
    Shortcut {
        sequence: StandardKey.Cut
        onActivated: textArea.cut()
    }
    Shortcut {
        sequence: StandardKey.Paste
        onActivated: textArea.paste()
    }
    MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: openDialog.open()
            }
            MenuItem {
                text: qsTr("&Save As...")
                onTriggered: saveDialog.open()
            }
            MenuItem {
                text: qsTr("&Quit")
                onTriggered: Qt.quit()
            }
        }

        Menu {
            title: qsTr("&Edit")

            MenuItem {
                text: qsTr("&Copy")
                enabled: textArea.selectedText
                onTriggered: textArea.copy()
            }
            MenuItem {
                text: qsTr("Cu&t")
                enabled: textArea.selectedText
                onTriggered: textArea.cut()
            }
            MenuItem {
                text: qsTr("&Paste")
                enabled: textArea.canPaste
                onTriggered: textArea.paste()
            }
        }
    }
    FileDialog {
        id: openDialog;
        nameFilters: ["Text files (*.txt)", "HTML files (*.html *.htm)"]
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: document.load(file)
    }
    header: ToolBar {
        leftPadding: 8
        Flow {
            id: flow
            width: parent.width

            Row {
                id: fileRow
                ToolButton {
                    id: openButton
                    text: "\uF115" // icon-folder-open-empty
                    font.family: "fontello"
                    onClicked: openDialog.open()
                }
                ToolSeparator {
                    contentItem.visible: fileRow.y === editRow.y
                }
            }

            Row {
                id: editRow
                ToolButton {
                    id: copyButton
                    text: "\uF0C5" // icon-docs
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    enabled: textArea.selectedText
                    onClicked: textArea.copy()
                }
                ToolButton {
                    id: cutButton
                    text: "\uE802" // icon-scissors
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    enabled: textArea.selectedText
                    onClicked: textArea.cut()
                }
                ToolButton {
                    id: pasteButton
                    text: "\uF0EA" // icon-paste
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    enabled: textArea.canPaste
                    onClicked: textArea.paste()
                }
                ToolSeparator {
                    //contentItem.visible: editRow.y === formatRow.y
                }
            }
        }
    }
    DocumentHandler {
        id: document
        document: textArea.textDocument
        onLoaded: {
            textArea.text = text
        }
        onError: {
            errorDialog.text = message
            errorDialog.visible = true
        }
    }

    SplitView{
        anchors.fill: parent
        orientation: Qt.Vertical
        Flickable {
            Layout.minimumHeight: 100;
            Layout.fillHeight: true;
            id: flickable
            anchors.top:parent.top;
            anchors.left: parent.left;
            anchors.right: parent.right
            height: commandPanel.y;
            flickableDirection: Flickable.HorizontalAndVerticalFlick

            Rectangle {
                id:panelLine;
                width: areaCountLine.width;
                height: parent.height;
                color: "#d1d1d1"
                x:hBar.position*parent.width;

                TextArea{
                    id:areaCountLine;
                    textFormat: textArea.textFormat;
                    text:"1";
                    persistentSelection: true;
                    leftPadding: 20;
                    rightPadding: 20;
                    topPadding: 0
                    //horizontalAlignment: TextEdit.AlignRight;

                    wrapMode: textArea.wrapMode;
                    enabled: false;
                    background: null;
                    bottomPadding: textArea.bottomPadding;
                }
            }
            TextArea.flickable: TextArea {
                id: textArea
                x:panelLine.width;
                textFormat: Qt.RichText
                wrapMode: TextArea.NoWrap

                focus: true
                selectByMouse: true
                persistentSelection: true
                // Different styles have different padding and background
                // decorations, but since this editor is almost taking up the
                // entire window, we don't need them.
                leftPadding: 10
                rightPadding: 100
                topPadding: 0
                bottomPadding: 20
                background: null
                onLineCountChanged: {
                    var text="";
                    for(var i=0;i<textArea.lineCount;++i)
                        text+=i+1+"<br>";
                    areaCountLine.text=text;
                }
                MouseArea {
                    acceptedButtons: Qt.RightButton
                    anchors.fill: parent
                    onClicked: contextMenu.open()
                }

                onLinkActivated: Qt.openUrlExternally(link)
            }

            ScrollBar.vertical: ScrollBar {
                active: true;
                onActiveChanged: {
                    active=true;
                }

            }
            ScrollBar.horizontal: ScrollBar{
                id:hBar;
                active: true;
                onActiveChanged: {
                    active=true;
                }
            }
        }
        Rectangle{
            id:commandPanel;
        //height: 10;
        //width: 100;

        Layout.minimumHeight: 100;
        Layout.maximumHeight: 500;
        anchors.bottom: parent.bottom
        }
    }
    Menu {
        id: contextMenu

        MenuItem {
            text: qsTr("Copy")
            enabled: textArea.selectedText
            onTriggered: textArea.copy()
        }
        MenuItem {
            text: qsTr("Cut")
            enabled: textArea.selectedText
            onTriggered: textArea.cut()
        }
        MenuItem {
            text: qsTr("Paste")
            enabled: textArea.canPaste
            onTriggered: textArea.paste()
        }
        MenuItem {
            text: qsTr("Count")
            enabled: true;
            onTriggered: console.log(textArea.lineCount);
        }
    }
}
