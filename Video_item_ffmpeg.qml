import QtQuick 2.0
import videoitem 1.0
Rectangle {
   anchors.fill: parent

      ListView {
          id:video_list
          width: parent.width
          height: parent.height/2
          model: $video

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



}
