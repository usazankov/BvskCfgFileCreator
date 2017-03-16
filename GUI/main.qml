import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.1
import Qt.labs.platform 1.0
import QtQuick.Controls.Material 2.1
import io.qt.BvskCfgFileCreatorGUI 1.0
import QtQuick.Layouts 1.0
import "./qml"
ApplicationWindow {
    id:appWindow;
    visible: true
    width: 800
    height: 600
    property string globalFont: "fontello";

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
    function createDoc(fileUrls){
        var component = Qt.createComponent("doc.qml");
        if (component.status === Component.Ready){
            var t=tabView.addTab("", component);
            t.active=true;
            t.item.resources[0].load(fileUrls);
            t.title=t.item.resources[0].fileName;
            tabView.currentIndex=tabView.count-1;
        }
    }
    function createDocFromTxt(txt){
        var component = Qt.createComponent("doc.qml");
        if (component.status === Component.Ready){
            var t=tabView.addTab("", component);
            t.active=true;
            t.item.resources[0].loaded(txt);
            t.title="Bvsk.cfg";
            tabView.currentIndex=tabView.count-1;
        }
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

    /*MenuBar {
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
    }*/
    FileDialog {
        id: openDialog;
        fileMode: FileDialog.OpenFiles
        nameFilters: ["Text files (*.txt)"];
        onAccepted: {
            createDoc(currentFiles);
        }
    }
    FileDialog {
        id: saveDialog
        fileMode: FileDialog.SaveFile
        defaultSuffix: document.fileType
        nameFilters: ["Cfg files (*.cfg)"];
        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: controller.saveResultToFile(file)
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
                    //text: "\uF115" // icon-folder-open-empty
                    text: "\uF115"
                    font.family: globalFont
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
                    font.family: globalFont
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
                    font.family: globalFont
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
                    font.family: globalFont
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
                spacing: 10;
                ComboBox {
                    id:comboBoxType;
                    Material.elevation: 0
                    font.family: globalFont;
                    font.pixelSize: 14;
                    focusPolicy: Qt.TabFocus
                    width:200;
                    model: [ "Calibration", "Termocalibration"]
                }
                Button{
                    Material.elevation: 0
                    height: 50;
                    width:100;
                    text:"Start";
                    font.family: globalFont;
                    font.pixelSize: 14;
                    font.capitalization: Font.MixedCase
                    onClicked: {
                        controller.docHandler=tabView.getTab(tabView.currentIndex).item.resources[0];
                        controller.typeProcess=comboBoxType.currentIndex;
                        if(controller.typeProcess==0){
                            if(controller.process()){
                                createDocFromTxt(controller.result);
                            }
                        }

                    }
                }
                Button{
                    id:saveButton;
                    Material.elevation: 0
                    height: 50;
                    width:100;
                    enabled: false;
                    text:"Save";
                    font.family: globalFont;
                    font.pixelSize: 14;
                    font.capitalization: Font.MixedCase
                    onClicked: {
                        controller.docHandler=tabView.getTab(tabView.currentIndex).item.resources[0];
                        saveDialog.open();
                    }
                }
            }
        }
    }




    TabView {
        id:tabView;
        anchors.fill: parent;
        anchors.topMargin: 4;
        style: TabViewStyle {
            property color frameColor: "#999"
            property color fillColor: "white"
            property color notSelectedColor: "#eee"
            frameOverlap: 1
            tabsMovable: true;
            frame: Rectangle {
                color: "white"
                border.color: tabView.count>0 ? frameColor : fillColor;
            }
            tab: Rectangle {
                color: styleData.selected ? fillColor : notSelectedColor
                implicitWidth: Math.max(text.width + 30, 80)
                implicitHeight: 40
                anchors.top: frame.bottom;
                border.color: frameColor;
                Rectangle{y:parent.height-1; width: parent.width-1; height: 1; x:parent.x+1; color: styleData.selected ? fillColor: frameColor;}
                Text {
                    id: text
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 6
                    anchors.rightMargin: 10;
                    text: styleData.title
                    color: Material.foreground;
                    font.family: globalFont;
                    font.pixelSize: 14;
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
        onCurrentIndexChanged: {
            var num=tabView.getTab(tabView.currentIndex).title.indexOf(".cfg");
            if(num!==-1)
                saveButton.enabled=true;
            else
                saveButton.enabled=false;
        }
    }
}
