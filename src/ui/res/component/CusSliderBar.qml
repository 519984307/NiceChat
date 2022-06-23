import QtQuick 2.15
import "../view"
import "../storage"

Rectangle {
    id:root

    property int curIndex: 0
    property alias model: listView.model
    property alias avatar: iconLogo.source

    width: 56
    height: parent.height
    anchors.left: parent.left
    color: "#FF2E2E2E"

    FontLoader {
        id: awesome
        source: "qrc:/font/iconfont.ttf"
    }

    Item{
        id:avatar
        width: 56
        height: 56
        anchors.top: parent.top

        Image{
            id:iconLogo
            width: 36
            height: 36
            source: "qrc:/image/ic_logo.png"
            anchors{
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 32
            }
        }

    }

    ListView{
        id:listView
        boundsBehavior: Flickable.StopAtBounds
        anchors{
            top:avatar.bottom
            topMargin: 36
            left: parent.left
            right:parent.right
            bottom: parent.bottom
        }
        delegate: Item{
            width: 56
            height: 40
            Text{
                anchors.centerIn: parent
                text:model.icon
                font.family: awesome.name
                color:curIndex === model.index ? Theme.colorPrimary : "#999999"
                font.pixelSize: model.fontSize
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    curIndex = model.index
                }
            }
        }
    }

    function getUrl(){
        return sliderModel.get(curIndex).url
    }

}
