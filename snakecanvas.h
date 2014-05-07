#ifndef SNAKECANVAS_H
#define SNAKECANVAS_H


#include <QtQuick/QQuickPaintedItem>
#include <QColor>
#include <QPainter>
#include <QTimer>

typedef struct
{
    int x,y;
}square;

class SnakeCanvas : public QQuickPaintedItem
{
    Q_OBJECT
    //Q_PROPERTY(QRect width READ name WRITE setName NOTIFY nameChanged)
public:
    SnakeCanvas(QQuickItem *parent = 0);
    void paint(QPainter *);
private:
    void drawSnake(bool pop);
    void eatFood();
    void checkSnake(int x, int y);
    void updateSpeed();

signals:

public slots:
    void upPressed();
    void downPressed();
    void leftPressed();
    void rightPressed();
    void start();
private slots:
    void moveSnake();
    void placeFood();


private:
    QTimer m_timer;
    std::vector<square> m_snake;
    int m_direction; //0-left, 1-right, 2-up, 3-down
    bool m_gameOver,m_foodPlaced;
    square m_food;
    int squareSize;

};

#endif // SNAKECANVAS_H
