import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../component"
import "../third/colorpicker"
import "../storage"
import QtQuick.Window 2.15
import com.dotool.ui 1.0

CusWindow {

    id:window
    width: 450
    height: 260
    title:"颜色选择器"

    Component.onCompleted: {
        resizable  = false
    }

    onWindowResult:
        (requestCode,resultCode,data)=> {
            if(resultCode === 2){
                colorPicker.finderColor = data
            }
        }

    page: CusPage{

        clip: true

        CusToolBar {
            id:toolBar
            maxEnable: false
            title: window.title
        }

        ColorPicker{
            id:colorPicker
            color:"transparent"
            fontColor:Theme.colorFontPrimary
            anchors{
                top: toolBar.bottom
                horizontalCenter: parent.horizontalCenter
            }
            findLayout:CusToolButton {
                anchors.centerIn: parent
                color: "#BBB"
                icon:"\ue605"
                onClickEvent: {
                    navigate(Router.window_colorfinder,1)
                }
            }
        }

        RowLayout{
            spacing: 24
            anchors{
                bottom: parent.bottom
                right: parent.right
                bottomMargin: 8
                rightMargin: 16
            }
            Text{
                text:"取消"
                font.pixelSize: 12
                color:Theme.colorFontPrimary
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        window.close()
                    }
                }
            }
            Text{
                text:"确定"
                font.pixelSize: 12
                color:Theme.colorPrimary
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        if(requestCode === 2){
                            Theme.colorPrimary = colorPicker.colorValue
                        }else{
                            UIHelper.textClipboard(colorPicker.colorValue)
                        }
                        window.close()
                    }
                }
            }
        }

    }
}


