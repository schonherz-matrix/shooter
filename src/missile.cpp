#include "missile.h"

#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include "player.h"

Missile::Missile(const QPointF& start_position, QColor color, Player* const owner, bool direction_down):
    owner(owner),
    color(color)
{
    speed = { 0, (direction_down ? 1.0 : -1.0) };
    
    setPos(start_position + speed);
}

QRectF Missile::boundingRect() const {
    return QRectF(0,0,1,1);
}

QPainterPath Missile::shape() const {
    QPainterPath path;
    path.addRect(0,0,1,1);
    return path;
}

void Missile::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(item);
    Q_UNUSED(widget);

    painter->setPen(QPen(color, 1));
    painter->drawPoint(0,0);
}

void Missile::advance(int phase) {
    if(phase == 0){
        if (lookAround(owner))
            remove();
        return;
    }
    
    setPos(pos() + (speed/2));

    if( pos().y() < 0 || pos().y() > 26 ){
        remove();
    }
}

void Missile::hit(Player *)
{
    remove();
}
