import QtQuick 2.15
import QtGraphicalEffects 1.15
import "../view"
import "../storage"

Item {
    id:layoutAvatar

    width: 42
    height: 42

    property alias avatar: iconAvatar.source
    property alias avatarName: textAvatar.text
    signal clickAvatar

    Image{
        id:iconAvatar
        width: layoutAvatar.width
        height: layoutAvatar.height
        visible: false
        smooth: false
        mipmap: true
        cache: true
    }

    Rectangle{
        id: mask
        anchors.fill: iconAvatar
        radius: 4
        visible: false
    }

    OpacityMask {
        anchors.fill: iconAvatar
        source: iconAvatar
        maskSource: mask
    }


    Rectangle{
        color:Theme.colorPrimary
        anchors.fill: iconAvatar
        radius: 4
        visible: iconAvatar.status != Image.Ready
        Text {
            id:textAvatar
            anchors.centerIn: parent
            color: "#FFFFFF"
            font.pixelSize: 14
        }
    }

    Rectangle{
        color: "#00000000"
        anchors.fill: iconAvatar
        radius: 4
        border{
            color: Theme.colorPrimary
            width: 2
        }
    }

    MouseArea{
        anchors.fill: iconAvatar
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            clickAvatar()
        }
    }

}
