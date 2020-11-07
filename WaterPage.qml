import QtQuick 2.0
import QtQuick.Controls 2.5
Rectangle{
   id:waterpage
   color: "grey"
   Text {
       anchors.centerIn: parent
       text: "水利页面"
       color: "white"
   }
   Grid {
       width: parent.width
       height: parent.height/2
       columns: 3
       rows: 2

       Rectangle {//土壤
           color: "white";
           width: parent.width/3;
           height: parent.height/2
           border.color: "black"
           border.width: 1
           Text {

               text: qsTr("土壤墒情站")
               anchors.centerIn: parent
               color: "black"
               font.family: "微软雅黑"
           }
           MouseArea{
              anchors.fill: parent
              onPressed: {
                  list_title_text.text=qsTr("土壤墒情站")
                  view.currentIndex=1
                  parent.color="#87CEFA"
              }
              onReleased: {
                  parent.color="white"

              }


           }
       }
       Rectangle {//气象站
           color: "white";
           width: parent.width/3;
           height: parent.height/2
           border.color: "black"
           border.width: 1
           Text {

               text: qsTr("气象站")
               anchors.centerIn: parent
               color: "black"
               font.family: "微软雅黑"
           }
           MouseArea{
              anchors.fill: parent
              onPressed: {
                  list_title_text.text=qsTr("气象站")
                  view.currentIndex=1
                  parent.color="#87CEFA"
              }
              onReleased: {
                  parent.color="white"

              }


           }
       }
       Rectangle {//灌溉管线
           color: "white";
           width: parent.width/3;
           height: parent.height/2
           border.color: "black"
           border.width: 1
           Text {

               text: qsTr("灌溉管线")
               anchors.centerIn: parent
               color: "black"
               font.family: "微软雅黑"
           }
           MouseArea{
              anchors.fill: parent
              onPressed: {
                  list_title_text.text=qsTr("灌溉管线")
                  view.currentIndex=1
                  parent.color="#87CEFA"
              }
              onReleased: {
                  parent.color="white"

              }


           }
       }
       Rectangle { //水肥机
           color: "white";
           width: parent.width/3;
           height: parent.height/2
           border.color: "black"
           border.width: 1

           Text {

               text: qsTr("水肥机")
               anchors.centerIn: parent
               color: "black"
               font.family: "微软雅黑"
           }
           MouseArea{
              anchors.fill: parent
              onPressed: {
                  list_title_text.text=qsTr("水肥机")
                  view.currentIndex=1
                  parent.color="#87CEFA"
              }
              onReleased: {
                  parent.color="white"

              }


           }
       }
       Rectangle {//泵房
           color: "white";
           width: parent.width/3;
           height: parent.height/2
           border.color: "black"
           border.width: 1
           Text {

               text: qsTr("泵房")
               anchors.centerIn: parent
               color: "black"
               font.family: "微软雅黑"
           }
           MouseArea{
              anchors.fill: parent
              onPressed: {
                  list_title_text.text=qsTr("泵房")
                  view.currentIndex=1
                  parent.color="#87CEFA"
              }
              onReleased: {
                  parent.color="white"

              }


           }
       }
       Rectangle { //高位水池
           color: "white";
           width: parent.width/3;
           height: parent.height/2
           border.color: "black"
           border.width: 1
           Text {

               text: qsTr("高位水池")
               anchors.centerIn: parent
               color: "black"
               font.family: "微软雅黑"
           }
           MouseArea{
              anchors.fill: parent
              onPressed: {
                  list_title_text.text=qsTr("高位水池")
                  view.currentIndex=1
                  parent.color="#87CEFA"
              }
              onReleased: {
                  parent.color="white"

              }


           }
       }
   }



}

