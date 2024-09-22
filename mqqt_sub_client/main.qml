import QtQuick 2.15
import QtQuick.Controls 2.15
import Qt.labs.folderlistmodel 2.1
import QtGraphicalEffects 1.0

ApplicationWindow {
    id: applicationwindowID
    visible: true
    width: 640
    height: 480
    title: qsTr("Battery Monitor")
    property real factor:applicationwindowID.width / 640
    property int batteryPercentage: mqttClient.batteryPercentage
    Image {
        id: batteryImage
        source: "qrc:/images/battery.png"
        visible: true
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
        width: 200 *factor
        height : 200 *factor

        Rectangle {
            id: batteryLevel
            height: innerRecID.height
            width: innerRecID.width * (batteryPercentage / 100)
            anchors.left: innerRecID.left
            anchors.verticalCenter: innerRecID.verticalCenter
            color: batteryPercentage > 70 ? "green" :
                                            batteryPercentage > 30 ? "yellow" : "red"
            border.color: "transparent"
            radius: 10 * factor
        }
        Rectangle {
            id : innerRecID
            width: batteryImage.width * 0.88
            height: batteryImage.height * 0.46
            y: 54 * factor
            x:7 * factor
            anchors.leftMargin: -10 * factor
            color: "transparent"
            border.color: "black"
            border.width: 0.5 * factor
            radius: 10 * factor
        }

    }
    Text {
        anchors.centerIn: batteryImage
        text:"Battery Percentage: " + mqttClient.batteryPercentage + "%"
        font.pixelSize: 14 *factor



    }
    Text {

        text: "Battery Status: " + mqttClient.batteryStatus
        font.pixelSize: 14 *factor
        anchors.left: batteryImage.left
        anchors.top : batteryImage.bottom
        font.bold: true

    }


}
