#include "missile.h"
#include <QPainter>

Missile(const QPointF& start_position, QColor color, QGraphicsItem* parent, bool direction_down):
    parent(parent),
    color(color)
{
    speed = { 0.0, (direction_down ? 1 : -1) };
    
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
    if (phase == 0)
        return;
    
    setPos(start_position + (speed/20));
}

void meetWith(PowerUp& pu){
    this->parent->applyPowerUp(pu.getPower());
    
    delete &pu;    
    delete this;
}

void meetWith(Asteroid& as){
    as.kill();
    
    delete this;
}

void meetWith(Player& p){
    p.hurt(20);
    
    delete this;
}
