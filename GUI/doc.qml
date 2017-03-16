import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls 1.4 as Controls
import io.qt.BvskCfgFileCreatorGUI 1.0
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.1
import "./qml"

Item{
    id:mainItem;
    objectName: "aaa";
    property bool isBuild: false;
    property string fontTextArea: "fontello";
    property int fontSize: 14;
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
        textColor: Material.foreground;
        backgroundColor: "#ffffff";
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
        Rectangle {
            Layout.minimumHeight: 100;
            Layout.fillHeight: true;
            anchors.top:parent.top;
            anchors.left: parent.left;
            anchors.right: parent.right
            height: commandPanel.y;
            id:panelLine;
            color: "#d1d1d1"
            Controls.TextArea {
                id: textArea
                anchors.fill: parent;
                //textFormat: Qt.RichText
                wrapMode: TextArea.NoWrap
                focus: true
                selectByMouse: true
                font.family: fontTextArea;
                font.pixelSize: fontSize;
                /*onLineCountChanged: {
                    var text="";
                    for(var i=0;i<textArea.lineCount;++i)
                        text+=i+1+"\n";
                    areaCountLine.text=text;
                }*/
            }
        }
        Rectangle{
            id:commandPanel;
            Layout.minimumHeight: 100;
            Layout.maximumHeight: 500;
            anchors.bottom: parent.bottom
                Controls.TextArea{
                    id:messagePanel;
                    anchors.fill: parent;
                    textFormat: Qt.RichText
                    textColor: Material.foreground;
                    wrapMode: TextArea.WordWrap
                    focus: true;
                    font.pixelSize: fontSize;
                    selectByMouse: true
                    readOnly: true;
                    font.family: fontTextArea;
                }
        }
    }
}
