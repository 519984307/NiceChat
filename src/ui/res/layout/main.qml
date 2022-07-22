import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import Qt.labs.platform 1.1
import "../component"
import "../storage"
import "../global/global.js" as Global

CusWindow {
    id:window
    title: qsTr(UIHelper.appName())
    width: 700
    height: 500
    closeDestory: false

    Component.onCompleted: {
        window.minimumWidth = 700
        window.minimumHeight = 500
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
                icon:"\ue9d2"
                fontSize:24
                url:"qrc:/layout/MainContact.qml"
            }
        }


        CusSliderBar{
            id:slider
            model: sliderModel
            avatar: IM.profile.icon
            avatarName: IM.profile.name.charAt(0)
            onClickAvatar:{
                showToast("点击头像")
            }
            onClickMenu:{
                main_menu.popup()
            }
        }


        StackLayout{
            id:content
            anchors{
                top:parent.top
                left: slider.right
                bottom: parent.bottom
                right:parent.right
            }
            currentIndex: slider.getIndex()
            MainSession{
                id:session
            }
            MainContact{
                id:contact
                onClickSend:
                    (user)=>{
                        slider.setIndex(0)
                        session.jumpSession(Global.deepCopy(user))
                    }
            }
        }

        CusToolBar {
            id:toolBar
            color:"#00000000"
            onCloseEvent: function(){
                window.close()
            }
        }
    }

    CusMenu{
        id:main_menu
        CusMenuItem{
            text:"意见反馈"
            onClicked: {

            }
        }
        CusMenuItem{
            text:"设置"
            onClicked: {
                navigate(Router.window_settings)
            }
        }
    }

    NetWorkStatus{
        id:networkWindow
        visible: window.visible
        x:window.x + (window.width - width)/2
        y:Math.max(window.y - 40,0)
        opacity: IM.state !== 3
    }

}
