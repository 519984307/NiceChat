import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import UI 1.0
import "../storage"
import "../global/global.js" as Global

ApplicationWindow {
    id:window

    property var router
    property alias page: container.children
    property int requestCode
    property var prevWindow
    property var resizable
    visible: true
    signal windowResult(int requestCode,int resultCode,var data)

    onClosing: function(closeevent){
        try{
            window.destroy()
            closeevent.accepted = false
        }catch(err){
            closeevent.accepted = false
        }
    }

    onResizableChanged: {
        if(resizable){
            minimumWidth = 0
            minimumHeight = 0
            maximumWidth = 16777215
            maximumHeight = 16777215
        }else{
            minimumWidth = width
            minimumHeight = height
            maximumWidth = width
            maximumHeight = height
            flags = flags | Qt.WindowStaysOnTopHint
            flags = flags &~ Qt.WindowStaysOnTopHint
        }
    }

    Component.onCompleted: {
        framelessHelper.titleBarHeight = 30
        framelessHelper.removeWindowFrame()
        if(router !== undefined){
            Router.addWindow(router.path,window)
        }
    }

    Component.onDestruction: {
        if(router !== undefined){
            Router.removeWindow(router.path)
        }
    }

    FramelessHelper {
        id: framelessHelper
    }

    Item {
        id:container
        anchors.fill: parent
        MouseArea{
            anchors.fill: parent
        }
    }

    Rectangle{
        id:layoutToast
        color: "black"
        height: 0
        clip: true
        property alias text: textToast.text
        anchors{
            left: container.left
            right:container.right
            bottom: container.bottom
        }
        antialiasing: true
        Text{
            id:textToast
            anchors.centerIn: parent
            color : "white"
            font.pixelSize: 12
        }

        Behavior on height{
            NumberAnimation{
                duration: 300
            }
        }
    }

    Rectangle{
        id:layoutLoading
        anchors.fill: container
        color: "#33000000"
        visible: false
        BusyIndicator{
            width: 60
            height: 60
            anchors.centerIn: parent
        }
        z:99
        MouseArea{
            hoverEnabled: true
            anchors.fill: parent
        }
    }

    Timer{
        id:timerToast
        interval: 1500
        onTriggered: {
            layoutToast.text = ""
            layoutToast.height = 0
        }
    }

    function toggleMaximized() {
        if (window.visibility === Window.Maximized) {
            window.showNormal();
        } else {
            window.showMaximized();
        }
    }

    function showToast(text){
        layoutToast.height = 36
        layoutToast.text = text === undefined ? "" : text
        timerToast.restart()
    }

    function showLoading(){
        layoutLoading.visible = true
    }

    function hideLoading(){
        layoutLoading.visible = false
    }

    function navigate(url,requestCode){
        var obj = Router.parseUrl(url)
        if(Object.keys(obj).length===0){
            obj = Router.parseUrl(Router.toUrl(url))
        }
        var path = obj.path;
        var isAttach = obj.isAttach.bool();
        var options = JSON.parse(obj.options)
        var data = Router.obtRouter(path)
        if(data === null){
            console.error("没有注册当前路由："+path)
            return
        }
        var win = Router.obtWindow(data.path)
        if(win !== null && data.onlyOne){
            for(var key in options){
                win[key] = options[key]
            }
            options.requestCode = requestCode
            options.prevWindow = window
            win.show()
            win.raise()
            win.requestActivate()
            return
        }
        options.requestCode = requestCode
        options.prevWindow = window
        var comp = Qt.createComponent(data.path)
        if (comp.status !== Component.Ready){
            console.error("组件创建错误："+path)
            return
        }
        options.router = data

        if(!isAttach){
            win = comp.createObject(null,options)
        }else{
            win = comp.createObject(window,options)
        }
    }

    function setResult(resultCode,data){
        prevWindow.windowResult(requestCode,resultCode,data)
    }

    function setHitTestVisible(view,isHit){
        framelessHelper.setHitTestVisible(view, isHit)
    }

    function getToolBarHeight(){
        return framelessHelper.titleBarHeight
    }

}
