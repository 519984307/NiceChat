//basicmenu.qml
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtQuick.Templates 2.12 as T
import QtQuick.Window 2.12
import QtGraphicalEffects 1.15
import "../storage"

T.Menu {
    id: control

    property color borderColor: "black"
    property color backgroundColor: Theme.colorBackground

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding)

    margins: 0

    font{
        pixelSize: 12
    }

    delegate: CusMenuItem { }

    contentItem: ListView {
        implicitHeight: contentHeight
        model: control.contentModel
        interactive: Window.window ? contentHeight > Window.window.height : false
        clip: true
        currentIndex: control.currentIndex

        ScrollIndicator.vertical: ScrollIndicator {}
    }

    background: Item {
        implicitWidth: 122
        implicitHeight: 30
             Rectangle{
                id:itemLayout
                anchors.fill: parent
                color: backgroundColor
             }

             DropShadow{
                 anchors.fill: itemLayout
                 radius: 8.0
                 samples: 17
                 color: AppStorage.isDark ? "#80FFFFFF" : "#80000000"
                 source: itemLayout
             }

    }

    T.Overlay.modal: Rectangle {
        color: Color.transparent(control.palette.shadow, 0.5)
    }

    T.Overlay.modeless: Rectangle {
        color: Color.transparent(control.palette.shadow, 0.12)
    }
}
