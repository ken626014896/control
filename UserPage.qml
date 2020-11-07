import QtQuick 2.0

Rectangle{

   color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
   Text {
       anchors.centerIn: parent
       text: "个人页面"
       color: "white"
   }

   Text {
       anchors.centerIn: parent
       text: "\uf007"
       color: "white"
       font.family: "FontAwesome"
   }
}
