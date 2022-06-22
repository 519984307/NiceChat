import QtQuick 2.15
import "../view"
import "../storage"

Rectangle {
    id:root

    property int curIndex: 0
    property alias model: listView.model

    width: 70
    height: parent.height
    anchors.left: parent.left
    color: Theme.colorBackground

    FontLoader {
        id: awesome
        source: "qrc:/font/iconfont.ttf"
    }

    Item{
        id:layout_logo
        width: 70
        height: 70
        anchors.top: parent.top

        Image{
            id:iconLogo
            width: 36
            height: 36
            source: "qrc:/image/ic_logo.png"
            anchors{
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 14
            }
        }

        Text {
            id:iconTitle
            text: qsTr(UIHelper.appName())
            color: Theme.colorPrimary
            font.pixelSize: 12
            anchors{
                horizontalCenter: parent.horizontalCenter
                top: iconLogo.bottom
                topMargin: 3
            }
        }

    }


    ListView{
        id:listView
        boundsBehavior: Flickable.StopAtBounds
        anchors{
            top:layout_logo.bottom
            left: parent.left
            right:parent.right
            bottom: parent.bottom
        }
        delegate: Item{
            width: 70
            height: 50
            Text{
                anchors.centerIn: parent
                text:model.icon
                font.family: awesome.name
                color:curIndex === model.index ? Theme.colorPrimary : Theme.colorFontPrimary
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
