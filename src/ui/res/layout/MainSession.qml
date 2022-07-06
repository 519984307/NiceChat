import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtGraphicalEffects 1.0
import UI 1.0
import Controller 1.0
import "../global/global.js" as Global
import "../view"
import "../component"
import "../storage"

Item {

    property var userInfo : JSON.parse(IM.userInfo)

    FontLoader {
        id: awesome
        source: "qrc:/font/iconfont.ttf"
    }

    Rectangle{
        anchors.fill: sessionListView
        color:Theme.colorBackground2
    }

    MessageController{
        id:messageController
    }

    SessionController{
        id:sessionController
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
        model: sessionController.sessionModel
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
                avatar: modelData.icon
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: 12
                }
            }

            Rectangle{
                height: 16
                width: 16
                radius: 8
                color:"#FF3B30"
                anchors{
                    right: itemAvatar.right
                    rightMargin: -4
                    topMargin: -4
                    top: itemAvatar.top
                }

                Text {
                    text: qsTr("99")
                    font.pixelSize: 11
                    color: "#FFFFFF"
                    anchors.centerIn: parent
                }

            }

            Text {
                text: model.id
                color: Theme.colorFontPrimary
                font.pixelSize: 14
                anchors{
                    top:parent.top
                    topMargin: 9
                    left: itemAvatar.right
                    leftMargin: 12
                }
            }

            Text {
                text: getEmojiStr(model.body)
                color: Theme.colorFontTertiary
                elide: Text.ElideRight
                anchors{
                    bottom:parent.bottom
                    bottomMargin: 9
                    left: itemAvatar.right
                    right: parent.right
                    rightMargin: 12
                    leftMargin: 12
                }
            }

            MouseArea{
                id:itemMouse
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    sessionListView.currentIndex = index
                }
            }
        }
        onCurrentIndexChanged: {
            sessionController.setCurrent(sessionListView.currentIndex)
            messageController.loadMessageData(sessionController.current.id)
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
                text:sessionController.current.id
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
            model: messageController.messageModel
            anchors{
                top: panelDivider.bottom
                bottom:panelBottomDivider.top
            }
            boundsBehavior: Flickable.StopAtBounds
            clip: true
            spacing : 10
            footer:Item{height: 10}
            header:Item{height: 10}
            ScrollBar.vertical: ScrollBar {
                minimumSize: 0.2
                anchors{
                    right: parent.right
                    rightMargin: 5
                }
            }

            Connections{
                target: messageController.messageModel
                function onViewToBottom(){
                    listMessage.positionViewAtEnd()
                }
            }

            delegate: Rectangle{
                width: listMessage.width
                height: childrenRect.height
                color:"#00000000"

                property bool isMine: IM.loginAccid === model.fromAccid

                CusAvatar{
                    id:itemMsgAvatar
                    width: 34
                    height: 34
                    avatarName: "朱"
                    anchors{
                        right: isMine ? parent.right : undefined
                        rightMargin: isMine ? 20 : undefined
                        left: isMine ? undefined : parent.left
                        leftMargin: isMine ? undefined : 20

                        top:parent.top
                    }
                    onClickAvatar: {
                        console.debug(itemMsgText.implicitWidth)
                        console.debug(itemMsgText.contentWidth)
                        console.debug(itemMsgText.paintedWidth)
                    }
                }

                Rectangle{
                    id:content
                    color: isMine ? "#FF95EC69" : "#FFFFFF"
                    width: itemMsgText.width+10
                    height: itemMsgText.height+10
                    radius: 3
                    anchors{
                        top: itemMsgAvatar.top
                        right: isMine ? itemMsgAvatar.left : undefined
                        rightMargin: isMine ? 10 : undefined
                        left: isMine ? undefined : itemMsgAvatar.right
                        leftMargin: isMine ? undefined : 10

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

                Item{
                    width: 25
                    height: 25
                    visible: model.status !== 0
                    anchors{
                        right:isMine?content.left : undefined
                        rightMargin:isMine?1 : undefined
                        left:isMine?undefined:content.right
                        leftMargin: isMine?undefined:1
                        verticalCenter: content.verticalCenter
                    }

                    Text{
                        anchors.centerIn: parent
                        font.family: awesome.name
                        font.pixelSize: 20
                        text:"\ue756"
                        antialiasing: true
                        color:"#999999"
                        visible: model.status === 1
                        RotationAnimation on rotation {
                            from: 0
                            to: 360
                            duration: 1500
                            loops: Animation.Infinite
                        }
                    }

                    Text{
                        anchors.centerIn: parent
                        font.family: awesome.name
                        font.pixelSize: 20
                        color:"#CC5353"
                        antialiasing: true
                        text:"\ue727"
                        visible: model.status === 2
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
                        console.debug("--==-=-=:"+messageController.messageModel.count())
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
                    IM.sendTextMessage(userInfo.accid,sessionController.current.id,UIHelper.htmlToPlainText(text))
                    messageInput.text= ""
                }
            }

        }

        Rectangle{
            id:panelEmpty
            color: Theme.colorBackground1
            anchors.fill: parent
            visible: Global.noValue(sessionController.current.id)

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
//        for(var i=0;i<sessionModel.length;i++){
//            var item = sessionModel[i]
//            if(item.accid === user.accid){
//                sessionListView.currentIndex = i
//                return
//            }
//        }
//        sessionModel.push(user)
//        sessionListView.model = sessionModel
    }

}
