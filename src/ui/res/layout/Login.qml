import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtWebView 1.1
import Qt.labs.platform 1.1
import "../component"
import "../storage"

CusWindow {
    id:window
    width: 300
    height: 400
    title: qsTr(UIHelper.appName())

    onClosing: function(closeevent){
        visible = false
        closeevent.accepted = false
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
            onCloseEvent: function(){
                window.close()
            }
        }





    }


}
