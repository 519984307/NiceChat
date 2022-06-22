import QtQuick 2.15
import "../storage"

Rectangle {

    id:layoutButton
    property string text : "Button"
    property color backColor: AppStorage.isDark ? "#333333" : "#FFF6F8FA"
    property color hoveColor: Qt.darker(backColor,1.3)
    radius: 5
    border{
        width: 1
        color:Theme.colorDivider
    }
    color: mouseButton.containsMouse ? hoveColor : backColor
    width: textButton.width+20
    height: textButton.height+16
    antialiasing: true
    smooth: true
    signal clicked

    Text{
        id:textButton
        text: layoutButton.text
        font.bold: true
        anchors.centerIn: parent
        color: Theme.colorFontPrimary
        font.pixelSize: 12
    }

    MouseArea{
        id:mouseButton
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        hoverEnabled: true
        onClicked:layoutButton.clicked()
    }

}
