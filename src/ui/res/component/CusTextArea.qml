import QtQuick 2.15
import QtQuick.Controls 2.15
import "../storage"
import UI 1.0

TextArea {

    id:inputText
    selectionColor: "#9BCAEF"
    selectByMouse: true
    selectByKeyboard: true
    textFormat: Text.RichText


    TextDocument{
        id:doc
        document: inputText.textDocument
        cursorPosition: inputText.cursorPosition
        selectionStart: inputText.selectionStart
        selectionEnd: inputText.selectionEnd
    }

    function plainText(){
        return doc.plainText()
    }

}
