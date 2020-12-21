import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.12
Rectangle {
    id: loginPage
    color: "white"
    visible: true

    Rectangle{
        id: bg_rect
        anchors.fill: parent
        color: "#ecedf1"
        z: 0
    }
    Column{
        width: parent.width
        height: dpH(150)

        y: dpH(100)
        TextField{
            id :ip_TF
            x: 0
            y: 0
            z: 1
            width: dpW(parent.width)
            height: dpH(30)
            placeholderText: "ip"
            style:TextFieldStyle{

                background: Rectangle {
                    color: "white"
                }
            }

        }
        TextField{
            id :username_TF
            x: 0
            y: 0
            z: 1
            width: dpW(parent.width)
            height: dpH(30)
            placeholderText: "用户名"
            style:TextFieldStyle{

                background: Rectangle {
                    color: "white"
                }
            }

        }

        TextField{
            id :password_TF
            x: 0
            y: dpH(30)
            z: 1
            width: dpW(parent.width)
            height: dpH(30)
            echoMode: 2
            placeholderText: "密码"
            style:TextFieldStyle{
                background: Rectangle {
                    color: "white"
                }
            }

        }

        Rectangle{
            id: line_rect
            color: "#eaecee"
            height: dpH(20)
            width: parent.width
            x: 0
            y: dpH(30)
            z: 1
        }

        Rectangle {
            id: login_button
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#1eb9f2"
            width: dpW(340)
            height: dpH(30)
            radius: dpX(4)
            border.color: "#1eb9f2"
            border.width: dpX(1)
            Text{
                id: login_button_text
                anchors.centerIn: parent
                font.pixelSize: parent.height*0.5
                color: "white"
                text: "登 录"
            }


        }
    }

}
