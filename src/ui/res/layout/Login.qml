import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtWebView 1.1
import Qt.labs.platform 1.1
import Controller 1.0
import "../component"
import "../storage"

CusWindow {
    id:window
    width: 280
    height: 380
    title: "登录"

    LoginController{
        id:controller
    }

    Connections{
        target: IM
        function onLoginFail(){
            hideLoading()
            showToast("登录失败")
        }
        function onLoginSuccess(){
            hideLoading()
            showToast("登录成功")
            close()
            navigate(Router.window_main)
        }
        function onStateChanged(){
            if(IM.state==0){
                hideLoading()
                showToast("网络异常")
            }
        }
    }

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
        }

        Text{
            text: "NiceChat"
            anchors{
                left:parent.left
                top: parent.top
                topMargin: 6
                leftMargin: 10
            }
        }


        PrimaryTextField{
            id:fieldUrl
            width: 180
            lableText: "URL"
            text:"ws://127.0.0.1:9999/ws"
            anchors{
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 85
            }
        }



        PrimaryTextField{
            id:fieldAccid
            width: 180
            lableText: "AccId"
            text:"admin"
            anchors{
                horizontalCenter: parent.horizontalCenter
                top: fieldUrl.bottom
                topMargin: 10
            }
        }



        PrimaryTextField{
            id:fieldToken
            width: 180
            lableText: "Token"
            text:"123456"
            anchors{
                horizontalCenter: parent.horizontalCenter
                top: fieldAccid.bottom
                topMargin: 10
            }
        }

        PrimaryButton{
            id:btnLogin
            width: 180
            text:"登录"
            anchors{
                horizontalCenter: parent.horizontalCenter
                bottom:parent.bottom
                bottomMargin: 50
            }
            onClicked: {
                showLoading()
                IM.login(fieldUrl.text,fieldAccid.text,fieldToken.text)
            }
        }
    }

}
