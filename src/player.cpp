#include "player.h"

Player::Player(bool upper) : upper(upper)
{
    if(upper) {
        // lightpink	#FFB6C1	rgb(255,182,193)
        color = QColor(255,82,193);
    }
    else {
        color = Qt::green;
    }
}

QRectF Player::boundingRect() const
{
    return QRectF(0, 0, 3, 3);
}

QPainterPath Player::shape() const
{
    QPainterPath path;
    //TODO implement this

    if(upper) {
        path.addRect(0,0,2,1);
        path.addRect(1,1,1,1);
    }
    else {
        path.addRect(0,0,2,1);
        path.addRect(1,1,1,1);
    }

    return path;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(QPen(color, 1));

    if(upper) {
        painter->drawPoint(0,0);
        painter->drawPoint(1,0);
        painter->drawPoint(1,1);
        painter->drawPoint(2,0);
    }
    else {
        painter->drawPoint(0,1);
        painter->drawPoint(1,1);
        painter->drawPoint(1,0);
        painter->drawPoint(2,1);
    }
}
