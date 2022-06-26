import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import UI 1.0

Item {
    id: container
    property var editor
    property EmojiModel model
    property var categories: ['Smileys & Emotion']
    property int skinColor: -1

    ScrollView{
        anchors.fill: parent
        GridLayout {
            id: grid
            property string category: categories[0]
            columns: 8
            columnSpacing: 8
            anchors.fill: parent
            Repeater {
                model: container.model.count(grid.category)
                delegate: Rectangle  {
                    property alias es: emojiSvg
                    Layout.preferredWidth: 40
                    Layout.preferredHeight: 40
                    radius: 40
                    color: mouseArea.containsMouse ? '#e6e6e6' : '#ffffff'
                    Image {
                        id: emojiSvg
                        source: container.model.path(grid.category, index, skinColor)
                        sourceSize: Qt.size(30, 30)
                        anchors.centerIn: parent
                        asynchronous: true
                    }
                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            var tag = "<img src = '%1' width = '20' height = '20' align = 'top'>"
                            editor.insert(editor.cursorPosition,tag.arg(emojiSvg.source))
                        }
                    }
                }
            }
        }
    }
}
