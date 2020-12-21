import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width : (Qt.platform.os === "android") ? Screen.width : 360
    height : (Qt.platform.os === "android") ? Screen.height : 640
    title: qsTr("水利监控")
    //除以得到系数
    id:root
    property real multiplierH : root.height / 640;
    property real multiplierW : root.width / 360;
    //计算高的函数
    function dpH(numbers)
    {
        return numbers * multiplierH;
    }
    //计算宽的函数
    function dpW(numbers)
    {

        return numbers * multiplierW;
    }
    //平均值函数
    function dpX(numbers)
    {
        return (dpW(numbers) + dpH(numbers)) / 2;
    }

    ListModel{
       id:itemModel
       ListElement{
          title:"水利"

       }
       ListElement{
          title:"视频"

       }
       ListElement{
          title:"我的"

       }

    }
    LoginPage{
       id:loginPage
       anchors.fill: parent
       z:2
    }
    SwipeView {
         id: view

         currentIndex: 0
         anchors.fill: parent

         interactive:false
         Rectangle{  //主界面
               width: view.width
               height: view.height
               Rectangle{
                  id:title_rect
                  width: parent.width
                  height: parent.height/10
                  color: "green"
                  Text {
                      id:title_text
                      anchors.centerIn: parent
                      text: "水利"
                      color: "white"
                  }
               }
               StackLayout {
                    id: layout

                    currentIndex: 0
                    anchors.top: title_rect.bottom
                    anchors.bottom: bottom_rect.top
                    width: parent.width
                    WaterPage {
                        id:waterpage
                        width:parent.width
                        height:parent.height
                    }
                    VideoPage {
                        id:videopage
                        width:parent.width
                        height:parent.height
                    }
                    UserPage {
                        id:userpage
                        width:parent.width
                        height:parent.height
                    }
                }
               Rectangle{
                   id:bottom_rect
                   width: parent.width
                   height: parent.height/10
                   anchors.bottom: parent.bottom
                   color: "green"

                   Row{
                       anchors.fill: parent
                       Repeater {
                                model: itemModel
                                Rectangle {
                                    width: bottom_rect.width/3; height: bottom_rect.height
                                    border.width: 1
                                    color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1);

                                    Text {
                                        anchors.centerIn: parent
                                        text: title
                                        color: "white"
                                    }

                                    MouseArea{
                                      anchors.fill: parent
                                      onClicked: {
                                          layout.currentIndex=index
                                          title_text.text=title


                                          if(layout.currentIndex==1)
                                                videopage.objModel_a.clear()
                                                videopage.objModel_a.append($manager.get_group_childs())
                                      }
                                    }
                                }
                            }

                   }



               }


         }
         Rectangle{ //不同选项的列表页面
             width: view.width
             height: view.height

             Rectangle{
                id:list_title_rect
                width: parent.width
                height: parent.height/10
                color: "green"
                Text {
                    id:list_title_text
                    anchors.centerIn: parent
                    font.pixelSize: parent.height/3
                    font.family: "微软雅黑"
                    text: "水利"
                    color: "white"
                }
                Rectangle{
                     height: parent.height
                     width: height
                     color: "transparent"
                     MouseArea{
                       anchors.fill: parent
                       onClicked: {
                       view.currentIndex=0
                       }
                     }
                     Text {
                         anchors.centerIn: parent
                         text: "\uf104"
                         color: "white"
                         font.pixelSize: parent.height/2
                         font.family: "FontAwesome"
                     }
                }

             }

             ListView{
                id:item_lsit
                width: parent.width
                anchors.bottom: parent.bottom
                anchors.top: list_title_rect.bottom
                clip: true
                model:$test
                boundsBehavior: Flickable.StopAtBounds

                delegate: Rectangle {
                          width: item_lsit.width
                          height: item_lsit.height/10
                          color: Qt.rgba(Math.random(), Math.random(), Math.random(), 1)

                          Text {
                                 anchors.centerIn: parent
                                 text:dmName
                                 color: "white"
                             }

                          Rectangle{
                               height: parent.height
                               width: height
                               anchors.right: parent.right
                               color: "transparent"
                               MouseArea{
                                 anchors.fill: parent
                                 onClicked: {
                                 view.currentIndex=2
                                 }
                               }
                               Text {
                                   anchors.centerIn: parent
                                   text: "\uf105"
                                   color: "white"
                                   font.pixelSize: parent.height/2
                                   font.family: "FontAwesome"
                               }
                          }

                }

             }
         }
         Rectangle{
             width: view.width
             height: view.height

             Rectangle{
                id:list_title_rect2
                width: parent.width
                height: parent.height/10
                color: "green"
                Text {
                    anchors.centerIn: parent
                    font.pixelSize: parent.height/3
                    font.family: "微软雅黑"
                    text: list_title_text.text
                    color: "white"
                }
                Rectangle{
                     height: parent.height
                     width: height
                     color: "transparent"
                     MouseArea{
                       anchors.fill: parent
                       onClicked: {
                       view.currentIndex=1
                       }
                     }
                     Text {
                         anchors.centerIn: parent
                         text: "\uf104"
                         color: "white"
                         font.pixelSize: parent.height/2
                         font.family: "FontAwesome"
                     }
                }




             }


             Text {
                 anchors.centerIn: parent
                 text: qsTr("text")
             }

         }




     }


}
