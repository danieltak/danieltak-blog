import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    color: "#888888"
    title: qsTr( MySingleton.helloWorld )

    Text{
        id: myText
        width: parent.width

        font.pixelSize: 22
        color: MySingleton.changeTextColor ? "red" : "blue"
        text: MySingleton.loremIpsum
        wrapMode: Text.WrapAnywhere
    }

    Button{
        id: myButton
        anchors.top: myText.bottom

        width: parent.width / 4
        text: "Trocar Cor"

        onClicked: {
            MySingleton.changeTextColor = !MySingleton.changeTextColor;
        }

    }

}
