import QtQuick 2.0
import Snake 1.0
import QtSensors 5.0

Rectangle {
    width: 360
    height: 360
    SnakeCanvas {
        id: aSnake
        anchors.fill: parent;
        Rectangle {
            x: 0
            y: 0
            color: "gray"
            Text {
                anchors.fill: parent
                text: "Restart"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            MouseArea {
                anchors.fill: parent
                onClicked: aSnake.start()
            }


            width: 50
            height: 25
            visible: false;
            objectName: "restartButton";
        }

        focus: true
        Keys.onUpPressed: aSnake.upPressed()
        Keys.onDownPressed: aSnake.downPressed()
        Keys.onLeftPressed: aSnake.leftPressed()
        Keys.onRightPressed: aSnake.rightPressed()
        MouseArea {
            anchors.fill: parent
            property int startX;
            property int startY;

            onPressed: {
                startX = mouse.x;
                startY = mouse.y;
            }

            onReleased: {
                var deltax = mouse.x - startX;
                var deltay = mouse.y - startY;

                if (Math.abs(deltax) > 50 || Math.abs(deltay) > 50) {
                    if (deltax > 30 && Math.abs(deltay) < 30) {
                        // swipe right
                        aSnake.rightPressed();
                    } else if (deltax < -30 && Math.abs(deltay) < 30) {
                        // swipe left
                        aSnake.leftPressed();
                    } else if (Math.abs(deltax) < 30 && deltay > 30) {
                        // swipe down
                        aSnake.downPressed();
                    } else if (Math.abs(deltax) < 30 && deltay < 30) {
                        // swipe up
                        aSnake.upPressed();
                    }
                }
            }

        }
    }
}
