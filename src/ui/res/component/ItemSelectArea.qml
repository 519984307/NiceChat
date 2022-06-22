import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import "../storage"
import "../global/global.js" as Global

Item {

    id:root
    property int startX
    property int startY
    property int endX
    property int endY
    property string maskColor: "#88000000"
    property string borderColor: Theme.colorPrimary
    property string dragColor : Theme.colorPrimary
    property bool enableSelect: true
    property bool showMenu: false
    signal clickRighListener
    anchors.fill: parent

    Rectangle{
        id:mask_top
        color: maskColor
        anchors{
            top: parent.top
            bottom: rect_select.top
            left: parent.left
            right: parent.right
        }
        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onClicked: {
                rightButton()
            }
        }
    }

    Rectangle{
        id:mask_left
        color: maskColor
        anchors{
            top: rect_select.top
            bottom: rect_select.bottom
            left: parent.left
            right: rect_select.left
        }
        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onClicked: {
                rightButton()
            }
        }
    }

    Rectangle{
        id:mask_right
        color: maskColor
        anchors{
            top: rect_select.top
            bottom: rect_select.bottom
            left: rect_select.right
            right: parent.right
        }
        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onClicked: {
                rightButton()
            }
        }
    }

    Rectangle{
        id:mask_bottom
        color: maskColor
        anchors{
            top: rect_select.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onClicked: {
                rightButton()
            }
        }
    }

    Rectangle{
        id:rect_select
        color: "#00000000"
        width: 0
        height: 0
        x:-2
        y:-2
        border{
            width: 2
            color: borderColor
        }
    }


    MouseArea{
        anchors.fill: parent
        enabled: enableSelect
        onPressed:
            (mouse)=> {
                startX = mouse.x
                startY = mouse.y
                rect_select.x = startX
                rect_select.y = startY
                rect_select.width = 0
                rect_select.height = 0
                mouse.accepted = true
            }
        onReleased:
            (mouse)=> {
                enableSelect = false
                showMenu = true
                rect_menu.x = Qt.binding(function(){
                    return rect_select.x + rect_select.width - rect_menu.width
                })
                rect_menu.y = Qt.binding(function(){
                    var offsetY = rect_select.y + rect_select.height + 10
                    if(offsetY+rect_menu.height>root.height){
                        offsetY = rect_select.y -  rect_menu.height - 10
                        if(offsetY < 0){
                            return rect_select.y + rect_select.height - rect_menu.height - 10
                        }else{
                            return offsetY
                        }
                    }else{
                        return offsetY
                    }
                })
            }
        onPositionChanged:
            (mouse)=> {
                if(mouse.x>=startX && mouse.y>=startY){
                    rect_select.x = startX
                    rect_select.y = startY
                    rect_select.width = mouse.x - rect_select.x
                    rect_select.height = mouse.y - rect_select.y
                }
                if(mouse.x<=startX && mouse.y>=startY){
                    rect_select.x = mouse.x
                    rect_select.y = startY
                    rect_select.width = startX - rect_select.x
                    rect_select.height = mouse.y - rect_select.y
                }
                if(mouse.x>=startX && mouse.y<=startY){
                    rect_select.x = startX
                    rect_select.y = mouse.y
                    rect_select.width = mouse.x - rect_select.x
                    rect_select.height = startY - rect_select.y
                }
                if(mouse.x<=startX && mouse.y<=startY){
                    rect_select.x = mouse.x
                    rect_select.y = mouse.y
                    rect_select.width = startX - rect_select.x
                    rect_select.height = startY - rect_select.y
                }
                mouse.accepted = true
            }
    }


    MouseArea{
        anchors.fill: rect_select
        cursorShape: Qt.SizeAllCursor
        drag.target: rect_select
        drag.axis: Drag.XAndYAxis
        drag.minimumX: 0
        drag.maximumX: root.width - rect_select.width
        drag.minimumY: 0
        drag.maximumY: root.height - rect_select.height
        acceptedButtons: Qt.AllButtons
        onClicked:(mouse)=> {
                      if(mouse.button === Qt.RightButton){
                          rightButton()
                      }
                  }
    }


    Rectangle{
        width: 6
        height: 6
        color: dragColor
        anchors{
            left: rect_select.left
            leftMargin: -2
            top:rect_select.top
            topMargin: -2
        }
        MouseArea{
            property point startPoint: "0,0"
            property point endPoint: "0,0"
            anchors.fill: parent
            cursorShape: Qt.SizeFDiagCursor
            onPressed:
                (mouse) => {
                    startPoint = Qt.point(rect_select.x, rect_select.y)
                    endPoint = Qt.point(rect_select.x+rect_select.width, rect_select.y+rect_select.height)
                }
            onPositionChanged:
                (mouse) => {
                    var pos = parent.mapToItem(parent.parent,mouseX,mouseY)
                    if(pos.x<endPoint.x && pos.y<endPoint.y){
                        rect_select.x = pos.x
                        rect_select.y = pos.y
                        rect_select.width = endPoint.x - rect_select.x
                        rect_select.height = endPoint.y - rect_select.y
                    }
                    if(pos.x>endPoint.x && pos.y>endPoint.y){
                        rect_select.x = endPoint.x
                        rect_select.y = endPoint.y
                        rect_select.width = pos.x - rect_select.x
                        rect_select.height = pos.y - rect_select.y
                    }
                    if(pos.x<endPoint.x && pos.y>endPoint.y){
                        rect_select.x = pos.x
                        rect_select.y = endPoint.y
                        rect_select.width = endPoint.x - rect_select.x
                        rect_select.height = pos.y - rect_select.y
                    }
                    if(pos.x>endPoint.x && pos.y<endPoint.y){
                        rect_select.x = endPoint.x
                        rect_select.y = pos.y
                        rect_select.width = pos.x - rect_select.x
                        rect_select.height = endPoint.y - rect_select.y
                    }
                }
        }
    }

    Rectangle{
        width: 6
        height: 6
        color: dragColor
        anchors{
            top:rect_select.top
            topMargin: -2
            horizontalCenter: rect_select.horizontalCenter
        }
        MouseArea{
            property point endPoint: "0,0"
            anchors.fill: parent
            cursorShape: Qt.SizeVerCursor
            onPressed:
                (mouse) => {
                    endPoint = Qt.point(rect_select.x+rect_select.width, rect_select.y+rect_select.height)
                }
            onPositionChanged:
                (mouse) => {
                    var pos = parent.mapToItem(parent.parent,mouseX,mouseY)
                    if(pos.y<endPoint.y){
                        rect_select.y = pos.y
                        rect_select.height = endPoint.y - rect_select.y
                    }else{
                        rect_select.y = endPoint.y
                        rect_select.height = pos.y - rect_select.y
                    }
                }
        }
    }

    Rectangle{
        width: 6
        height: 6
        color: dragColor
        anchors{
            right: rect_select.right
            rightMargin: -2
            top:rect_select.top
            topMargin: -2
        }
        MouseArea{
            property point startPoint: "0,0"
            property point endPoint: "0,0"
            anchors.fill: parent
            cursorShape: Qt.SizeBDiagCursor
            onPressed:
                (mouse) => {
                    startPoint = Qt.point(rect_select.x, rect_select.y)
                    endPoint = Qt.point(rect_select.x+rect_select.width, rect_select.y+rect_select.height)
                }
            onPositionChanged:
                (mouse) => {
                    var pos = parent.mapToItem(parent.parent,mouseX,mouseY)
                    if(pos.x>startPoint.x && pos.y<endPoint.y){
                        rect_select.x = startPoint.x
                        rect_select.y = pos.y
                        rect_select.width = pos.x - startPoint.x
                        rect_select.height = endPoint.y - pos.y
                    }
                    if(pos.x<startPoint.x && pos.y>endPoint.y){
                        rect_select.x = pos.x
                        rect_select.y = endPoint.y
                        rect_select.width =  startPoint.x -  pos.x
                        rect_select.height = pos.y -  endPoint.y
                    }
                    if(pos.x<startPoint.x && pos.y<endPoint.y){
                        rect_select.x = pos.x
                        rect_select.y = pos.y
                        rect_select.width = startPoint.x - pos.x
                        rect_select.height = endPoint.y - pos.y
                    }
                    if(pos.x>startPoint.x && pos.y>endPoint.y){
                        rect_select.x = startPoint.x
                        rect_select.y = endPoint.y
                        rect_select.width =  pos.x -  startPoint.x
                        rect_select.height = pos.y -  endPoint.y
                    }
                }
        }
    }

    Rectangle{
        width: 6
        height: 6
        color: dragColor
        anchors{
            left: rect_select.left
            leftMargin: -2
            bottom:rect_select.bottom
            bottomMargin: -2
        }
        MouseArea{
            property point startPoint: "0,0"
            property point endPoint: "0,0"
            anchors.fill: parent
            cursorShape: Qt.SizeBDiagCursor
            onPressed:
                (mouse) => {
                    startPoint = Qt.point(rect_select.x, rect_select.y)
                    endPoint = Qt.point(rect_select.x+rect_select.width, rect_select.y+rect_select.height)
                }
            onPositionChanged:
                (mouse) => {
                    var pos = parent.mapToItem(parent.parent,mouseX,mouseY)
                    if(pos.x<endPoint.x && pos.y>startPoint.y){
                        rect_select.x = pos.x
                        rect_select.y = startPoint.y
                        rect_select.width = endPoint.x - pos.x
                        rect_select.height = pos.y -  startPoint.y
                    }
                    if(pos.x>endPoint.x && pos.y<startPoint.y){
                        rect_select.x = endPoint.x
                        rect_select.y = pos.y
                        rect_select.width = pos.x - endPoint.x
                        rect_select.height = startPoint.y - pos.y
                    }
                    if(pos.x>endPoint.x && pos.y>startPoint.y){
                        rect_select.x = endPoint.x
                        rect_select.y = startPoint.y
                        rect_select.width = pos.x - endPoint.x
                        rect_select.height = pos.y -  startPoint.y
                    }
                    if(pos.x<endPoint.x && pos.y<startPoint.y){
                        rect_select.x = pos.x
                        rect_select.y = pos.y
                        rect_select.width = endPoint.x - pos.x
                        rect_select.height = startPoint.y -  pos.y
                    }
                }
        }
    }

    Rectangle{
        width: 6
        height: 6
        color: dragColor
        anchors{
            bottom:rect_select.bottom
            bottomMargin: -2
            horizontalCenter: rect_select.horizontalCenter
        }
        MouseArea{
            property point startPoint: "0,0"
            anchors.fill: parent
            cursorShape: Qt.SizeVerCursor
            onPressed:
                (mouse) => {
                    startPoint = Qt.point(rect_select.x, rect_select.y)
                }
            onPositionChanged:
                (mouse) => {
                    var pos = parent.mapToItem(parent.parent,mouseX,mouseY)
                    if(pos.y>startPoint.y){
                        rect_select.y = startPoint.y
                        rect_select.height = pos.y - rect_select.y
                    }else{
                        rect_select.y = pos.y
                        rect_select.height = startPoint.y - rect_select.y
                    }
                }
        }
    }

    Rectangle{
        width: 6
        height: 6
        color: dragColor
        anchors{
            right: rect_select.right
            rightMargin: -2
            bottom:rect_select.bottom
            bottomMargin: -2
        }
        MouseArea{
            property point startPoint: "0,0"
            property point endPoint: "0,0"
            anchors.fill: parent
            cursorShape: Qt.SizeFDiagCursor
            onPressed:
                (mouse) => {
                    startPoint = Qt.point(rect_select.x, rect_select.y)
                    endPoint = Qt.point(rect_select.x+rect_select.width, rect_select.y+rect_select.height)
                }
            onPositionChanged:
                (mouse) => {
                    var pos = parent.mapToItem(parent.parent,mouseX,mouseY)
                    if(pos.x>startPoint.x && pos.y>startPoint.y){
                        rect_select.x = startPoint.x
                        rect_select.y = startPoint.y
                        rect_select.width = pos.x - rect_select.x
                        rect_select.height = pos.y - rect_select.y
                    }
                    if(pos.x<startPoint.x && pos.y<startPoint.y){
                        rect_select.x = pos.x
                        rect_select.y = pos.y
                        rect_select.width = startPoint.x - pos.x
                        rect_select.height = startPoint.y - pos.y
                    }
                    if(pos.x<startPoint.x && pos.y>startPoint.y){
                        rect_select.x = pos.x
                        rect_select.y = startPoint.y
                        rect_select.width = startPoint.x - pos.x
                        rect_select.height = pos.y - rect_select.y
                    }
                    if(pos.x>startPoint.x && pos.y<startPoint.y){
                        rect_select.x = startPoint.x
                        rect_select.y = pos.y
                        rect_select.width = pos.x - startPoint.x
                        rect_select.height = startPoint.y - pos.y
                    }
                }
        }
    }



    Rectangle{
        width: 6
        height: 6
        color: dragColor
        anchors{
            right: rect_select.right
            rightMargin: -2
            verticalCenter: rect_select.verticalCenter
        }
        MouseArea{
            property point startPoint: "0,0"
            anchors.fill: parent
            cursorShape: Qt.SizeHorCursor
            onPressed:
                (mouse) => {
                    startPoint = Qt.point(rect_select.x, rect_select.y)
                }
            onPositionChanged:
                (mouse) => {
                    var pos = parent.mapToItem(parent.parent,mouseX,mouseY)
                    if(pos.x>startPoint.x){
                        rect_select.x = startPoint.x
                        rect_select.width = pos.x - rect_select.x
                    }else{
                        rect_select.x = pos.x
                        rect_select.width = startPoint.x - rect_select.x
                    }
                }
        }
    }

    Rectangle{
        width: 6
        height: 6
        color: dragColor
        anchors{
            left: rect_select.left
            leftMargin: -2
            verticalCenter: rect_select.verticalCenter
        }
        MouseArea{
            property point endPoint: "0,0"
            anchors.fill: parent
            cursorShape: Qt.SizeHorCursor
            onPressed:
                (mouse) => {
                    endPoint = Qt.point(rect_select.x+rect_select.width, rect_select.y+rect_select.height)
                }
            onPositionChanged:
                (mouse) => {
                    var pos = parent.mapToItem(parent.parent,mouseX,mouseY)
                    if(pos.x<endPoint.x){
                        rect_select.x = pos.x
                        rect_select.width = endPoint.x - rect_select.x
                    }else{
                        rect_select.x = endPoint.x
                        rect_select.width = pos.x - rect_select.x
                    }
                }
        }
    }

    Rectangle{
        id:rect_menu
        width: 120
        height: 40
        visible: showMenu


        CusToolButton {
            id:btnClose
            color: "#BBB"
            icon:"\ue600"
            anchors{
                verticalCenter: parent.verticalCenter
                right: btnRight.left
                rightMargin: 14
            }
            onClickEvent: {
                Window.window.close()
            }
        }

        CusToolButton {
            id:btnRight
            color: Theme.colorPrimary
            icon:"\ue650"
            anchors{
                verticalCenter: parent.verticalCenter
                right: parent.right
                rightMargin: 14
            }
            onClickEvent: {
                clickRighListener()
            }
        }
    }

    function rightButton(){
        if(enableSelect){
            Window.window.close()
        }else{
            retrunParam()
        }
    }

    function getAreaX(){
        return (rect_select.x+4)*Screen.devicePixelRatio
    }

    function getAreaY(){
        return (rect_select.y+4)*Screen.devicePixelRatio
    }

    function getAreaWidth(){
        return (rect_select.width-8)*Screen.devicePixelRatio
    }

    function getAreaHeight(){
        return (rect_select.height-8)*Screen.devicePixelRatio
    }

    function retrunParam(){
        rect_select.width=0
        rect_select.height=0
        rect_select.x=-4
        rect_select.y=-4
        enableSelect = true
        showMenu = false
    }

}
