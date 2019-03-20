#include "player.h"

Player::Player(bool upper, Bar *bar) : bar(bar), upper(upper), life(max_life)
{
    if(upper) {
        // lightpink	#FFB6C1	rgb(255,182,193)
        color = QColor(255,82,193);
        setPos(15,0);
        bar->setPos(31,0);
    }
    else {
        color = Qt::green;
        setPos(15,24);
        bar->setPos(0,0);
    }
}

QRectF Player::boundingRect() const
{
    return QRectF(0, 0, 3, 3);
}

QPainterPath Player::shape() const
{
    QPainterPath path;

    if(upper) {
        path.addRect(0,0,3,1);
        path.addRect(0,1,1,1);
    }
    else {
        path.addRect(1,0,1,1);
        path.addRect(0,1,3,1);
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

void Player::advance(int phase)
{
    Q_UNUSED(phase);
    // TODO impelemnt this
}
