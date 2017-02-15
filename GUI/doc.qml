import QtQuick 2.7
import QtQuick.Controls 2.1
import Qt.labs.platform 1.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import io.qt.BvskCfgFileCreatorGUI 1.0
import "./qml"

Item{
    id:mainItem;
    objectName: "aaa";
    property bool isBuild: false;

    function getTextArea(){
        return textArea;
    }
    function getMessagePanel(){
        return messagePanel;
    }
    resources:[
    DocumentHandler {
        id:document;
        objectName: "doc";

        document: textArea.textDocument
        onLoaded: {
            textArea.text = text
        }
        onError: {
            errorDialog.text = message
            errorDialog.visible = true
        }
    }
    ]
    SplitView{
        id:split;
        anchors.fill: parent;
        orientation: Qt.Vertical

        Flickable {
            Layout.minimumHeight: 100;
            Layout.fillHeight: true;
            id: flickable
            anchors.top:parent.top;
            anchors.left: parent.left;
            anchors.right: parent.right
            height: commandPanel.y;
            anchors.topMargin: 10;
            flickableDirection: Flickable.HorizontalAndVerticalFlick
            Rectangle {
                id:panelLine;
                width: areaCountLine.width;
                height: parent.height;
                color: "#d1d1d1"
                x:hBar.position*parent.width;
                TextArea{
                    id:areaCountLine;
                    textFormat: Qt.RichText
                    text:"1";
                    persistentSelection: true
                    selectByMouse: true
                    leftPadding: 20;
                    rightPadding: 20;
                    topPadding: 0
                    wrapMode: textArea.wrapMode;
                    readOnly: true;
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
                    anchors.fill: parent;
                    //cursorShape: Qt.IBeamCursor;
                    onClicked: contextMenu.open()
                }

                onLinkActivated: Qt.openUrlExternally(link)
            }

            ScrollBar.vertical: ScrollBar {
                id:vBar;
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
            Layout.minimumHeight: 100;
            Layout.maximumHeight: 500;
            anchors.bottom: parent.bottom

            Flickable {
                //anchors.bottom: parent.bottom
                id: flickable_messages;
                anchors.fill:parent;
                flickableDirection: Flickable.HorizontalAndVerticalFlick
                TextArea.flickable:TextArea{
                    id:messagePanel;
                    leftPadding: 10
                    rightPadding: 10
                    background: null;
                    textFormat: Qt.RichText
                    wrapMode: TextArea.WordWrap
                    focus: true;
                    font.pixelSize: 14;
                    selectByMouse: true
                    persistentSelection: true
                    readOnly: true;
                    //enabled: false;
                }
                ScrollBar.vertical: ScrollBar {
                    active: true;
                    onActiveChanged: {
                        active=true;
                    }
                }
            }
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
