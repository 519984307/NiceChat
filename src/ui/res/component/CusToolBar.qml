import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import "../storage"
import "../view"


Rectangle {

    property string title
    property url logo
    property var window: Window.window
    property bool maxEnable: true
    property bool minEnable: true
    property bool closeEnable: true
    property bool darkEnable: true
    property bool topEnable: true
    property bool isTop : false
    color: Theme.colorBackground
    property var onCloseEvent

    clip: true
    height: window.getToolBarHeight()

    onIsTopChanged: {
        if(isTop){
            window.flags = window.flags | Qt.WindowStaysOnTopHint
        }else{
            window.flags = window.flags &~ Qt.WindowStaysOnTopHint
        }
    }

    anchors{
        left: parent.left
        right: parent.right
        top:parent.top
    }

    function toggleMaximized() {
        if (window.visibility === Window.Maximized) {
            window.showNormal();
        } else {
            window.showMaximized();
        }
    }

    Item {
        id:layout_top
        anchors.fill: parent

        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.NoButton
        }

        RowLayout {
            spacing: 5
            anchors.left: parent.left
            anchors.leftMargin: 8
            height: parent.height
            Image {
                sourceSize: Qt.size(15,15)
                source: logo
            }

            Text {
                text: title
                font.pixelSize: 12
                color:Theme.colorFontPrimary
            }
        }

        RowLayout {
            spacing: 0
            anchors.right: parent.right
            anchors.rightMargin: 5
            height: parent.height

            CusToolButton {
                id:btnDark
                icon: AppStorage.isDark ? "\ue6c9" : "\ue6e6"
                color: AppStorage.isDark ? "#FA9D16" : "#FA9D16"
                onClickEvent: {
                    AppStorage.isDark = !AppStorage.isDark
                }
                visible: darkEnable
                Component.onCompleted: Window.window.setHitTestVisible(btnDark, true)
            }

            CusToolButton {
                id:btnTop
                icon: "\ue770"
                onClickEvent: { isTop = !isTop }
                iconSize : 16
                visible: topEnable
                color: isTop ? Theme.colorPrimary : "#666"
                Component.onCompleted: Window.window.setHitTestVisible(btnTop, true)
            }

            CusToolButton {
                id:btnMin
                icon: "\ue664"
                onClickEvent: window.showMinimized()
                visible: minEnable
                iconSize : 14
                Component.onCompleted: Window.window.setHitTestVisible(btnMin, true)
            }
            CusToolButton {
                id:btnMax
                icon: window.visibility === Window.Maximized ? "\ue65d" : "\ue692"
                onClickEvent: window.toggleMaximized();
                visible: maxEnable
                iconSize : 14
                Component.onCompleted: Window.window.setHitTestVisible(btnMax, true)
            }
            CusToolButton {
                id:btnClose
                icon: "\ue6f4"
                onClickEvent: {
                    if(onCloseEvent)
                        onCloseEvent()
                    else
                        window.close()
                }
                hoverColor: "#E81123"
                hoverTextColor: "#FFFFFF"
                visible: closeEnable
                iconSize : 15
                Component.onCompleted: Window.window.setHitTestVisible(btnClose, true)
            }
        }
    }


}
