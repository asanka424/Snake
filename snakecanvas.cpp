#include "snakecanvas.h"

SnakeCanvas::SnakeCanvas(QQuickItem *parent) :
    m_gameOver(false),m_foodPlaced(false),QQuickPaintedItem(parent)
{
    //initial snake
    m_timer.setInterval(200);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(moveSnake()));
    connect(this,SIGNAL(widthChanged()),this,SLOT(placeFood()));
    connect(this,SIGNAL(heightChanged()),this,SLOT(placeFood()));

    this->start();

}

void SnakeCanvas::paint(QPainter *p_painter)
{
    if (!m_gameOver)
    {
        p_painter->setBrush(QBrush(QColor("blue")));
        p_painter->setPen(QColor("blue"));
        for (size_t i=0; i<m_snake.size(); i++)
        {
            p_painter->drawRect(m_snake[i].x, m_snake[i].y, 10, 10);
        }
        //food
        if (m_foodPlaced)
        p_painter->drawRect(m_food.x,m_food.y,10,10);
    }
    else
    {
        p_painter->drawText(QPointF(this->width()/2 - 30,this->height()/2),"Game Over");
        m_timer.stop();
        QObject *rect = this->findChild<QObject*>("restartButton");
        if (rect)
            rect->setProperty("visible", "true");
    }
    if (!m_foodPlaced)
        placeFood();
    //display score
    p_painter->setPen(QColor("black"));
    p_painter->drawText(QPointF(10,this->height()-10),QString("Score: ") + QString::number(m_snake.size()));
}
void SnakeCanvas::drawSnake(bool pop)
{
    if (pop)
        m_snake.pop_back();
    std::vector<square>::iterator it;
    it = m_snake.begin();
    int x,y;
    square point = *it;
    switch (m_direction)
    {
    case 0: //left
        x = point.x - 12;
        y = point.y;
        checkSnake(x,y);
        break;
    case 1: //right
        x = point.x + 12;
        y = point.y;
        checkSnake(x,y);
        break;
    case 2: //up
        x = point.x;
        y = point.y - 12;
        checkSnake(x,y);
        break;
    case 3: //down
        x = point.x;
        y = point.y + 12;
        checkSnake(x,y);
        break;
    }
    square newPoint;
    newPoint.x = x;
    newPoint.y = y;
    m_snake.insert(it,newPoint);
    //check if snake ate food
    if (pop)
    {
        if ((newPoint.x >= m_food.x && newPoint.x  <= m_food.x + 10) &&
                (newPoint.y >= m_food.y && newPoint.y  <= m_food.y + 10))
        {
            drawSnake(false);
            updateSpeed();
            m_foodPlaced = false;
        }
        else if ((newPoint.x+9 >= m_food.x && newPoint.x  <= m_food.x + 10) &&
                (newPoint.y+9 >= m_food.y && newPoint.y  <= m_food.y + 10))
        {
            drawSnake(false);
            updateSpeed();
            m_foodPlaced = false;
        }
    }
}

void SnakeCanvas::moveSnake()
{
    //placeFood();
    drawSnake(true);
    this->update();
}
void SnakeCanvas::upPressed()
{
    m_direction = 2;
}
void SnakeCanvas::downPressed()
{
    m_direction = 3;
}
void SnakeCanvas::leftPressed()
{
    m_direction = 0;
}
void SnakeCanvas::rightPressed()
{
    m_direction = 1;
}

void SnakeCanvas::checkSnake(int x, int y)
{
    m_gameOver = (x < 0 || x+10 > this->width() || y < 0 || y+10 > this->height());
    if (!m_gameOver)
    {
        for (size_t i=1; i<m_snake.size(); i++)
        {
            square point = m_snake[i];
            m_gameOver = (x >= point.x && x  <= point.x + 11) && (y >= point.y && y  <= point.y + 11);
            if (m_gameOver)
                break;
        }
    }
}
void SnakeCanvas::placeFood()
{
    bool wrongPlace = true;
    int x,y;
    while (wrongPlace)
    {
        x = qrand() % (int)this->width();
        y = qrand() % (int)this->height();
        if (x+10 >= (int)this->width() || y + 10 >= (int)this->height())
            continue;
        for (size_t i=0; i<m_snake.size(); i++)
        {
            square point = m_snake[i];
            wrongPlace = (x >= point.x && x  <= point.x + 11) && (y >= point.y && y  <= point.y + 11);
            if (!wrongPlace)
                break;
        }
    }
    m_food.x = x;
    m_food.y = y;
    m_foodPlaced = true;
}
void SnakeCanvas::start()
{
    m_snake.resize(5);
    int j=4;
    for (size_t i=0; i<m_snake.size(); i++)
    {
        square point;
        point.x = i * 12;
        point.y = 0;
        m_snake[j--] = point;
    }
    //initial direction
    m_direction = 1; //left
    m_timer.start();
    QObject *rect = this->findChild<QObject*>("restartButton");
    if (rect)
        rect->setProperty("visible", "false");
}
void SnakeCanvas::updateSpeed()
{
    int snakeSize = (int)m_snake.size();
    if (snakeSize > 100)
    {
        m_timer.setInterval(100);
        return;
    }
    else if (snakeSize > 80)
    {
        m_timer.setInterval(120);
        return;
    }
    else if (snakeSize > 60)
    {
        m_timer.setInterval(140);
        return;
    }
    else if (snakeSize > 40)
    {
        m_timer.setInterval(160);
        return;
    }
    else if (snakeSize > 20)
    {
        m_timer.setInterval(180);
        return;
    }
}
