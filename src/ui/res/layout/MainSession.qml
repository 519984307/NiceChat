import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtGraphicalEffects 1.0
import UI 1.0
import "../global/global.js" as Global
import "../view"
import "../component"
import "../storage"

Item {

    property var userInfo : JSON.parse(IM.userInfo)

    property var curAccid : IM.sessionModel.getModelValue(sessionListView.currentIndex,"id")

    Rectangle{
        anchors.fill: sessionListView
        color:Theme.colorBackground2
    }

    ListView{
        id:sessionListView
        property color hoverItemColor : Qt.darker(Theme.colorBackground2,1.1)
        property color checkItemColor : Qt.darker(Theme.colorBackground2,1.2)
        height: parent.height
        anchors{
            left: parent.left
            right: centerDivder.left
        }
        boundsBehavior: Flickable.StopAtBounds
        model: IM.sessionModel
        delegate: Rectangle{
            color: {
                if(ListView.isCurrentItem){
                    return sessionListView.checkItemColor
                }
                return itemMouse.containsMouse ? sessionListView.hoverItemColor : Theme.colorBackground2
            }
            height: 60
            width: sessionListView.width

            CusAvatar{
                id:itemAvatar
                avatarName: model.id.charAt(0)
                avatar: model.id
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: 12
                }
            }

            Text {
                text: model.id
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
                    sessionListView.currentIndex = index
                    IM.updateMessageModel(curAccid)
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

        Item{
            width: parent.width
            anchors{
                top: layoutPanel.top
                bottom:panelDivider.bottom
            }

            Text{
                text:sessionModel[sessionListView.currentIndex].name
                font.pixelSize: 16
                color:Theme.colorFontPrimary
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: 20
                }
            }

            CusToolButton {
                id:btnMenu
                icon: "\ue61b"
                onClickEvent: {
                }
                hoverColor: "#00000000"
                iconSize : 16
                width: 26
                height: 26
                anchors{
                    top: parent.top
                    topMargin: 30
                    right: parent.right
                    rightMargin: 7
                }
            }
        }

        Rectangle{
            id:panelDivider
            color : Theme.colorDivider
            width: parent.width
            height: 1
            anchors{
                top: parent.top
                topMargin: 60
            }
        }

        Rectangle{

            property int bottomLenght : 130

            id:panelBottomDivider
            color : Theme.colorDivider
            width: parent.width
            height: 1
            anchors{
                bottom: parent.bottom
                bottomMargin: bottomLenght
            }
        }


        MouseArea{
            property point clickPos: "0,0"
            height: 4
            width: panelBottomDivider.width
            anchors{
                verticalCenter: panelBottomDivider.verticalCenter
            }
            cursorShape: Qt.SplitVCursor
            onPressed: {
                clickPos = Qt.point(mouse.x, mouse.y)
            }
            onPositionChanged: {
                var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
                panelBottomDivider.bottomLenght = Math.min(420,Math.max(130, panelBottomDivider.bottomLenght-delta.y))
                listMessage.positionViewAtEnd()
            }
        }


        ListModel{
            id:modelMessage
            ListElement{
                icon:""
                name:"朱子楚"
                text:" asdf asd"
            }
            ListElement{
                icon:""
                name:"朱子楚"
                text:" asdf asd"
            }
            ListElement{
                icon:""
                name:"朱子楚"
                text:"阿松大撒旦[EMJ1f62f][EMJ1f62f][EMJ1f632][EMJ1f632]阿松大撒旦[EMJ1f62f][EMJ1f62f][EMJ1f632][EMJ1f632]阿松大撒旦[EMJ1f62f][EMJ1f62f][EMJ1f632][EMJ1f632]阿松大撒旦[EMJ1f62f][EMJ1f62f][EMJ1f632][EMJ1f632]阿松大撒旦[EMJ1f62f][EMJ1f62f][EMJ1f632][EMJ1f632]阿松大撒旦[EMJ1f62f][EMJ1f62f][EMJ1f632][EMJ1f632]阿松大撒旦[EMJ1f62f][EMJ1f62f][EMJ1f632][EMJ1f632]阿松大撒旦[EMJ1f62f][EMJ1f62f][EMJ1f632][EMJ1f632]"
            }
        }


        ListView{
            id:listMessage
            width: parent.width
            model: IM.messageModel
            anchors{
                top: panelDivider.bottom
                bottom:panelBottomDivider.top
            }
            boundsBehavior: Flickable.StopAtBounds
            clip: true
            spacing : 10
            footer:Item{height: 10}
            header:Item{height: 10}
            onCountChanged:{
                contentY = Number.MAX_VALUE
            }
            ScrollBar.vertical: ScrollBar {
                minimumSize: 0.2
                anchors{
                    right: parent.right
                    rightMargin: 5
                }
            }
            delegate: Rectangle{
                width: listMessage.width
                height: childrenRect.height
                color:"#00000000"

                CusAvatar{
                    id:itemMsgAvatar
                    width: 34
                    height: 34
                    avatarName: "朱"
                    anchors{
                        right: parent.right
                        top:parent.top
                        rightMargin: 20
                    }
                    onClickAvatar: {
                        console.debug(itemMsgText.implicitWidth)
                        console.debug(itemMsgText.contentWidth)
                        console.debug(itemMsgText.paintedWidth)
                    }
                }

                Rectangle{
                    color:"#FF95EC69"
                    width: itemMsgText.width+10
                    height: itemMsgText.height+10
                    radius: 3
                    anchors{
                        top: itemMsgAvatar.top
                        right: itemMsgAvatar.left
                        rightMargin: 10
                    }
                    CusTextEdit{
                        id:itemMsgText
                        text: getEmojiStr(model.body)
                        wrapMode: Text.WrapAnywhere
                        anchors.centerIn: parent
                        readOnly: true
                        textFormat: Text.RichText
                        selectByMouse: true
                        width: Math.min(listMessage.width-200,600,itemMsgText.implicitWidth)
                    }
                }
            }
        }

        Item{
            id:layoutPanelBottom
            width: parent.width
            anchors{
                top: panelBottomDivider.bottom
                bottom: parent.bottom
            }

            Item{
                id:bottomBar
                width: parent.width
                height: 30

                CusToolButton {
                    id:btnEmoji
                    icon: "\ue7bb"
                    onClickEvent: {
                        IM.test()
                        console.debug("--==-=-=:"+listMessage.count)
                        emojiPicker.showDialog()
                    }
                    iconSize : 18
                    width: 24
                    height: 24
                    anchors{
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: 6
                    }
                }

            }

            ScrollView{
                width: parent.width
                anchors{
                    top: bottomBar.bottom
                    bottom: btnSend.top
                }
                clip: true
                focus: true
                CusTextArea{
                    id:messageInput
                    wrapMode: Text.WrapAnywhere
                    font.pixelSize: 14
                    color:Theme.colorFontPrimary
                    placeholderText:"请输入消息"
                    focus: true
                    onTextChanged: {
                        if (length > 2048) {
                            remove(2048, length)
                            return
                        }
                    }
                }
            }


            CusButton{
                id:btnSend
                width: 100
                text: "发送"
                anchors{
                    bottom: parent.bottom
                    right: parent.right
                    bottomMargin: 10
                    rightMargin: 10
                }
                onClicked: {
                    var text  = messageInput.text
                    if(text === ""){
                        showToast("内容不能为空")
                        return
                    }
                    text = text.replace(
                                /<img [^>]*src=['"]([^'"]+)[^>]*>/gi,
                                function (match, capture) {
                                    return capture.replace("qrc:/emojiSvgs/", "[EMJ").replace(".svg", "]")
                                })
                    IM.sendTextMessage(userInfo.accid,curAccid,UIHelper.htmlToPlainText(text))
                    messageInput.text= ""
                }
            }

        }

        Rectangle{
            id:panelEmpty
            color: Theme.colorBackground1
            anchors.fill: parent
            visible: Global.noValue(curAccid)

            FontLoader {
                id: awesome
                source: "qrc:/font/iconfont.ttf"
            }

            Text{
                anchors.centerIn: parent
                font.family: awesome.name
                font.pixelSize: 25
                text:"\ue6e6"
            }

        }

    }

    EmojiPickerWindow{
        id:emojiPicker
        target:btnEmoji
        editor: messageInput
    }

    function escape2Html(str) {
        var arrEntities = {
            "lt": '<',
            "gt": '>',
            "nbsp": ' ',
            "amp": '&',
            "quot": '"'
        }
        return str.replace(/&(lt|gt|nbsp|amp|quot);/ig, function (all, t) {
            return arrEntities[t]
        })
    }

    function getEmojiStr(str) {
        if (str === undefined) {
            return ""
        }
        var reg = /\[EMJ([^\]]+)\]/g
        var tag = "<img src=\"qrc:/emojiSvgs/$1.svg\" width=\"20\" height=\"20\" style=\"vertical-align: top;\" />"
        str = str.replace(reg,tag)
        return str
    }


    function addSession(user){
        IM.saveSession(user.accid)
    }

}
