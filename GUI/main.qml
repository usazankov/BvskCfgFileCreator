import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import Qt.labs.platform 1.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.0
import QtQuick.Controls.Material 2.1
import "./qml"
ApplicationWindow {
    id:appWindow;
    visible: true
    width: 800
    height: 600
    title: qsTr("BvskCfgFileCreator")
    function normalMessage(txt){
        return "<span>"+txt+"</span>";
    }
    function errorMessage(txt){
        return "<span style='color:#CF5151'>"+txt+"</span>";
    }
    function goodMessage(txt){
        return "<span style='color:#008000'>"+txt+"</span>";
    }
    Component.onCompleted: {
        x = Screen.width / 2 - width / 2
        y = Screen.height / 2 - height / 2
    }
    Connections {
        target: errHandle
        onNewMessage: {
            if(tabView.count>0)
                if(tabView.getTab(tabView.currentIndex).item)
                    tabView.getTab(tabView.currentIndex).item.getMessagePanel().append(txt);
        }
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
        onActivated: tabView.getTab(tabView.currentIndex).item.getTextArea().copy()
    }
    Shortcut {
        sequence: StandardKey.Cut
        onActivated: tabView.getTab(tabView.currentIndex).item.getTextArea().cut()
    }
    Shortcut {
        sequence: StandardKey.Paste
        onActivated: tabView.getTab(tabView.currentIndex).item.getTextArea().paste()
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
                enabled: {
                    if(tabView.count>0)
                        if(tabView.getTab(tabView.currentIndex).item)
                            tabView.getTab(tabView.currentIndex).item.getTextArea().selectedText
                        else return false;
                    else return false;
                }
                onTriggered: tabView.getTab(tabView.currentIndex).item.getTextArea().copy()
            }
            MenuItem {
                text: qsTr("Cu&t")
                enabled: {
                    if(tabView.count>0)
                        if(tabView.getTab(tabView.currentIndex).item)
                            tabView.getTab(tabView.currentIndex).item.getTextArea().selectedText
                        else return false;
                    else return false;
                }
                onTriggered: tabView.getTab(tabView.currentIndex).item.getTextArea().cut()
            }
            MenuItem {
                text: qsTr("&Paste")
                enabled: {
                    if(tabView.count>0)
                        if(tabView.getTab(tabView.currentIndex).item)
                            tabView.getTab(tabView.currentIndex).item.getTextArea().canPaste
                        else return false;
                    else return false;
                }
                onTriggered: tabView.getTab(tabView.currentIndex).item.getTextArea().paste()
            }
        }
    }
    FileDialog {
        id: openDialog;
        nameFilters: ["Text files (*.txt)"]
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            var component = Qt.createComponent("doc.qml");
            if (component.status === Component.Ready){
                var t=tabView.addTab("", component);
                t.active=true;
                t.item.resources[0].load(file)
                t.title=t.item.resources[0].fileName
                tabView.currentIndex=tabView.count-1;
                errHandle.newMessage(normalMessage(t.item.resources[0].fileUrl.toString())+" <span style='color:#008000'>loaded</span>")
            }

        }
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
                    enabled: {
                        if(tabView.count>0)
                            if(tabView.getTab(tabView.currentIndex).item)
                                return tabView.getTab(tabView.currentIndex).item.getTextArea().selectedText;
                            else return false;
                        else return false;
                    }
                    onClicked: {
                        if(tabView.count>0)
                            tabView.getTab(tabView.currentIndex).item.getTextArea().copy()
                    }
                }
                ToolButton {
                    id: cutButton
                    text: "\uE802" // icon-scissors
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    enabled: {
                        if(tabView.count>0)
                            if(tabView.getTab(tabView.currentIndex).item)
                                 tabView.getTab(tabView.currentIndex).item.getTextArea().selectedText;
                            else return false;
                        else return false;
                    }
                    onClicked: {
                        if(tabView.count>0)
                            tabView.getTab(tabView.currentIndex).item.getTextArea().cut()
                    }
                }
                ToolButton {
                    id: pasteButton
                    text: "\uF0EA" // icon-paste
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    enabled: {
                        if(tabView.count>0)
                            if(tabView.getTab(tabView.currentIndex).item)
                                tabView.getTab(tabView.currentIndex).item.getTextArea().canPaste
                            else return false;
                        else return false;
                    }
                    onClicked: {
                        if(tabView.count>0)
                            tabView.getTab(tabView.currentIndex).item.getTextArea().paste()}
                }
                ToolSeparator {
                    //contentItem.visible: editRow.y === formatRow.y
                }
            }
            Row {
                id:confRow;

                ComboBox {
                    Material.elevation: 0
                    font.family: "fontello"
                    focusPolicy: Qt.TabFocus
                    width: 200
                    model: [ "Calibration", "Termocalibration"]
                }
                Button{
                    Material.elevation: 0
                    height: 50;
                    width:100;
                    text:"Start";
                    onClicked: {

                    }
                }
            }
        }
    }

    TabView {
        id:tabView;
        anchors.fill: parent;

        style: TabViewStyle {
            property color frameColor: "#999"
            property color fillColor: "white"
            property color notSelectedColor: "#eee"
            tabsMovable: true;
            frame: Rectangle {
                color: "white"
                border.color: tabView.count>0 ? frameColor : fillColor;
            }
            tab: Rectangle {
                color: styleData.selected ? fillColor : notSelectedColor
                implicitWidth: Math.max(text.width + 30, 80)
                implicitHeight: 40
                border.color: styleData.selected ? fillColor : frameColor
                Rectangle { height: 1 ; width: parent.width ; color: frameColor}
                Rectangle { height: parent.height ; width: 1; color: frameColor}
                Rectangle { x: parent.width -1; height: parent.height ; width: 1; color: frameColor}
                Text {
                    id: text
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 6
                    anchors.rightMargin: 10;
                    text: styleData.title
                    color: "black"
                }
                Button {
                    anchors.right: parent.right
                    anchors.topMargin: 10;
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.rightMargin:4;
                    height: 16;
                    background: Rectangle {
                        implicitWidth: 16
                        implicitHeight: 16
                        radius: width/2
                        color: control.hovered ? "#eee": "#ccc"
                        border.color: "gray"
                        Text {text: "X" ; anchors.centerIn: parent ; color: "gray"}
                    }
                    onClicked: tabView.removeTab(styleData.index)
                }
            }
        }
    }


}
