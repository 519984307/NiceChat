import QtQuick 2.15

Item {
    id:root

    property alias icon : textIcon.text
    property color color : "#666"
    signal clickEvent
    property alias iconSize: textIcon.font.pixelSize

    property color normalColor : "#00000000"
    property color hoverColor: "#11000000"

    property color hoverTextColor : color

    height: 30
    width: 30

    FontLoader {
        id: awesome
        source: "qrc:/font/iconfont.ttf"
    }

    Rectangle{
        anchors.fill: parent
        color: mouseArea.containsMouse ? hoverColor : normalColor
    }

    MouseArea {
        id:mouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: clickEvent()
    }

    Text {
        id:textIcon
        font.pixelSize: 20
        font.family: awesome.name
        color: mouseArea.containsMouse ? hoverTextColor : root.color
        anchors.centerIn: parent
    }

}
