import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtWebView 1.1
import Qt.labs.platform 1.1
import "../component"
import "../storage"

CusWindow {
    id:window
    width: 596
    height: 600
    title: qsTr(UIHelper.appName())

    onClosing: function(closeevent){
        visible = false
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
                systemTray.showMessage("友情提示","程序已隐藏在托盘中。。。")
            }
        }

        ListModel{
            id:sliderModel
            ListElement{
                name:"首页"
                icon:"\ue719"
                fontSize:24
                url:"qrc:/layout/MainHome.qml"
            }
            ListElement{
                name:"设置"
                icon:"\ue6c7"
                fontSize:24
                url:"qrc:/layout/MainSetting.qml"
            }
            ListElement{
                name:"关于"
                icon:"\ue622"
                fontSize:21
                url:"qrc:/layout/MainAbout.qml"
            }
        }


        CusSliderBar{
            id:slider
            model: sliderModel
        }

        Loader{
            id:content
            anchors{
                top:toolBar.bottom
                left: slider.right
                bottom: parent.bottom
                right:parent.right
            }
            source: slider.getUrl()
        }
    }


}
