import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtWebView 1.1
import Qt.labs.platform 1.1
import "../component"
import "../storage"

CusWindow {
    id:window
    minimumWidth: 684
    minimumHeight: 464
    title: qsTr(UIHelper.appName())

    property var userInfo : JSON.parse(IM.userInfo)

    Connections{
        target: IM
        function userInfoChanged(){
            console.debug(IM.userInfo)
        }
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


}
