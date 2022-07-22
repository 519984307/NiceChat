import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import "../view"
import "../storage"
import "../component"

Item {
    anchors.fill: parent

    Connections{
        target: UIHelper
        function onCheckUpdateResult(status){
            hideLoading()
            if(status === -1){
                showToast("获取版本信息失败")
                return
            }
            if(status === 0){
                showToast("已经是最新版了")
                return
            }
            showToast("有更新")
        }
    }



    ColumnLayout{
        anchors{
            top: parent.top
            left: parent.left
            topMargin: 24
            leftMargin: 24
        }

        Text{
            font.pixelSize: 24
            text:UIHelper.appName()
            font.bold: true
            color:Theme.colorFontPrimary
        }

        RowLayout{

            Layout.topMargin: 20

            Text{
                font.pixelSize: 12
                text:"版本：v"+UIHelper.appVersion()
                color:Theme.colorFontPrimary
                Layout.alignment: Qt.AlignVCenter
            }

            CusButton{
                text: "检测更新"
                Layout.leftMargin: 8
                onClicked: {
                    showLoading()
                    UIHelper.checkUpdate()
                }
            }

        }

        Text{
            font.pixelSize: 12
            text:"本软件开源"
            color:Theme.colorFontPrimary
        }

        Row{
            Text{
                font.pixelSize: 12
                text:"项目链接："
                color:Theme.colorFontPrimary
            }
            Text{
                font.pixelSize: 12
                text:"Github"
                color:Theme.colorPrimary
                font.underline: true
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        Qt.openUrlExternally("https://github.com/zhuzichu520/DoTool")
                    }
                }
            }
        }

        Text{
            font.pixelSize: 12
            text:"邮箱：524787275@qq.com"
            color:Theme.colorFontPrimary
        }


        Text{
            font.pixelSize: 12
            text:"找一份Android或Qt兼职，有岗位的联系上面邮箱"
            color:Theme.colorFontPrimary
        }

        Text{
            font.pixelSize: 12
            text:"个人博客"
            color:Theme.colorPrimary
            font.underline: true
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    Qt.openUrlExternally("https://zhuzichu520.github.io/")
                }
            }
        }

        Text{
            property bool isColorPrimary : false
            id:niceText
            font.pixelSize: 16
            text:"用爱发电！！请作者喝杯咖啡~"
            Layout.topMargin: 20
            color: isColorPrimary ? Theme.colorPrimary : Theme.colorFontPrimary
            Behavior on color{
                ColorAnimation {
                    duration: 300
                }
            }
            Timer{
                id:colorTimer
                interval: 500
                repeat: true
                running: true
                onTriggered: {
                    niceText.isColorPrimary = !niceText.isColorPrimary
                }
            }
        }



        ColumnLayout{
            Image{
                width: 200
                height: 200
                sourceSize: Qt.size(width,height)
                fillMode: Image.PreserveAspectFit
                source: "qrc:/image/paycode.png"
                Layout.topMargin: 10
            }

            Text{
                font.pixelSize: 12
                text:"支付宝扫码"
                color:Theme.colorFontPrimary
                Layout.alignment: Qt.AlignCenter
            }
        }

    }

}
