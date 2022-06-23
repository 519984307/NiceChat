import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import "../view"
import "../storage"

Item {
    anchors.fill: parent

    FontLoader {
        id: awesome
        source: "qrc:/font/iconfont.ttf"
    }


    Rectangle{
        color : Theme.colorDivider
        width: 1
        height: parent.height
        anchors{
            left: parent.left
            leftMargin: 250
        }
    }


}
