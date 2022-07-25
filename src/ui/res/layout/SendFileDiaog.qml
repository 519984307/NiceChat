import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import "../component"
import "../storage"


Dialog {
    id: dialog
    anchors.centerIn: parent
    modal: Qt.WindowModal
    closePolicy: Popup.NoAutoClose
    width: 320
    height: 320

    property var user
    property alias model: file_list_view.model

    signal clickLeft
    signal clickRight

    background: Item {
        Rectangle{
            id:background_layout
            anchors.fill: parent
            color: Theme.colorBackground
        }

        DropShadow{
            anchors.fill: background_layout
            radius: 8.0
            samples: 17
            color: AppStorage.isDark ? "#80FFFFFF" : "#80000000"
            source: background_layout
        }
    }


    Text{
        id:title
        text:"发送给："
        font.pixelSize: 15
        anchors{
            top: parent.top
            left: parent.left
            topMargin: 16
            leftMargin: 16
        }
        color:Theme.colorFontPrimary
    }

    CusAvatar{
        id:avatar
        width: 38
        height: 38
        avatar: user.icon
        avatarName: user.name.charAt(0)
        anchors{
            top: title.bottom
            topMargin: 10
            left: title.left
        }
    }

    Text{
        font.pixelSize: 12
        text: user.name

        color:Theme.colorFontPrimary
        anchors{
            verticalCenter: avatar.verticalCenter
            left:avatar.right
            leftMargin: 14
        }
    }


    Rectangle{
        id:divider
        color:Theme.colorDivider
        height: 1
        anchors{
            top: avatar.bottom
            left: parent.left
            right: parent.right
            leftMargin: 16
            rightMargin: 16
            topMargin: 10
        }
    }

    ListView{
        id:file_list_view
        anchors{
            topMargin: 10
            top: divider.bottom
            left: divider.left
            right: divider.right
            bottom:left_btn.top
            bottomMargin: 10
        }
        boundsBehavior: Flickable.StopAtBounds
        clip: true
        ScrollBar.vertical: ScrollBar {}
        delegate: Item{

            width: file_list_view.width
            height: 60

            Image {
                id:item_icon
                width: 33
                height: 40.5
                source: model.icon
                fillMode: Image.PreserveAspectCrop
                clip: true
                anchors{
                    verticalCenter: parent.verticalCenter
                    left:parent.left
                    leftMargin: 7
                }
                smooth: true
                mipmap: true
            }

            Text{
                id:item_name
                text: model.name
                elide: Text.ElideMiddle
                font.pixelSize: 14
                color:Theme.colorFontPrimary
                anchors{
                    left: item_icon.right
                    right: parent.right
                    rightMargin: 20
                    leftMargin: 10
                    top: item_icon.top
                }
            }


            Text{
                id:item_size
                text: formatBytes(model.size)
                font.pixelSize: 12
                color:Theme.colorFontTertiary
                anchors{
                    left: item_icon.right
                    right: parent.right
                    rightMargin: 20
                    leftMargin: 10
                    bottom: item_icon.bottom
                }
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    showToast(model.icon)
                }
            }

        }
    }


    PrimaryButton{
        id:left_btn
        width: 92
        height: 30
        text:"确定"
        anchors{
            left: parent.left
            bottom:parent.bottom
            bottomMargin: 15
            leftMargin: 50
        }
        onClicked: {
            dialog.close()
            clickLeft()
        }
    }

    CusButton{
        id:right_btn
        width: 92
        height: 30
        text:"取消"
        anchors{
            right: parent.right
            bottom:parent.bottom
            rightMargin: 50
            bottomMargin: 15
        }
        onClicked: {
            dialog.close()
            clickRight()
        }
    }

    function show(sessionId,urls){
        user = IM.getUserObject(sessionId)
        dialog.user = user
        open()
    }

    function formatBytes(a, b) {
        if (0 === a) return "0 B";
        var c = 1024, d = b || 2, e = ["B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"], f = Math.floor(Math.log(a) / Math.log(c));
        return parseFloat((a / Math.pow(c, f)).toFixed(d)) + " " + e[f];
    }

}
