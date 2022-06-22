import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import "../view"
import "../storage"

Item {
    anchors.fill: parent

    ColumnLayout{
        anchors{
            top: parent.top
            left: parent.left
            topMargin: 24
            leftMargin: 24
        }

        RowLayout{

            Text{
                font.pixelSize: 12
                text:"主题颜色"
                color:Theme.colorFontPrimary
            }

            Rectangle{
                width: 30
                height: 30
                color:Theme.colorPrimary
                MouseArea{
                    cursorShape: Qt.PointingHandCursor
                    anchors.fill: parent
                    onClicked: {
                        navigate(Router.window_colorpicker,2)
                    }
                }
            }
        }

    }
}
