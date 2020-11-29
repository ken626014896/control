import QtQuick 2.0
import QtQuick.Controls 2.5
import videoitem 1.0
Rectangle {
   anchors.fill: parent
   property var video_id: ""
   property var camera_id: video_id
   property alias busy_vis: busy.visible

   color: "white"
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
                  onPlay_signal:{
                     busy.visible=false
                  }
              }
          }
      }

      BusyIndicator {
           running: true
           z:2
           id:busy
           anchors.horizontalCenter: parent.horizontalCenter
           y:parent.height/4-height/2

       }
      Text {
          anchors.horizontalCenter: parent.horizontalCenter
          anchors.top: busy.bottom
          anchors.topMargin: 10
          visible: busy.visible
          text: qsTr("loading..")
          color: "black"
      }
      ListModel{
         id:cmditemModel
         ListElement{
            mindex:0
            mtitle:"左上"
            mcmd:"leftup"
            mText:"\uf137"

         }
         ListElement{
            mindex:1
            mtitle:"上"
            mcmd:"up"
            mText:"\uf139"

         }
         ListElement{
            mindex:2
            mtitle:"右上"
            mcmd:"rightup"
            mText:"\uf138"

         }

         ListElement{
            mindex:3
            mtitle:"左"
            mcmd:"left"
            mText:"\uf137"

         }
         ListElement{
            mindex:4
            mtitle:"中心"
            mcmd:""
            mText:"\uf03d"

         }
         ListElement{
            mindex:5
            mtitle:"右"
            mcmd:"right"
            mText:"\uf138"

         }


         ListElement{
            mindex:6
            mtitle:"左下"
            mcmd:"leftdown"
            mText:"\uf137"

         }
         ListElement{
            mindex:7
            mtitle:"下"
            mText:"\uf13a"
            mcmd:"down"

         }
         ListElement{
            mindex:8
            mtitle:"右下"
            mcmd:"rightdown"
            mText:"\uf138"

         }
      }
      Timer {
          id:ptz_timer
          interval: 200;
          repeat: true
          onTriggered: {
              if(direct.send_cmd!=""){
                  $manager.ptz_control(camera_id,direct.send_cmd,"start",2,2)
                  console.log(direct.send_cmd)

              }
          }
      }
      Grid{ //方向控制
         height: parent.height/3
         anchors.bottom: parent.bottom
         width: parent.width/3*2
         id:direct
         columns: 3
         rows: 3
         property var send_cmd: ""
         Repeater{
              model:cmditemModel

              Rectangle{
                  width: direct.width/3
                  height: direct.height/3
                  color: "transparent"
                  Rectangle{
                     anchors.fill: parent
                     anchors.margins: 2

                     color: "transparent"
                     Text {
                         anchors.centerIn: parent
                         text: mText
                         rotation: mindex==0||mindex==8?45:(mindex==2||mindex==6?-45:0)
                         color:direct_btn.pressed? "green":"black"
                         font.pixelSize: parent.height*0.8
                         font.family: "FontAwesome"
                     }
                     MouseArea{
                        id:direct_btn
                        anchors.fill: parent
                        enabled: mindex!=4
                        onClicked: {

                        }
                        onPressed: {
                            direct.send_cmd=mcmd
                            ptz_timer.start()
                        }
                        onReleased: {
                            ptz_timer.stop()
                           $manager.ptz_control(camera_id,mcmd,"stop",2,2)
                        }
                     }
                  }

              }



         }
      }

      Rectangle{ //开始暂停控制
          id:control_rect
          anchors.top: video_list.bottom
          width: parent.width
          height: parent.height*0.1
          color: "black"
          property bool isplay : true
          Row{
             anchors.centerIn: parent
             spacing: 10

             Rectangle{
                 height: control_rect.height*0.9
                 width: height
                 radius: height/2
                 color: "transparent"
                 Text {
                     anchors.centerIn: parent
                     text:control_rect.isplay?"\uf01d":"\uf28c"
                     color:"white"
                     font.pixelSize: parent.height*0.8
                     font.family: "FontAwesome"
                 }
                 MouseArea{
                     anchors.fill: parent
                     onClicked: {
                         control_rect.isplay=!control_rect.isplay
                         $manager.pause_play_video(video_id)
                     }

                 }
             }
             Rectangle{
                 height: control_rect.height*0.9
                 width: height
                 radius: height/2
                 color: "transparent"
                 Text {
                     anchors.centerIn: parent
                     text:"\uf28e"
                     color:stop_btn.pressed? "green":"white"
                     font.pixelSize: parent.height*0.8
                     font.family: "FontAwesome"
                 }
                 MouseArea{
                     id:stop_btn
                     anchors.fill: parent
                     onClicked: {
                         $manager.stop_play_video(video_id)
                         itemDisplay.visible=false
                     }

                 }
             }


          }


      }




      Rectangle{
         anchors.right: parent.right
         anchors.left: direct.right
         anchors.bottom: parent.bottom
         height: direct.height
         id:bianjiao_rect

         Row{
             anchors.top: parent.top
             spacing: parent.width*0.1
             Text {
                 anchors.verticalCenter: parent.verticalCenter
                 text:"\uf151"
                 color:out_btn.pressed? "green":"black"
                 font.pixelSize: bianjiao_rect.height*0.2
                 font.family: "FontAwesome"

                 MouseArea{
                     id:out_btn
                     anchors.fill: parent
                     onPressed: {
                         direct.send_cmd="zoomout"
                         ptz_timer.start()
                     }
                     onReleased: {
                         ptz_timer.stop()
                        $manager.ptz_control(camera_id,"zoomout","stop",2,2)
                     }

                 }
             }
             Text {
                 id:title_text
                 anchors.verticalCenter: parent.verticalCenter
                 text: "变焦"
                 font.pixelSize: bianjiao_rect.height*0.1
                 font.family: "微软雅黑"
                 color: "black"
             }
             Text {
                 anchors.verticalCenter: parent.verticalCenter
                 text:"\uf150"
                 color:in_btn.pressed? "green":"black"
                 font.pixelSize: bianjiao_rect.height*0.2
                 font.family: "FontAwesome"

                 MouseArea{
                     id:in_btn
                     anchors.fill: parent
                     onPressed: {
                         direct.send_cmd="zoomin"
                         ptz_timer.start()
                     }
                     onReleased: {
                         ptz_timer.stop()
                        $manager.ptz_control(camera_id,"zoomin","stop",2,2)
                     }

                 }
             }


         }
      }

}
