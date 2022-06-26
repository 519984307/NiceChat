import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15
import UI 1.0
import "../component"

CusWindowDialog {

    id:dialog
    dialogWidth: 400
    dialogHeight: 400
    property var editor


    EmojiPicker {
        id: emojiPicker
        model: emojiModel
        editor: messageInput
        anchors.fill: parent
        anchors.margins: 3


        EmojiModel {
            id: emojiModel
            iconsPath: "../emojiSvgs/"
            iconsType: ".svg"
        }

    }

}
