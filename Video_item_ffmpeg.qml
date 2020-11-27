import QtQuick 2.0
import QtQuick.Controls 2.5
import videoitem 1.0
Rectangle {
   anchors.fill: parent
   property var video_id: ""
   property var camera_id: video_id
      ListView {
          id:video_list
          width: parent.width
          height: parent.height/2
          model: $video
          orientation: ListView.Horizontal
          clip: true
          delegate:Rectangle{
              width: video_list.width
              height: video_list.height


              VideoItem{
                  id: video
                  anchors.fill: parent
                  model:$video
                  video_id: dmId

                  Component.onCompleted: {

                  }
              }
          }
      }



      Row{
         anchors.horizontalCenter: parent.horizontalCenter
         spacing: 10
         anchors.bottom: parent.bottom
         Button{
             text: "pause"
             onClicked: {
                $manager.pause_play_video(video_id)
             }
         }
         Button{
             text: "stop"
             onClicked: {
                 $manager.stop_play_video(video_id)
                 itemDisplay.visible=false
             }
         }
         Button{

             onClicked: {
                 $manager.ptz_control(camera_id,"left","start",2,2)

             }
             text: "test"

         }
      }





}
