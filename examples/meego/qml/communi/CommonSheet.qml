import QtQuick 1.1
import com.nokia.meego 1.0
import "UIConstants.js" as UI

Sheet {
    id: sheet

    property bool acceptable: false
    default property alias content: contentItem.data
    property alias titleText: label.text

    acceptButtonText: acceptable ? qsTr("Ok") : ""
    rejectButtonText: qsTr("Cancel")

    content: Rectangle {
        id: background
        anchors.fill: parent
        color: "#e0e1e2"

        Column {
            anchors.fill: parent
            anchors.margins: UI.PAGE_MARGIN
            spacing: UI.DEFAULT_SPACING
            Label {
                id: label
                width: parent.width
                font.pixelSize: 32
                font.family: "Nokia Pure Text Light"
                horizontalAlignment: Text.AlignHCenter
            }
            Item {
                id: contentItem
                width: parent.width
                height: parent.height - label.height - UI.DEFAULT_SPACING
            }
        }
    }
}
