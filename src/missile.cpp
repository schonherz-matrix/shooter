#include "missile.h"
#include <QPainter>

Missile::Missile(const QPointF& start_position, QColor color, QGraphicsItem* owner, bool direction_down):
    parent(owner),
    color(color)
{
    speed = { 0.0, (direction_down ? 1.0 : -1.0) };
    
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
    
    if( pos().y() < 0 || pos().y() > 26 )
        delete this;
}

void Missile::meetWith(PowerUp& pu){
    //parent->applyPowerUp(pu.getPower());
    
    delete &pu;    
    delete this;
}

void Missile::meetWith(Asteroid& as){
   //as.kill();
    
    delete this;
}

void Missile::meetWith(Player& p){
    p.hurt(20);
    
    delete this;
}
