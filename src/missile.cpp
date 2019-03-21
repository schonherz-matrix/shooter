#include "missile.h"

#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>

Missile::Missile(const QPointF& start_position, QColor color, QGraphicsItem* owner, bool direction_down):
    parent(owner),
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
    CollidingItem::advance(phase);
    
    setPos(pos() + (speed/2));

    if( pos().y() < 0 || pos().y() > 26 )
        scene()->removeItem(this);
}

void Missile::meetWith(PowerUp& pu){
    //parent->applyPowerUp(pu.getPower());
    
    delete &pu;    
    scene()->removeItem(this);
}

void Missile::meetWith(Asteroid& as){
   //as.kill();
    
    scene()->removeItem(this);
}

void Missile::meetWith(Player& p){
    p.hurt(20);
    
   scene()->removeItem(this);
}


void Missile::hit(QGraphicsItem *item)
{
    // TODO
}
