﻿import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import "../global/global.js" as Global

Window {

    id:dialog
    flags: Qt.Tool | Qt.FramelessWindowHint
    property int dialogWidth: 300
    property int dialogHeight: 300
    property var target
    width: dialogWidth+10
    height: dialogHeight+10
    color:"#00000000"

    default property alias  children : content.children

    onActiveFocusItemChanged: {
        if(dialog.activeFocusItem == null){
            hide()
        }
    }

    Rectangle{
        id:content
        width: dialogWidth
        height: dialogHeight
        anchors.centerIn: parent
        layer.enabled: true
        radius: 5
        layer.effect: DropShadow{
            color:"#80000000"
        }
    }


    function showDialog(){
        if(!Global.noValue(target)){
            var pos = target.mapToGlobal(Qt.point(0,0))
            var w = target.width
            var h = target.height
            dialog.x = Math.min(Math.max(pos.x - (dialog.width - w)/2,0),Screen.desktopAvailableWidth-width)
            dialog.y = Math.max(pos.y - dialog.height,0)
        }
        show()
        requestActivate()
    }

    function hideDialog(){
        hide()
    }

}
