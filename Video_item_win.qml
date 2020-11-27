import QtQuick 2.0
import QtQuick.Controls 2.5
import QtMultimedia 5.12
Rectangle{

   signal  back()
    property alias playerSource:player.source

   anchors.fill: parent

   Text {
       text: qsTr("播放地址：")+player.source
   }



   Row{
       anchors.horizontalCenter: parent.horizontalCenter
       anchors.bottom: parent.bottom
       Button{

           onClicked: {


               player.play()
           }
           text: "播放"

       }
       Button{

           onClicked: {


               player.pause()
           }
           text: "暂停"

       }
       Button{

           onClicked: {

               itemDisplay.visible=false
               player.stop()
           }
           text: "返回"

       }

   }



   MediaPlayer {
       id: player
       source: ""

       onPlaying: {

       }
   }

   VideoOutput {
       id: videoOutput
       source: player
       width: parent.width
       height: parent.height/2



   }
   Component.onCompleted: {


   }

}
