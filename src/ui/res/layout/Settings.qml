import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import Controller 1.0
import "../component"
import "../storage"

CusWindow {
    id:window
    width: 550
    height: 470
    title: "设置"

    Component.onCompleted: {
        resizable = false
    }

    page: CusPage{

        CusToolBar {
            id:toolBar
            maxEnable: false
            darkEnable: false
            topEnable: false
            isTop: false
            title:window.title
        }

        ListModel{
            id:settinsModel
            ListElement{
                text:"账号设置"
            }
            ListElement{
                text:"通用设置"
            }
            ListElement{
                text:"关于"
            }
        }


        Rectangle{
            id:divider
            width: 1
            color:Theme.colorDivider
            anchors{
                right: settingListView.right
                top: settingListView.top
                bottom: settingListView.bottom
                topMargin: 9
            }
        }

        ListView{
            id:settingListView
            width: 110
            anchors{
                top: toolBar.bottom
                topMargin: 50
                bottom:parent.bottom
                left:parent.left
            }
            model:settinsModel
            delegate: Item{
                width: settingListView.width
                height: 30
                Text{
                    text:model.text
                    color:settingListView.currentIndex === index ? Theme.colorPrimary : Theme.colorFontPrimary
                    font.pixelSize: 13
                    anchors.centerIn: parent
                }
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        settingListView.currentIndex = index
                    }
                }
                Rectangle{
                    width: 1
                    color:settingListView.currentIndex === index ? Theme.colorPrimary : "#00000000"
                    anchors{
                        right: parent.right
                        top: parent.top
                        topMargin: 9
                        bottomMargin: 8
                        bottom: parent.bottom
                    }
                }
            }
        }

        Loader{
            id:loader
            anchors{
                left: divider.right
                right: parent.right
                top: divider.top
                bottom: divider.bottom
            }
            sourceComponent: {
                switch(settingListView.currentIndex){
                case 0:
                    return comp_account
                case 1:
                    return comp_common
                case 2:
                    return comp_about
                }
            }
        }

    }

    Component{
        id:comp_account
        Item{
            anchors.fill: parent

            Rectangle{
                width: 300
                height: 150
                radius: 5
                color:Theme.colorBackground
                anchors{
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                }

                CusAvatar{
                    id:avatar
                    width: 50
                    height: 50
                    avatar: IM.profile.icon
                    avatarName: IM.profile.name.charAt(0)
                    anchors{
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: 20
                    }
                }

                Text{
                    text:IM.profile.name
                    anchors{
                        top: avatar.top
                        left: avatar.right
                        leftMargin: 20
                    }
                    color:Theme.colorFontPrimary
                    font.pixelSize: 18
                }

                Text{
                    text:"账号：%1".arg(IM.profile.id)
                    anchors{
                        bottom: avatar.bottom
                        left: avatar.right
                        leftMargin: 20
                    }
                    color:Theme.colorFontTertiary
                    font.pixelSize: 11
                }


            }

            CusButton{
                width: 100
                text: "退出登录"
                anchors{
                    horizontalCenter: parent.horizontalCenter
                    bottom:parent.bottom
                    bottomMargin: 80
                }
                onClicked: {
                    dialog.open()
                }
            }

        }
    }

    Component{
        id:comp_common
        Item{
            anchors.fill: parent
        }
    }

    Component{
        id:comp_about
        Item{
            anchors.fill: parent
        }
    }

    CusTextDialog {
        id: dialog
        onClickLeft: {
            UIHelper.restart()
        }
    }

}
