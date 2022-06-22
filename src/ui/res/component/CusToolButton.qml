import QtQuick 2.15

Item {
    id:root

    property alias icon : textIcon.text
    property alias color : textIcon.color
    signal clickEvent
    property alias iconSize: textIcon.font.pixelSize

    height: 30
    width: 30

    Rectangle{
        anchors.fill: parent
        color: mouseArea.containsMouse ? "#11000000" : "#00000000"
    }

    FontLoader {
        id: awesome
        source: "qrc:/font/iconfont.ttf"
    }

    Text {
        id:textIcon
        font.pixelSize: 20
        font.family: awesome.name
        color: "#BBB"
        anchors.centerIn: parent
    }

    MouseArea {
        id:mouseArea
        cursorShape: Qt.PointingHandCursor
        anchors.fill: parent
        hoverEnabled: true
        onClicked: clickEvent()
    }

}
