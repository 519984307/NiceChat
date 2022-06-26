import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import Qt.labs.platform 1.1

Window {

    id:networkWindow
    width: 320
    height: 36
    flags: Qt.Tool | Qt.FramelessWindowHint
    Rectangle{
        anchors.fill: parent
        color:"#CC5353"
    }

    Text{
        text:"网络不可用，请检查你网络设置"
        font.pixelSize: 13
        anchors.centerIn: parent
        color:"#FFFFFF"
    }

    Connections{
        target: window
        function onActiveChanged(){
            if(window.active){
                networkWindow.raise()
            }
        }

        function onVisibilityChanged(){
            networkWindow.raise()
        }
    }

}
