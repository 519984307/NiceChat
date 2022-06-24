import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtWebView 1.1
import Qt.labs.platform 1.1
import "../component"
import "../storage"

CusWindow {
    id:window
    title: qsTr(UIHelper.appName())
    width: 700
    height: 500
    property var userInfo : JSON.parse(IM.userInfo)

    Connections{
        target: IM
        function userInfoChanged(){
            console.debug(IM.userInfo)
        }
    }

    Component.onCompleted: {
        window.minimumWidth = 700
        window.minimumHeight = 500
    }

    onClosing: function(closeevent){
        window.visible = false
        closeevent.accepted = false
    }

    SystemTrayIcon {
        id:systemTray
        visible: true
        icon.source: "qrc:/image/ic_logo.ico"
        onActivated:
            (reason)=>{
                if(reason === 3){
                    window.show()
                    window.raise()
                    window.requestActivate()
                }
            }
        menu: Menu {
            MenuItem {
                text: qsTr("退出")
                onTriggered: Qt.quit()
            }
        }
    }

    page: CusPage{

        CusToolBar {
            id:toolBar
            onCloseEvent: function(){
                window.close()
            }
        }

        ListModel{
            id:sliderModel
            ListElement{
                name:"消息"
                icon:"\ue61a"
                fontSize:24
                url:"qrc:/layout/MainSession.qml"
            }
            ListElement{
                name:"联系人"
                icon:"\ue7fe"
                fontSize:24
                url:"qrc:/layout/MainContact.qml"
            }
        }


        CusSliderBar{
            id:slider
            model: sliderModel
            avatar: userInfo.icon
            avatarName: userInfo.name.charAt(0)
            onClickAvatar:{
                showToast("点击头像")
            }
        }

        Loader{
            id:content
            anchors{
                top:parent.top
                left: slider.right
                bottom: parent.bottom
                right:parent.right
            }
            source: slider.getUrl()
        }
    }


    NetWorkStatus{
        id:networkWindow
        visible: window.visible
        x:window.x + (window.width - width)/2
        y:Math.max(window.y - 40,0)
        transientParent: window
        opacity: IM.state !== 3
        Connections{
            target: window
            function onActiveChanged(){
                networkWindow.raise()
            }

            function onVisibilityChanged(){
                networkWindow.raise()
            }
        }
    }

}
