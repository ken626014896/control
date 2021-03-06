﻿import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

import QtQuick.Layouts 1.12
import QtMultimedia 5.12
Rectangle{

   color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1);
   property  var height_e: 50
   property alias objModel_a: objModel
   Rectangle{ //通道号页面
       anchors.fill: parent
       id:channel_rect
       color: "transparent"
       visible: !itemDisplay.visible
       Text {
           anchors.bottom: parent.bottom
           anchors.horizontalCenter: parent.horizontalCenter
           text: "视频页面"
           color: "white"
           z:2
           MouseArea{
               anchors.fill: parent
               onClicked: {
//                   objModel.clear()
//                   objModel.append($manager.get_group_childs())
               }
           }
       }


       //Model
       ListModel {
           id: objModel
           Component.onCompleted: {
               //        objModel.append({"name":"A1","level":0,"subNode":[]})
               //        objModel.append({"name":"A2","level":0,"subNode":[]})
               //        objModel.append({"name":"A3","level":0,"subNode":[]})
               //        objModel.get(1).subNode.append({"name":"B1","level":1,"subNode":[]})
               //        objModel.get(1).subNode.append({"name":"B2","level":1,"subNode":[]})
               //        objModel.get(1).subNode.get(0).subNode.append({"name":"C3","level":2,"subNode":[]})
           }
       }

       //Delegate
       Component {
           id: objRecursiveDelegate
           Column {

               id:column_group
               Row {
                   //indent
                   //            Item {
                   //                height: 1
                   //                width: model.level * 20
                   //            }

                   Rectangle{
                       id:item_rect
                       height: c_listview.height/9
                       width: c_listview.width
                       border.color: "black"
                       color: rect_btn.pressed||rect_btn2.pressed?"#1E90FF":"white"
                       property bool isopen: true

                       Rectangle{ //目录
                          anchors.fill: parent
                          color: "transparent"
                          visible: dmType==1
                          Row{
                              anchors.left: parent.left
                              anchors.right: parent.right
                              height: parent.height
                              spacing: parent.width*0.02
                              anchors.leftMargin: parent.width*0.02+parent.height/2*dmLevel


                              Rectangle{
                                  width:camera_icon.contentWidth
                                  height: camera_icon.contentHeight
                                  color: "transparent"
                                  anchors.verticalCenter: parent.verticalCenter

                                  Text {

                                      text: item_rect.isopen?"\uf107":"\uf105"
                                      color: "grey"
                                      anchors.centerIn: parent
                                      font.pixelSize: parent.height*0.8
                                      font.family: "FontAwesome"

                                  }
                              }

                              Text {
                                  text: "\uf0e8"
                                  color: "grey"
                                  visible: dmType==1
                                  font.pixelSize: parent.height/2
                                  font.family: "FontAwesome"
                                  anchors.verticalCenter: parent.verticalCenter
                              }
                              Text {
                                  text:dmName
                                  anchors.verticalCenter: parent.verticalCenter
                                  font.pixelSize: parent.height/3
                                  font.family: "微软雅黑"
                              }


//                              Text {
//                                  text:dmLevel
//                                  font.pixelSize: parent.height/4
//                                  anchors.verticalCenter: parent.verticalCenter
//                                  color: "red"

//                              }
                          }
                          MouseArea{
                              id:rect_btn
                              anchors.fill: parent
                              onClicked: {
   //                               console.log(dmCount)
                                  item_rect.isopen=!item_rect.isopen


                                  var v = false;
                                  for(var i=1; i < column_group.children.length -1; i++){
                                      column_group.children[i].visible = !column_group.children[i].visible
                                      v = column_group.children[i].visible;
                                  }

                              }
                          }

                       }
                       Rectangle{ //摄像机
                          anchors.fill: parent
                          color: "transparent"
                          visible: dmType==0
                          Row{
                              anchors.left: parent.left
                              anchors.right: parent.right
                              height: parent.height
                              spacing: parent.width*0.02
                              anchors.leftMargin: parent.width*0.02+parent.height/2*dmLevel
                              Text {
                                  id:camera_icon
                                  text: "\uf03d"
                                  color: "grey"
                                  font.pixelSize: parent.height/2
                                  font.family: "FontAwesome"
                                  anchors.verticalCenter: parent.verticalCenter
                              }
                              Text {
                                  text:dmName
                                  anchors.verticalCenter: parent.verticalCenter
                                  font.pixelSize: parent.height/3
                                  font.family: "微软雅黑"
                              }

                              Text {
                                  text:dmUrl
                                  font.pixelSize: parent.height/4
                                  anchors.verticalCenter: parent.verticalCenter
                                  visible: dmType==0

                              }

//                              Text {
//                                  text:dmLevel
//                                  font.pixelSize: parent.height/4
//                                  anchors.verticalCenter: parent.verticalCenter
//                                  color: "red"

//                              }
                          }
                          MouseArea{
                            id:rect_btn2
                            anchors.fill: parent
                            onDoubleClicked: {
                                    if(dmUrl=="")
                                        return
                                    $manager.start_play_video(dmId)
                                    itemDisplay.video_id=dmId
                                    itemDisplay.visible=true
                                    itemDisplay.busy_vis=true

                            }
                          }

                       }

                   }

               }

               Repeater {
                   model: dmGroupChilds
                   delegate: objRecursiveDelegate
               }
           }
       }

       //View
       ListView{
           id:c_listview
           anchors.fill: parent
           model:objModel
           delegate: objRecursiveDelegate
           clip: true

       }
   }




   Video_item_ffmpeg{
       id: itemDisplay
       anchors.fill: parent
       visible: false

   }
}

