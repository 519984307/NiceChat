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
        currentId: sessionController.current.id
    }

    SessionController{
        id:sessionController
    }

    Component{
        id:com_text

        CusTextEdit{
            text: getEmojiStr(getBlankWrapStr(attach.msg),18)
            wrapMode: Text.WrapAnywhere
            readOnly: true
            textFormat: Text.RichText
            width: Math.min(messageListView.width-200,600,implicitWidth)
        }

    }

    Component{
        id:com_image

        Rectangle{
            color:Theme.colorBackground
            width: getWH(true,attach.w,attach.h)
            height: getWH(false,attach.w,attach.h)

            Image{
                anchors.fill: parent
                source:"http://127.0.0.1:8889/oss/%1".arg(attach.url)

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        showToast(attach.url)
                    }
                }

            }

        }

    }

    Component{
        id:com_file

        Rectangle{
            width: 220
            height: 60

            color: item_mouse.containsMouse? Theme.colorBackground2 : Theme.colorBackground

            Text{
                text:attach.name
                font.pixelSize: 12
                color:Theme.colorFontPrimary
                elide: Text.ElideMiddle
                anchors{
                    top: item_icon.top
                    right: item_icon.left
                    rightMargin: 10
                    left: parent.left
                    leftMargin: 10
                }
            }

            Text{
                text: formatBytes(attach.size)
                font.pixelSize: 12
                color:Theme.colorFontSecondary
                anchors{
                    bottom: item_icon.bottom
                    left: parent.left
                    leftMargin: 10
                }
            }


            Image {
                id:item_icon
                width: 33
                height: 40.5
                mipmap: true
                smooth: true
                source: UIHelper.getFileIcon(attach.ext)
                anchors{
                    verticalCenter: parent.verticalCenter
                    right:parent.right
                    rightMargin: 10
                }
            }

            MouseArea{
                id:item_mouse
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: {

                }
            }

        }

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

        Connections{
            target: sessionController

            function onCurrentChanged(){
                messageController.loadMessageData()
                IM.clearUnreadCount(sessionController.current.id)
            }
        }

        delegate: Rectangle{

            property var user : IM.getUserObject(model.id)

            color: {
                if(sessionController.current.id === model.id)
                    return sessionListView.checkItemColor
                if(model.top)
                    return sessionListView.hoverItemColor
                return itemMouse.containsMouse ? sessionListView.hoverItemColor : Theme.colorBackground2
            }
            height: 60
            width: sessionListView.width
            border{
                width: {
                    if(sessionMenu.session == null)
                        return 0
                    return model.id === sessionMenu.session.id ? 2 : 0
                }
                color:Theme.colorPrimary
            }
            CusAvatar{
                id:item_session_avatar
                avatarName: user.name.charAt(0)
                avatar: user.icon
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
                    right: item_session_avatar.right
                    rightMargin: -4
                    topMargin: -4
                    top: item_session_avatar.top
                }
                visible: model.unread>0

                Text {
                    text: Math.min(model.unread,99)
                    font.pixelSize: 11
                    color: "#FFFFFF"
                    anchors.centerIn: parent
                }

            }

            Text {
                id:item_session_name
                text: user.name
                color: Theme.colorFontPrimary
                font.pixelSize: 14
                maximumLineCount: 1
                elide: Text.ElideRight
                anchors{
                    top:parent.top
                    topMargin: 9
                    left: item_session_avatar.right
                    leftMargin: 12
                    right: item_session_time.left
                }
            }

            Text{
                id:item_session_time
                text:getSessionTime(model.time)
                color: Theme.colorFontTertiary
                font.pixelSize: 10
                anchors{
                    verticalCenter:item_session_name.verticalCenter
                    right: parent.right
                    rightMargin: 12
                }
            }

            Text {
                text: getEmojiStr(model.content,12);
                color: Theme.colorFontTertiary
                elide: Text.ElideRight
                maximumLineCount: 1
                antialiasing: true
                anchors{
                    bottom:parent.bottom
                    bottomMargin: 9
                    left: item_session_avatar.right
                    right: parent.right
                    rightMargin: 12
                    leftMargin: 12
                }
            }

            MouseArea{
                id:itemMouse
                anchors.fill: parent
                hoverEnabled: true
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onClicked: {
                    if (mouse.button === Qt.RightButton) {
                        sessionMenu.show(sessionController.sessionModel.getItem(index))
                    }else if(mouse.button === Qt.LeftButton){
                        sessionController.setCurrent(index)
                    }
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

        DropArea{
            visible: !panel_empty.visible && !send_file_dialg.visible
            anchors.fill: parent
            onDropped: {
                layoutPanel.color = Qt.binding(function(){return Theme.colorBackground1})
                sessionController.loadFileList(drop.urls)
                send_file_dialg.show(sessionController.current.id,drop.urls)
            }
            onEntered: {
                layoutPanel.color = Qt.binding(function(){return Theme.colorDivider})
            }
            onExited: {
                layoutPanel.color = Qt.binding(function(){return Theme.colorBackground1})
            }
        }

        Item{
            width: parent.width
            anchors{
                top: layoutPanel.top
                bottom:panelDivider.bottom
            }

            Text{
                text:IM.getUserName(sessionController.current.id)
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
                icon: "\ueaf1"
                onClickEvent: {
                }
                hoverColor: "#00000000"
                iconSize : 20
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
                messageListView.positionViewAtEnd()
            }
        }

        ListView{
            id:messageListView
            width: parent.width
            model: messageController.messageModel
            onContentYChanged: {
                if(contentY == originY && !Global.noValue(sessionController.current.id)){
                    messageController.loadMessageData()
                }
            }
            anchors{
                top: panelDivider.bottom
                bottom:panelBottomDivider.top
            }
            boundsBehavior: Flickable.StopAtBounds
            clip: true
            spacing : 10
            footer:Item{height: 10}
            header:Item{
                height: 30
                width: messageListView.width

                Text {
                    text: {
                        if(messageController.loadStatus === 0){
                            return "加载更多"
                        }
                        return ""
                    }
                    anchors.centerIn: parent
                    font.underline: true
                    visible: false
                    color:Theme.colorPrimary
                    MouseArea{
                        anchors.fill: parent
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            messageController.loadMessageData()
                        }
                    }
                }


                Text{
                    anchors.centerIn: parent
                    font.family: awesome.name
                    font.pixelSize: 20
                    text:"\ue756"
                    antialiasing: true
                    visible: messageController.loadStatus === 0
                    color:"#999999"
                    RotationAnimation on rotation {
                        from: 0
                        to: 360
                        duration: 1500
                        loops: Animation.Infinite
                    }
                }
            }
            ScrollBar.vertical: ScrollBar {
                id:scrollBar
                minimumSize: 0.2
                anchors{
                    right: parent.right
                    rightMargin: 5
                }
            }

            Connections{
                target: messageController.messageModel
                function onViewToBottom(){
                    messageListView.positionViewAtEnd()
                    messageListView.positionViewAtEnd()
                }
                function onViewToPosition(pos){
                    messageListView.positionViewAtIndex(pos,ListView.Beginning)
                }
            }

            delegate: Rectangle{
                width: messageListView.width
                height: childrenRect.height
                color:"#00000000"

                property bool isMine: IM.loginAccid === model.fromAccid
                property var user: IM.getUserObject(model.fromAccid)

                CusAvatar{
                    id:itemMsgAvatar
                    width: 26
                    height: 26
                    avatarName: user.name.charAt(0)
                    avatar: user.icon
                    anchors{
                        right: isMine ? parent.right : undefined
                        rightMargin: isMine ? 20 : undefined
                        left: isMine ? undefined : parent.left
                        leftMargin: isMine ? undefined : 20

                        top:parent.top
                    }
                    onClickAvatar: {
                        console.debug("messageListView.contentHeight:"+messageListView.contentHeight)
                        console.debug("messageListView.contentY:"+messageListView.contentY)
                        console.debug("messageListView.originY:"+messageListView.originY)
                        console.debug("messageListView.height:"+messageListView.height)
                    }
                }

                Rectangle{
                    id:content
                    color: isMine ? "#FF95EC69" : "#FFFFFF"
                    width: item_msg_loader.width+10
                    height: item_msg_loader.height+10
                    radius: 3
                    anchors{
                        top: itemMsgAvatar.top
                        right: isMine ? itemMsgAvatar.left : undefined
                        rightMargin: isMine ? 10 : undefined
                        left: isMine ? undefined : itemMsgAvatar.right
                        leftMargin: isMine ? undefined : 10

                    }

                    Loader{
                        id:item_msg_loader
                        property var attach: model.attachment
                        anchors.centerIn: parent
                        sourceComponent: {
                            switch(model.type){
                            case 0:
                                return com_text
                            case 1:
                                return com_image
                            case 2:
                                return com_file
                            }
                        }
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
                    icon: "\ue63d"
                    onClickEvent: {
                        IM.test()
                        emojiPicker.showDialog()
                    }
                    iconSize : 20
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
                    text = text.replace(
                                /<img [^>]*src=['"]([^'"]+)[^>]*>/gi,
                                function (match, capture) {
                                    return capture.replace("qrc:/emojiSvgs/", "[EMJ").replace(".svg", "]")
                                })
                    text = UIHelper.htmlToPlainText(text)
                    if(text.trim() === ""){
                        showToast("内容不能为空")
                        return
                    }
                    //                    text = text.replace(/ /gi,"&nbsp;")
                    //                    text = text.replace(/\n/gi,"<br>")
                    IM.sendTextMessage(sessionController.current.id,0,text)
                    messageInput.text= ""
                }
            }

        }

        Rectangle{
            id:panel_empty
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

    CusMenu{

        property var session : null

        id:sessionMenu
        CusMenuItem{
            text: {
                if(sessionMenu.session==null)
                    return ""
                return sessionMenu.session.top ? "取消置顶" : "置顶"
            }
            onClicked: {
                IM.topSession(sessionMenu.session.id,!sessionMenu.session.top)
            }
        }
        CusMenuItem{
            text: "删除"
            onClicked: {
                IM.deleteSession(sessionMenu.session.id)
            }
        }

        function show(item){
            sessionMenu.session = item
            popup()
        }

        onClosed:{
            sessionMenu.session = null
        }
    }


    EmojiPickerWindow{
        id:emojiPicker
        target:btnEmoji
        editor: messageInput
    }

    SendFileDiaog{
        id:send_file_dialg
        model: sessionController.fileModel
        onClickLeft: {
            sessionController.sendSelectedFile(sessionController.current.id,0)
        }
    }

    function formatBytes(a, b) {
        if (0 === a) return "0 B";
        var c = 1024, d = b || 2, e = ["B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"], f = Math.floor(Math.log(a) / Math.log(c));
        return parseFloat((a / Math.pow(c, f)).toFixed(d)) + " " + e[f];
    }

    function getEmojiStr(str,size) {
        if (str === undefined) {
            return ""
        }
        var reg = /\[EMJ([^\]]+)\]/g
        var tag = "<img src=\"qrc:/emojiSvgs/$1.svg\" width=\"%1\" height=\"%1\" style=\"vertical-align: top;\" />".arg(size)
        str = str.replace(reg,tag)
        return str
    }

    function getBlankWrapStr(str){
        str = str.replace(/ /gi,"&nbsp;")
        str = str.replace(/\n/gi,"<br>")
        return str;
    }

    function getWH(is_w, w, h) {
        var ref_w = 200
        var flag = w > h
        var realW
        var realH
        if (w > ref_w) {
            var proportion = ref_w / w
            realW = w * proportion
            realH = h * proportion
        } else {
            realW = w
            realH = h
        }
        if (is_w) {
            return realW
        } else {
            return realH
        }
    }


    function getSessionTime(str){
        var date = new Date(parseInt(str));//时间戳为10位需*1000，时间戳为13位的话不需乘1000
        var year = date.getFullYear(),
        month = ("0" + (date.getMonth() + 1)).slice(-2),
        sdate = ("0" + date.getDate()).slice(-2),
        hour = ("0" + date.getHours()).slice(-2),
        minute = ("0" + date.getMinutes()).slice(-2),
        second = ("0" + date.getSeconds()).slice(-2);
        if (date.toDateString() === new Date().toDateString()) {
            return hour +":"+ minute;
        } else if (date < new Date()){
            return  year + "/"+ month +"/"+ sdate;
        }
        return result
    }

    function jumpSession(user){
        sessionController.jumpSession(user.id)
    }

}
