import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import "../global/global.js" as Global
import "../storage"
import "../component"
import "../view"

Item {

    property var friends : JSON.parse(IM.friends).friends

    property var user: friends[friendListView.currentIndex]

    signal clickSend(var user)

    FontLoader {
        id: awesome
        source: "qrc:/font/iconfont.ttf"
    }

    Rectangle{
        anchors.fill: friendListView
        color:Theme.colorBackground2
    }

    ListView{
        id:friendListView
        property color hoverItemColor : Qt.darker(Theme.colorBackground2,1.1)
        property color checkItemColor : Qt.darker(Theme.colorBackground2,1.2)
        height: parent.height
        anchors{
            left: parent.left
            right: centerDivder.left
        }
        boundsBehavior: Flickable.StopAtBounds
        model: friends
        delegate: Rectangle{
            color: {
                if(ListView.isCurrentItem){
                    return friendListView.checkItemColor
                }
                return itemMouse.containsMouse ? friendListView.hoverItemColor : Theme.colorBackground2
            }
            height: 60
            width: friendListView.width

            CusAvatar{
                id:itemAvatar
                avatarName: modelData.name.charAt(0)
                avatar: modelData.icon
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: 12
                }
            }

            Text {
                text: modelData.name
                color: Theme.colorFontPrimary
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: itemAvatar.right
                    leftMargin: 12
                }
            }
            MouseArea{
                id:itemMouse
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    friendListView.currentIndex = index
                }
            }
        }
    }

    Rectangle{
        id:centerDivder
        color : Theme.colorDivider
        width: 1
        height: parent.height
        anchors{
            left: parent.left
            leftMargin: 250
        }
    }

    Rectangle{
        id:layoutPanel
        color: Theme.colorBackground1
        anchors{
            left:centerDivder.right
            right: parent.right
        }
        height: parent.height
    }

    Item {
        anchors{
            horizontalCenter: layoutPanel.horizontalCenter
        }
        width: 340
        height: layoutPanel.height

        ColumnLayout{

            width: parent.width

            Item{
                width: parent.height
                height: childrenRect.height
                Layout.topMargin: 100

                CusAvatar{
                    id:avatar
                    width: 58
                    height: 58
                    avatar: Global.toString(user.icon)
                    avatarName: user.name.charAt(0)
                }

                Text{
                    text:Global.toString(user.name)
                    anchors{
                        left:avatar.right
                        leftMargin: 14
                        top: avatar.top
                    }
                    color:Theme.colorFontPrimary
                    font.pixelSize: 18
                }

            }


            Rectangle{
                width: parent.width
                height: 1
                color:Theme.colorDivider
            }

            PrimaryButton{
                width: 180
                text:"发消息"
                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 20
                onClicked: {
                    clickSend(user)
                }
            }
        }
    }
}
